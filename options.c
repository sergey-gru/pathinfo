
#include <stdlib.h>
#include <string.h>
#include <sergey-gru/cterm/cterm.h>
#include "options.h"

// FUNCTIONS
static void PrintHelp(const OPTS_Settings_t *set);
static void PrintVersion(const OPTS_Settings_t *set);
static int  GetMaxLongOptLen(const OPTS_Settings_t *set);
static void PrintOptions(const OPTS_Settings_t *set);

//Diagnostic
static int GetMaxLongOptLen(const OPTS_Settings_t *set)
{
	OPTS_OptionLong_t *opts_long = set->opts_long;
	OPTS_OptionDesc_t *opts_desc = set->opts_desc;

	int max = 0;
	for (int i = 0; opts_long[i].name != 0; i++)
	{
		int len = 0;
		if (opts_long[i].name) len += strlen(opts_long[i].name);
		if (opts_desc[i].arg)  len += strlen(opts_desc[i].arg);

		if (max < len) max = len;
	}
	return max;
}




/// \brief Prints a string str as paragraph no more than 80 width
/// Makes new lines if need
/// Returns a number of characters printedlast line
int _OPTS_PrintParagraph(const char *str,
						int align_first,
						int align,
						int max_width,
						unsigned int printed)
{
	//Make new align
	int i;
	for (i = printed; i < align_first; i++)
		putchar(' ');

	char *next = strchr(str, ' ');

	int len;
	while (next)
	{
		// Here next points on space
		len = next - str;

		// (width - 1) is for end space, witch I need to write if
		if (i + len > max_width)
		{
			//Make new align
			putchar('\n');
			for (i = 0; i < align; i++)
				putchar(' ');
		}

		fwrite(str, 1, len, stdout);
		putchar(' ');

		str = next + 1;
		i += len + 1;

		next = strchr(str, ' ');
	}

	len = strlen(str);
	if (i + len > max_width)
	{
		//Make new align
		putchar('\n');
		for (i = 0; i < align; i++)
			putchar(' ');
	}

	i += fwrite(str, 1, len, stdout);
	return i;
}

static void PrintOptions(const OPTS_Settings_t *set)
{
	OPTS_OptionLong_t *opts_long = set->opts_long;
	OPTS_OptionDesc_t *opts_desc = set->opts_desc;

	// for characters: --=<> or --=[]
	int max_optarg = GetMaxLongOptLen(set) + 5;

	int opt_string_len = max_optarg + 6;
	int opt_string_buf = max_optarg + 1;

	char *buf_arg = malloc(opt_string_buf);
	if (!buf_arg)
	{
		fprintf(stderr, "malloc error: cannot alloc %d bytes\n", opt_string_buf);
		exit(1);
	}

	printf("Options:\n");

	for (int i = 0; opts_long[i].name; i++)
	{
		switch (opts_long[i].has_arg)
		{
		default:
			snprintf(buf_arg, opt_string_buf, "--%s",
							opts_long[i].name);
			break;
		case required_argument:
			snprintf(buf_arg, opt_string_buf, "--%s[=%s]",
							opts_long[i].name, opts_desc[i].arg);
			break;
		case optional_argument:
			snprintf(buf_arg, opt_string_buf, "--%s=<%s>",
							opts_long[i].name, opts_desc[i].arg);
			break;
		}

		if (opts_long[i].val < _OPTS_CMD_BEGIN)
		{
			printf("  -%c, %-*s", (char)opts_long[i].val, max_optarg, buf_arg);
		}
		else
		{
			printf( "      %-*s", max_optarg, buf_arg);
		}

		_OPTS_PrintParagraph(opts_desc[i].desc,
						opt_string_len + 1,
						opt_string_len + 4,
						set->terminal_width,
						opt_string_len);
		putchar('\n');
	}
}


static void PrintHelp(const OPTS_Settings_t *set)
{
	if (set->FPrintUsage) set->FPrintUsage(stdout);
	PrintOptions(set);
	if (set->FPrintExplain) set->FPrintExplain(stdout);
}

static void PrintVersion(const OPTS_Settings_t *set)
{
	printf("Version: %s\n", set->prog_version);
}



int OPTS_ReadOptions(int argc,
				char **argv,
				const OPTS_Settings_t *set)
{
	opterr = 0;

	int c;
	int option_index = 0;
	while (1)
    {
		c = getopt_long(argc, argv, set->opts_short, set->opts_long, &option_index);

		/* Detect the end of the options. */
		if (c == -1)
			break;

		switch (c)
		{
			case 0:
				// Flag <opts_long[option_index].flag>
				// setted equal <opts_long[option_index].val>
				break;

			case ':':
				// No required argument of option <optopt>
				fprintf(stderr, "No required argument of option -%c\n", (char)optopt);
				exit(1);
				break;

			default:
				if (set->FSetOption)
				{
					int res = set->FSetOption(c, optarg);
					if (!res) break;
				}
				// no break

			case '?':
				// Unrecognized option <optopt>
				fprintf(stderr, "Unrecognized option -%c\n", (char)optopt);
				exit(1);
				break;

			case OPTS_CMD_HELP:
				PrintHelp(set);
				exit(0);
				break;

			case OPTS_CMD_VERSION:
				PrintVersion(set);
				exit(0);
				break;
		}
    }

    if (optind == argc)
	{
		fprintf(stderr, "%s: " CT_C_RED "fatal error:" CT_RESET " no input path\n",
				optind, set->prog_name);
		if (set->FPrintUsage) set->FPrintUsage(stderr);
		fprintf(stderr, "Try: '%s --help' for more information.\n", set->prog_name);
		exit(1);
	}

	return optind;
}


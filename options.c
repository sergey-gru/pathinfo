
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <sergey-gru/cterm/cterm.h>
#include "compile.h"
#include "options.h"


static void Options_Init(OPTS_Options_t *ptr);
static void PrintUsage(FILE *fstream);
static void PrintHelp(const char *name);
static void PrintVersion(const char *name);

typedef struct option Option_t;
typedef struct
{
	char *arg;
	char *desc;
} OptionDesc_t;
typedef enum
{
	CMD__BEGIN = 256,
	CMD_VERSION,
	CMD_HELP
} CMD_e;

OPTS_Options_t opts;
static const char *opts_short = ":apdDnbestTzO";
static const Option_t opts_long[] =
{
/*0*/   {"all",       no_argument,         0, 'a'},
/*1*/   {"path",      optional_argument,   0, 'p'},
/*2*/   {"dir",       optional_argument,   0, 'd'},
/*3*/   {"dirs",      optional_argument,   0, 'D'},
/*4*/   {"name",      optional_argument,   0, 'n'},
/*5*/   {"bname",     optional_argument,   0, 'b'},
/*6*/   {"ext",       optional_argument,   0, 'e'},
/*7*/   {"short",     optional_argument,   0, 's'},
/*8*/   {"tag",       optional_argument,   0, 't'},
/*9*/   {"tags",      optional_argument,   0, 'T'},
/*10*/  {"zero",      no_argument,         0, 'z'},
/*11*/  {"optimize",  no_argument,         0, 'O'},
/*12*/  {"help",      no_argument,         0, CMD_HELP},
/*13*/  {"version",   no_argument,         0, CMD_VERSION},
/*14*/  {0, 0, 0, 0}
};
static const int opts_long_count = sizeof(opts_long) / sizeof(Option_t) - 1;

static OptionDesc_t opts_desc[] =
{
/*0*/   {0,       "Output all variables. Equvalent -pdDnbestT"},
/*1*/   {"path",  "Output variable <path>  - full path " \
				  "(can be optimized if option -O presents)"},
/*2*/   {"dir",   "Output variable <dir>   - full directory"},
/*3*/   {"dirs",  "Output variable <dirs>  - array of directories variable"},
/*4*/   {"name",  "Output variable <name>  - name of file/(last directory)"},
/*5*/   {"bname", "Output variable <bname> - base name without last extension"},
/*6*/   {"ext",   "Output variable <ext>   - last extension (true extension)"},
/*7*/   {"short", "Output variable <short> - short name without all extensions"},
/*8*/   {"tag",   "Output variable <tag>   - all extensions as single string"},
/*9*/   {"tags",  "Output variable <tags>  - all extensions as array"},
/*10*/  {0,       "Output \\0 character instead of \\n at the end of string"},
/*11*/  {0,       "Normalize path before calculation"},
/*12*/  {0,       "Print this help"},
/*13*/  {0,       "Print version of program"},
/*14*/  {0, 0}
};
static const int opts_desc_count = sizeof(opts_desc) / sizeof(OptionDesc_t) - 1;

//Diagnostic
static int GetMaxLongOptLen(void)
{
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

static void PrintU()
{

}

static void PrintUsage(FILE *fstream)
{
	fprintf(fstream, "Usage: " OPTS_PROG_NAME " [-a] [-O] [-pdDnbestTz...] PATH [PATH...]\n");
}


/// \brief Prints a string str as paragraph no more than 80 width
/// Makes new lines if need
/// Returns a number of characters printedlast line
static int PrintParagraph(const char *str,
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

#define TERM_WIDTH        80
#define BUF_ARG_SIZE      16

static void PrintOptions()
{
	static char buf_arg[BUF_ARG_SIZE];

	int max_optarg = GetMaxLongOptLen();
	max_optarg += 5; // for characters: --=<> or --=[]
	int opt_string_len = max_optarg + 6;

	assert(BUF_ARG_SIZE >= max_optarg + 1);
	assert(BUF_ARG_SIZE == max_optarg + 1);

	printf("Options:\n");

	for (int i = 0; opts_long[i].name; i++)
	{
		switch (opts_long[i].has_arg)
		{
		default:
			snprintf(buf_arg, BUF_ARG_SIZE, "--%s",
							opts_long[i].name);
			break;
		case required_argument:
			snprintf(buf_arg, BUF_ARG_SIZE, "--%s[=%s]",
							opts_long[i].name, opts_desc[i].arg);
			break;
		case optional_argument:
			snprintf(buf_arg, BUF_ARG_SIZE, "--%s=<%s>",
							opts_long[i].name, opts_desc[i].arg);
			break;
		}

		if (opts_long[i].val < CMD__BEGIN)
		{
			printf("  -%c, %-*s", (char)opts_long[i].val, max_optarg, buf_arg);
		}
		else
		{
			printf( "      %-*s", max_optarg, buf_arg);
		}

		PrintParagraph(opts_desc[i].desc,
						opt_string_len + 1,
						opt_string_len + 4,
						TERM_WIDTH,
						opt_string_len);
		putchar('\n');
	}
}


static void PrintHelp(const char *name)
{
	PrintUsage(stdout);
	PrintOptions();



}

static void PrintVersion(const char *name)
{
	printf("Version 1.0\n");
}

static void Options_Init()
{
	assert(opts_long_count == opts_desc_count);
	assert(opts_long[opts_long_count].name == 0);
	assert(opts_desc[opts_desc_count].desc == 0);

	memset(&opts, 0, sizeof(OPTS_Options_t));

	opts.o_alias_path  = "path";
	opts.o_alias_dir   = "dir";
	opts.o_alias_dirs  = "dirs";
	opts.o_alias_name  = "name";
	opts.o_alias_bname = "bname";
	opts.o_alias_ext   = "ext";
	opts.o_alias_short = "short";
	opts.o_alias_tag   = "tag";
	opts.o_alias_tags  = "tags";

	opts.ch_str_end = '\n';
}

int OPTS_ReadArgs(int argc, char **argv)
{
	Options_Init(&opts);
	opterr = 0;

	int c;
	int option_index = 0;
	char f_o_opt = 0;
	while (1)
    {
		c = getopt_long(argc, argv, opts_short, opts_long, &option_index);

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
			case '?':
				// Unrecognized option <optopt>
				fprintf(stderr, "Unrecognized option -%c\n", (char)optopt);
				exit(1);
				break;

			case CMD_HELP:
				PrintHelp(argv[0]);
				exit(0);
				break;

			case CMD_VERSION:
				PrintVersion(argv[0]);
				exit(0);
				break;

			case 'a':
				opts.o_path  = 1;
				opts.o_dir   = 1;
				opts.o_dirs  = 1;
				opts.o_name  = 1;
				opts.o_bname = 1;
				opts.o_ext   = 1;
				opts.o_short = 1;
				opts.o_tag   = 1;
				opts.o_tags  = 1;
				f_o_opt = 1;
				break;

			case 'p': opts.o_path  = 1; f_o_opt = 1; break;
			case 'd': opts.o_dir   = 1; f_o_opt = 1; break;
			case 'D': opts.o_dirs  = 1; f_o_opt = 1; break;
			case 'n': opts.o_name  = 1; f_o_opt = 1; break;
			case 'b': opts.o_bname = 1; f_o_opt = 1; break;
			case 'e': opts.o_ext   = 1; f_o_opt = 1; break;
			case 's': opts.o_short = 1; f_o_opt = 1; break;
			case 't': opts.o_tag   = 1; f_o_opt = 1; break;
			case 'T': opts.o_tags  = 1; f_o_opt = 1; break;

			case 'z': opts.ch_str_end = '\0'; break;
			case 'O': opts.o_optimize  = 1; break;
		}
    }

	if (!f_o_opt)
	{
		opts.o_path = 1;
		opts.o_optimize = 1;
	}

    if (optind == argc)
	{
		fprintf(stderr, OPTS_PROG_NAME ": " \
				CT_C_RED "fatal error:" CT_RESET " no input path\n",
				optind);
		PrintUsage(stderr);
		fprintf(stderr, "Try: '" OPTS_PROG_NAME " --help' for more information.\n");
		exit(1);
	}

	return optind;
}


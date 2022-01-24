
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include "options.h"
#include "sergey-gru/cterm/cterm.h"

static void Options_Init(OPTS_Options_t *ptr);
static void PrintUsage(char *name);
static void PrintHelp(char *name);
static void PrintVersion(char *name);

typedef enum
{
	_OPTS_CMD_Version = 1001
} _OPTS_CMD_e;

OPTS_Options_t opts;
static const char *opts_short = ":hapdDnbestTzZ";
static struct option opts_long[] =
{

/*1*/  {"all",       no_argument,         0, 'a'},
/*2*/  {"path",      optional_argument,   0, 'p'},
/*3*/  {"dir",       optional_argument,   0, 'd'},
/*4*/  {"dirs",      optional_argument,   0, 'D'},
/*5*/  {"name",      optional_argument,   0, 'n'},
/*6*/  {"bname",     optional_argument,   0, 'b'},
/*7*/  {"ext",       optional_argument,   0, 'e'},
/*8*/  {"short",     optional_argument,   0, 's'},
/*9*/  {"tag",       optional_argument,   0, 't'},
/*10*/ {"tags",      optional_argument,   0, 'T'},
/*11*/ {"zero",      no_argument,         0, 'z'},
/*12*/ {"normalize", no_argument,         0, 'Z'},
/*0*/  {"help",      no_argument,         0, 'h'},
/*0*/  {"version",   no_argument,         0, _OPTS_CMD_Version},
       {0, 0, 0, 0}
};

static char *opts_desc[] =
{
/*1*/  "Output all variables. Equvalent -pdDnbestT",
/*2*/  "=<path> Output full path as <path> variable",
/*3*/  "=<dir> Output full directory as <dir> variable",
/*4*/  "=<dirs> Output path as <dirs> variable",
/*5*/  "=<name> Output path as <name> variable",
/*6*/  "=<bname> Output path as <bname> variable",
/*7*/  "=<ext> Output path as <ext> variable",
/*8*/  "=<short> Output path as <short> variable",
/*9*/  "=<tag> Output path as <tag> variable",
/*10*/ "=<tags> Output path as <tags> variable",
/*11*/ "Output \\0 character instead of \\n at the end of string",
/*12*/ "Normalize path before calculation"
/*0*/  "Print this help",
/*0*/  "Print this version",
};

static void Options_Init(OPTS_Options_t *opts)
{
	assert(opts != NULL);
	memset(opts, 0, sizeof(OPTS_Options_t));

	opts->o_alias_path  = "path";
	opts->o_alias_dir   = "dir";
	opts->o_alias_dirs  = "dirs";
	opts->o_alias_name  = "name";
	opts->o_alias_bname = "bname";
	opts->o_alias_ext   = "ext";
	opts->o_alias_short = "short";
	opts->o_alias_tag   = "tag";
	opts->o_alias_tags  = "tags";

	opts->ch_str_end = '\n';
}

int OPTS_ReadArgs(int argc, char **argv)
{
	Options_Init(&opts);

	opterr = 0;

	int c;
	int option_index = 0;
	while (1)
    {
		c = getopt_long(argc, argv, opts_short, opts_long, &option_index);

		/* Detect the end of the options. */
		if (c == -1)
			break;

		switch (c)
		{
			case 0:
				// Flag <opts_long[option_index].flag> setted equal <opts_long[option_index].val>
				break;

			case ':':
				// No required argument of option <optopt>
				fprintf(stderr, "No required argument of option -%c\n", (char)optopt);
				exit(1);
				break;

			case '?':
				// Unrecognized option <optopt>
				fprintf(stderr, "Unrecognized option -%c\n", (char)optopt);

				// Message has printed by getopt_long
				exit(1);
				break;

			default:
				exit(1);
				break;

			case 'h':
				PrintHelp(argv[0]);
				exit(0);
				break;

			case _OPTS_CMD_Version:
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
				break;

			case 'p': opts.o_path  = 1; break;
			case 'd': opts.o_dir   = 1; break;
			case 'D': opts.o_dirs  = 1; break;
			case 'n': opts.o_name  = 1; break;
			case 'b': opts.o_bname = 1; break;
			case 'e': opts.o_ext   = 1; break;
			case 's': opts.o_short = 1; break;
			case 't': opts.o_tag   = 1; break;
			case 'T': opts.o_tags  = 1; break;

			case 'z': opts.ch_str_end = '\0'; break;
			case 'Z': opts.o_norm  = 1; break;
		}
    }

	return optind;
}

static void PrintUsage(char *name)
{

	printf("Usage: %s -a <path> [<path2>...]\n", name);
	printf("Show all: %s -a <path> [<path2>...]\n", name);
	printf("Set variable: %s -p -Z <path> [<path2>...]\n", name);

	printf("%s", CT_EXAMPLE4);
	CT_PrintTable();
	CT_PrintTableRGB();
}
static void PrintHelp(char *name)
{
	PrintUsage(name);

}

static void PrintVersion(char *name)
{
	printf("Version 1.0\n");
}

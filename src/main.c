
#include <assert.h>
//#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "options.h"
#include "path.h"
#include "main.h"

// FUNCTIONS
static void CmdPathInfo(char *path);
static void Options_Init();
static int  SetOption(int opt, char *optarg);
static void PrintExplain(FILE *fstream);
static void PrintUsage(FILE *fstream);


static char opts_short[] = ":apdDnbestTzO";
static OPTS_OptionLong_t opts_long[] =
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
/*12*/  {"help",      no_argument,         0, OPTS_CMD_HELP},
/*13*/  {"version",   no_argument,         0, OPTS_CMD_VERSION},
/*14*/  {0, 0, 0, 0}
};
static const int opts_long_count = sizeof(opts_long) / sizeof(OPTS_OptionLong_t) - 1;

static OPTS_OptionDesc_t opts_desc[] =
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
static const int opts_desc_count = sizeof(opts_desc) / sizeof(OPTS_OptionDesc_t) - 1;

static OPTS_Settings_t set =
{
	opts_short,
	opts_long,
	opts_desc,
	80,
	"pathinfo",
	"1.0",
	PrintUsage,
	PrintExplain,
	SetOption
};

/// Struct for place opts value constants
AppOptions_t opts;


int main(int argc, char *argv[])
{
	Options_Init();

	int optind = OPTS_ReadOptions(argc, argv, &set);
	if (!opts.o_path &&
		!opts.o_dir &&
		!opts.o_dirs &&
		!opts.o_name &&
		!opts.o_bname &&
		!opts.o_ext &&
		!opts.o_short &&
		!opts.o_tag &&
		!opts.o_tags)
	{
		opts.o_path = 1;
		opts.o_optimize = 1;
	}

	// Reading non option arguments
	for (; optind < argc; optind++)
	{
		CmdPathInfo(argv[optind]);
		putchar(opts.ch_str_end);
	}

	return 0;
}

static void Options_Init()
{
	assert(opts_long_count == opts_desc_count);
	assert(opts_long[opts_long_count].name == 0);
	assert(opts_desc[opts_desc_count].desc == 0);

	memset(&opts, 0, sizeof(AppOptions_t));

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

static int SetOption(int opt, char *optarg)
{
	switch (opt)
	{
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

		case 'p': opts.o_path  = 1; if (optarg) opts.o_alias_path  = optarg; break;
		case 'd': opts.o_dir   = 1; if (optarg) opts.o_alias_dir   = optarg; break;
		case 'D': opts.o_dirs  = 1; if (optarg) opts.o_alias_dirs  = optarg; break;
		case 'n': opts.o_name  = 1; if (optarg) opts.o_alias_name  = optarg; break;
		case 'b': opts.o_bname = 1; if (optarg) opts.o_alias_bname = optarg; break;
		case 'e': opts.o_ext   = 1; if (optarg) opts.o_alias_ext   = optarg; break;
		case 's': opts.o_short = 1; if (optarg) opts.o_alias_short = optarg; break;
		case 't': opts.o_tag   = 1; if (optarg) opts.o_alias_tag   = optarg; break;
		case 'T': opts.o_tags  = 1; if (optarg) opts.o_alias_tags  = optarg; break;

		case 'z': opts.ch_str_end = '\0'; break;
		case 'O': opts.o_optimize  = 1; break;

		default:
			return 1;
	}

	return 0;
}

static void PrintUsage(FILE *fstream)
{
	fprintf(fstream, "Usage: %s [-a] [-O] [-pdDnbestTz...] PATH [PATH...]\n",
			set.prog_name);
}

static void PrintExplain(FILE *fstream)
{

}

void CmdPathInfo(char *path)
{
	if (opts.o_optimize)
	{
		PATH_Normalize(path);
	}

	if (opts.o_path)  printf("%s=%s%c", opts.o_alias_path,  path, opts.ch_str_end);
	if (opts.o_dir)   printf("%s=%s%c", opts.o_alias_dir,   path, opts.ch_str_end);
	if (opts.o_dirs)  printf("%s=%s%c", opts.o_alias_dirs,  path, opts.ch_str_end);
	if (opts.o_name)  printf("%s=%s%c", opts.o_alias_name,  path, opts.ch_str_end);
	if (opts.o_bname) printf("%s=%s%c", opts.o_alias_bname, path, opts.ch_str_end);
	if (opts.o_ext)   printf("%s=%s%c", opts.o_alias_ext,   path, opts.ch_str_end);
	if (opts.o_short) printf("%s=%s%c", opts.o_alias_short, path, opts.ch_str_end);
	if (opts.o_tag)   printf("%s=%s%c", opts.o_alias_tag,   path, opts.ch_str_end);
	if (opts.o_tags)  printf("%s=%s%c", opts.o_alias_tags,  path, opts.ch_str_end);

}


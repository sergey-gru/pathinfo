
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sergey-gru/cterm/cterm.h>

#include "options.h"
#include "help.h"
#include "path.h"
#include "main.h"

// FUNCTIONS
static void CmdPathInfo(char *path);
static void InitOptions();
static int MAIN_SetOption(int opt, char *optarg);

/// Struct for place opts value constants
MAIN_AppOptions_t opts;

int main(int argc, char *argv[])
{
	InitOptions(&opts);

	HLP_Init();
	int optind = OPTS_ReadOptions(argc, argv, &HLP_set, MAIN_SetOption);

	char opt_count =
		opts.o_path +
		opts.o_dir +
		opts.o_dirs +
		opts.o_name +
		opts.o_bname +
		opts.o_ext +
		opts.o_sname +
		opts.o_tag +
		opts.o_tags;

	switch (opt_count)
	{
		case 0:
			opts.o_path = 1;
			opts.o_optimize = 1;
			opts.out_type = MAIN_OutType_TEXT;
			break;

		case 1:
			opts.out_type = MAIN_OutType_TEXT;
			break;

		default:
			opts.out_type = MAIN_OutType_HTABLE;
			break;
	}

	// Checking error count of args
	if (optind >= argc) return 1;

	// Reading non option arguments
	for (; optind < argc; optind++)
	{
		CmdPathInfo(argv[optind]);
	}

	return 0;
}


static void InitOptions(MAIN_AppOptions_t *opts)
{
	assert(opts != NULL);

	memset(opts, 0, sizeof(*opts));

	opts->o_alias_path  = "path";
	opts->o_alias_dir   = "dir";
	opts->o_alias_dirs  = "dirs";
	opts->o_alias_name  = "name";
	opts->o_alias_bname = "bname";
	opts->o_alias_ext   = "ext";
	opts->o_alias_sname = "short";
	opts->o_alias_tag   = "tag";
	opts->o_alias_tags  = "tags";

	opts->ch_str_end = '\n';
}

static int MAIN_SetOption(int opt, char *optarg)
{
	switch (opt)
	{
		// all << tag << dir,name << path
		case 'a':
			opts.o_path  = 1;
			opts.o_dir   = 1;
			opts.o_dirs  = 1;
			opts.o_name  = 1;
			opts.o_bname = 1;
			opts.o_ext   = 1;
			opts.o_sname = 1;
			opts.o_tag   = 1;
			opts.o_tags  = 1;

			opts.p_path  = 1;
			opts.p_dir   = 1;
			opts.p_tag   = 1;
			opts.p_name  = 1;
			break;

		case 'p':
			opts.o_path = 1;
			if (optarg) opts.o_alias_path = optarg;
			break;

		// dir/name << path
		case 'd':
			opts.o_dir = 1;
			opts.p_path = 1;
			if (optarg) opts.o_alias_dir = optarg;
			break;
		case 'n':
			opts.o_name = 1;
			opts.p_path = 1;
			if (optarg) opts.o_alias_name  = optarg;
			break;

		// bname.ext << name << path
		// sname.tag << name << path
		case 'b':
			opts.o_bname = 1;
			opts.p_path = 1;
			opts.p_name = 1;
			if (optarg) opts.o_alias_bname = optarg;
			break;
		case 'e':
			opts.o_ext = 1;
			opts.p_path = 1;
			opts.p_name = 1;
			if (optarg) opts.o_alias_ext   = optarg;
			break;
		case 's':
			opts.o_sname = 1;
			opts.p_path = 1;
			opts.p_name = 1;
			if (optarg) opts.o_alias_sname = optarg;
			break;
		case 't':
			opts.o_tag = 1;
			opts.p_path = 1;
			opts.p_name = 1;
			if (optarg) opts.o_alias_tag   = optarg;
			break;

		// dirs << dir << path
		case 'D':
			opts.o_dirs = 1;
			opts.p_path = 1;
			opts.p_dir = 1;
			if (optarg) opts.o_alias_dirs = optarg;
			break;

		// tags << tag << name << path
		case 'T':
			opts.o_tags = 1;
			opts.p_path = 1;
			opts.p_name = 1;
			opts.p_tag = 1;
			if (optarg) opts.o_alias_tags  = optarg;
			break;

		case 'z':
			opts.ch_str_end = '\0';
			break;

		case 'O':
			opts.o_optimize  = 1;
			break;

		case 'o':
			if (strcmp(optarg, "hash"))
			{
				opts.out_type = MAIN_OutType_HTABLE;
			}
			else if (strcmp(optarg, "var"))
			{
				opts.out_type = MAIN_OutType_VARS;
			}
			else if (strcmp(optarg, "text"))
			{
				opts.out_type = MAIN_OutType_TEXT;
			}
			else
			{
				fprintf(stderr, "Error: Unrecognized output type %s\n", optarg);
				exit(1);
			}
			break;

		default:
			return OPTS_CMD_ERR;
	}

	return OPTS_CMD_NEXT;
}

static void PrintBegin()
{
	switch (opts.out_type)
	{
		default:
		case MAIN_OutType_TEXT:
			break;

		case MAIN_OutType_VARS:
			putchar('\n');
			break;

		case MAIN_OutType_HTABLE:
			putchar('(');
			break;
	}
}

static void PrintEnd()
{
	switch (opts.out_type)
	{
		default:
		case MAIN_OutType_TEXT:
			putchar('\n');
			break;

		case MAIN_OutType_VARS:
			putchar('\n');
			break;

		case MAIN_OutType_HTABLE:
			putchar(')');
			break;
	}
}

static void PrintKeyVal( const char *key, char *val, size_t len)
{
	switch (opts.out_type)
	{
		case MAIN_OutType_VARS:
			printf("%s=", key);
			fwrite(val, 1, len, stdout);
			putchar(opts.ch_str_end);
			break;

		default:
		case MAIN_OutType_HTABLE:
			printf("['%s']='", key);
			fwrite(val, 1, len, stdout);
			printf("' ");
			break;

		case MAIN_OutType_TEXT:
			fwrite(val, 1, len, stdout);
			if (opts.ch_str_end == 0) putchar(opts.ch_str_end);
			break;
	}
}










static void CmdPathInfo(char *path)
{
	size_t len;

	// Optimize
	if (opts.o_optimize) len = PATH_OptimizePath(path);
	else len = PATH_OptimizeSlash(path);

	PATH_PathInfo_t pinf = {0, 0};
	PATH_NameInfo_t ninf = {0, 0};
	char *dirs = 0;
	char *tags = 0;

	// Parse
	if (opts.p_path)  PATH_ParsePath (path, len,     &pinf);
	if (opts.p_name)  PATH_ParseName (pinf.name.str, pinf.name.len, &ninf);
	if (opts.p_dir)   PATH_ParseDir  (pinf.dir.str,  pinf.dir.len,  &dirs);
	if (opts.p_tag)   PATH_ParseTag  (ninf.tag.str,  ninf.tag.len,  &tags);

	// Outputs
	PrintBegin();
	if (opts.o_path)  PrintKeyVal(opts.o_alias_path,  path, len);
	if (opts.o_dir)   PrintKeyVal(opts.o_alias_dir,   pinf.dir.str,   pinf.dir.len);
	if (opts.o_name)  PrintKeyVal(opts.o_alias_name,  pinf.name.str,  pinf.name.len);
	if (opts.o_ext)   PrintKeyVal(opts.o_alias_ext,   ninf.ext.str,   ninf.ext.len);
	if (opts.o_bname) PrintKeyVal(opts.o_alias_bname, ninf.bname.str, ninf.bname.len);
	if (opts.o_sname) PrintKeyVal(opts.o_alias_sname, ninf.sname.str, ninf.sname.len);
	if (opts.o_tag)   PrintKeyVal(opts.o_alias_tag,   ninf.tag.str,   ninf.tag.len);
	if (opts.o_dirs)  PrintKeyVal(opts.o_alias_dirs,  dirs,           strlen(dirs));
	if (opts.o_tags)  PrintKeyVal(opts.o_alias_tags,  tags,           strlen(tags));
	PrintEnd();
}


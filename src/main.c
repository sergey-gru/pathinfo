
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sergey-gru/cterm/cterm.h>
#include <glib-2.0/glib.h>

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

static void PrintStringCovered(const char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '\\') putchar('\\');

		putchar(*str);
		str++;
	}
}

static void PrintMemCovered(const char *str, size_t len)
{
	for (int i = 0; i < len; i++)
	{
		if (str[i] == '\'' || str[i] == '\\') putchar('\\');
		putchar(str[i]);
	}
}

static void PrintMemCovered2(PATH_SubString_t *v)
{
	char *str = v->str;
	size_t len = v->len;

	PrintMemCovered(str, len);
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

static void PrintKeyVal(const char *key, const char *val, size_t len)
{
	assert(val);

	switch (opts.out_type)
	{
		case MAIN_OutType_VARS:
			printf("%s=", key);
			PrintMemCovered(val, len);
			//fwrite(val, 1, len, stdout);
			putchar(opts.ch_str_end);
			break;

		default:
		case MAIN_OutType_HTABLE:
			printf("['%s']='", key);
			PrintMemCovered(val, len);
			//fwrite(val, 1, len, stdout);
			printf("' ");
			break;

		case MAIN_OutType_TEXT:
			PrintMemCovered(val, len);
			//fwrite(val, 1, len, stdout);
			if (opts.ch_str_end == 0) putchar(opts.ch_str_end);
			break;
	}
}

static void PrintKeyVal2(const char *key, PATH_SubString_t *value)
{
	assert(value);

	char *val  = value->str;
	size_t len = value->len;

	PrintKeyVal(key, val, len);
}

static void PrintKeyValGArray(const char *key, const GArray *values)
{
	assert(values);

	PATH_SubString_t v;

	printf("['%s']='", key);

	for (int i = 0; i < values->len; i++)
	{
		v = g_array_index(values, PATH_SubString_t, i);
		PrintMemCovered2(&v);
		putchar(' ');
	}

	printf("'");


}








static void CmdPathInfo(char *path)
{
	size_t len;

	// Optimize
	if (opts.o_optimize) len = PATH_OptimizePath(path);
	else len = PATH_OptimizeSlash(path);

	PATH_PathInfo_t pinf = {0, 0};
	PATH_NameInfo_t ninf = {0, 0};

	GArray *dirs = g_array_new(0, 0, sizeof(PATH_SubString_t));
	GArray *tags = g_array_new(0, 0, sizeof(PATH_SubString_t));

	if (!dirs && !tags) exit(1);

	// Parse
	if (opts.p_path)  PATH_ParsePath (path, len,     &pinf);
	if (opts.p_name)  PATH_ParseName (pinf.name.str, pinf.name.len, &ninf);
	if (opts.p_dir)   PATH_ParseDir  (pinf.dir.str,  pinf.dir.len,  dirs);
	if (opts.p_tag)   PATH_ParseTag  (ninf.tag.str,  ninf.tag.len,  tags);


	// Outputs
	PrintBegin();
	if (opts.o_path)  PrintKeyVal(opts.o_alias_path,  path, len);
	if (opts.o_dir)   PrintKeyVal2(opts.o_alias_dir,   &pinf.dir);
	if (opts.o_name)  PrintKeyVal2(opts.o_alias_name,  &pinf.name);
	if (opts.o_ext)   PrintKeyVal2(opts.o_alias_ext,   &ninf.ext);
	if (opts.o_bname) PrintKeyVal2(opts.o_alias_bname, &ninf.bname);
	if (opts.o_sname) PrintKeyVal2(opts.o_alias_sname, &ninf.sname);
	if (opts.o_tag)   PrintKeyVal2(opts.o_alias_tag,   &ninf.tag);
	if (opts.o_dirs)  PrintKeyValGArray(opts.o_alias_dirs,  dirs);
	if (opts.o_tags)  PrintKeyValGArray(opts.o_alias_tags,  tags);
	PrintEnd();

	g_array_free(dirs, 1);
	g_array_free(tags, 1);
}


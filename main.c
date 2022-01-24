
//#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "options.h"
#include "path.h"
#include "main.h"

void PathInfo(char *path);

int main(int argc, char *argv[])
{
	int optind = OPTS_ReadArgs(argc, argv);

	// Reading non option arguments
	for (; optind < argc; optind++)
	{
		PathInfo(argv[optind]);
		putchar(opts.ch_str_end);
	}

	return 0;
}

void PathInfo(char *path)
{
	if (opts.o_norm)
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


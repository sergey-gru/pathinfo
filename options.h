#ifndef _OPTIONS_H_
#define _OPTIONS_H_

typedef struct
{
	// <dir>/<name> <dirs[]>=<dir>
	// name=<bname>.<ext>
	// name=<short>.<tag> <tags[]>=<tag>
	unsigned o_path  :1;
	unsigned o_dir   :1;
	unsigned o_dirs  :1;
	unsigned o_name  :1;
	unsigned o_bname :1;
	unsigned o_ext   :1;
	unsigned o_short :1;
	unsigned o_tag   :1;
	unsigned o_tags  :1;

	// special modes
	unsigned o_norm :1; // normalize path before all calculations
	char ch_str_end; // endstring character

	// aliases for variables
	char *o_alias_path;
	char *o_alias_dir;
	char *o_alias_dirs;
	char *o_alias_name;
	char *o_alias_bname;
	char *o_alias_ext;
	char *o_alias_short;
	char *o_alias_tag;
	char *o_alias_tags;

} OPTS_Options_t;

/// Struct for place opts value constants
extern OPTS_Options_t opts;

/// \brief Reads command line arguments. Calls help, version, usage and exit()
/// @return: Returns index of argv of the first operand folowing by last options or --
extern int OPTS_ReadArgs(int argc, char **argv);

#endif // _OPTIONS_H_

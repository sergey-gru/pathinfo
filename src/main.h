#ifndef _MAIN_H_
#define _MAIN_H_

/*!
    \defgroup PINF
    \brief interface of main program
*/

/// Set of posibility output types
typedef enum
{
	MAIN_OutType_TEXT = 0,
	MAIN_OutType_VARS,
	MAIN_OutType_HTABLE

} MAIN_OutType_e;

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
	unsigned o_sname :1;
	unsigned o_tag   :1;
	unsigned o_tags  :1;

	// flags to parse
	unsigned p_path  :1;
	unsigned p_dir   :1;
	unsigned p_name  :1;
	unsigned p_tag   :1;

	// special modes
	unsigned o_optimize :1; // normalize path before all calculations
	char     ch_str_end;    // endstring character

	// aliases for variables
	char *o_alias_path;
	char *o_alias_dir;
	char *o_alias_dirs;
	char *o_alias_name;
	char *o_alias_bname;
	char *o_alias_ext;
	char *o_alias_sname;
	char *o_alias_tag;
	char *o_alias_tags;

	MAIN_OutType_e out_type;
	unsigned f_alias :1;




} MAIN_AppOptions_t;

extern MAIN_AppOptions_t opts;

#endif // _MAIN_H_

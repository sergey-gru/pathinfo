#ifndef _OPTIONS_H_
#define _OPTIONS_H_

#include <stdio.h>
#include <getopt.h>

#define OPTS_ARG_NO  no_argument
#define OPTS_ARG_OPT optionsl_argument
#define OPTS_ARG_REQ required_argument

typedef struct option OPTS_OptionLong_t;

typedef enum
{
	_OPTS_CMD_BEGIN = 256,
	OPTS_CMD_VERSION,
	OPTS_CMD_HELP,
	OPTS_CMD_FREE
} OPTS_CMD_e;

typedef struct
{
	char *arg;
	char *desc;

} OPTS_OptionDesc_t;

typedef struct
{
	char              *opts_short; ///< String of short options. Ex: ":abcdhz"
	OPTS_OptionLong_t *opts_long;  ///< null struct terminated array of long options
	OPTS_OptionDesc_t *opts_desc;  ///< null struct terminated array of descriptions

	int terminal_width;

	char *prog_name;
	char *prog_version;

	void (*FPrintUsage)(FILE *fstream);
	void (*FPrintExplain)(FILE *fstream);
	int  (*FSetOption)(int opt, char *optarg);

} OPTS_Settings_t;

/// \brief Reads command line arguments. Calls help, version, usage and exit()
/// @return: Returns index of argv of the first operand folowing by last options or --
extern int OPTS_ReadOptions(int argc, char **argv, const OPTS_Settings_t *sett);
int _OPTS_PrintParagraph(const char *str,
						int align_first,
						int align,
						int max_width,
						unsigned int printed);

#endif // _OPTIONS_H_

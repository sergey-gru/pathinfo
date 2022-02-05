#ifndef _OPTIONS_H_
#define _OPTIONS_H_

#include <stdio.h>
#include <getopt.h>

typedef enum
{
	OPTS_CMD_NEXT = 0,
	_OPTS_CMD_BEGIN = 255,
	OPTS_CMD_ERR,
	OPTS_CMD_VERSION,
	OPTS_CMD_HELP,
	OPTS_CMD_USAGE,
	OPTS_CMD_free
} OPTS_CMD_e;

typedef struct
{
	char *arg;
	char *desc;

} OPTS_OptionDesc_t;

typedef struct
{
	char              *opts_short; ///< String of short options. Ex: ":abcdhz"
	struct option     *opts_long;  ///< null struct terminated array of long options
	OPTS_OptionDesc_t *opts_desc;  ///< null struct terminated array of descriptions
	unsigned int       terminal_width;
	unsigned int       min_args_count;

	const char *prog_name;
	const char *prog_version;
	const char *str_usage;
	const char *str_explain;

} OPTS_Settings_t;

/// \brief Reads command line arguments. Calls help, version, usage and exit()
/// @return: Returns index of argv of the first operand folowing by last options or --
int OPTS_ReadOptions(int argc,
						char **argv,
						const OPTS_Settings_t *sett,
						int (*FSetOption)(int opt, char *optarg));

int _OPTS_PrintParagraph(const char *str,
						int align_first,
						int align,
						int max_width,
						unsigned int printed);

#endif // _OPTIONS_H_

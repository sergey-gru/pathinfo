
#include <assert.h>
#include "main.h"
#include "help.h"

static
char opts_short[] = ":apdDnbestTzO";

static
struct option opts_long[] =
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
/*11*/  {"out-type",  required_argument,   0, 'o'},
/*10*/  {"zero",      no_argument,         0, 'z'},
/*11*/  {"optimize",  no_argument,         0, 'O'},
/*12*/  {"help",      no_argument,         0, OPTS_CMD_HELP},
/*13*/  {"version",   no_argument,         0, OPTS_CMD_VERSION},
/*14*/  {0, 0, 0, 0}
};

static
OPTS_OptionDesc_t opts_desc[] =
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
/*10*/  {"type",  "Choose an output type=var|hash|text. 'text' is only for one output option"},
/*10*/  {0,       "Output \\0 character instead of \\n at the end of string"},
/*11*/  {0,       "Normalize path before calculation"},
/*12*/  {0,       "Print this help"},
/*13*/  {0,       "Print version of program"},
/*14*/  {0, 0}
};

static
char str_usage[] =
"  pathinfo [-a] [-O] [-pdDnbestTz...] PATH [PATH...]\n"
"Return:\n"
"  pathinfo PATH\n";

/*"  path='<path>'"
	"  dir='<path>'"
	"  dirs='<path>'"
	"  path='<path>'"
	"  path='<path>'"

	"  <optimized path>"
*/

static
char str_explain[] =
"";

OPTS_Settings_t HLP_set =
{
	opts_short,
	opts_long,
	opts_desc,
	80,
	1,
	"pathinfo",
	"1.0",
	str_usage,
	str_explain
};

void HLP_Init()
{
	const int opts_long_count = sizeof(opts_long) / sizeof(struct option) - 1;
	const int opts_desc_count = sizeof(opts_desc) / sizeof(OPTS_OptionDesc_t) - 1;

	assert(opts_long_count == opts_desc_count);
	assert(opts_long[opts_long_count].name == 0);
	assert(opts_desc[opts_desc_count].desc == 0);
}


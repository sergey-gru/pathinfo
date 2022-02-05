
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../compile.h"
#include "../path.h"

static int TEST_PATH_Optimize(void);

typedef struct
{
	const char *task;
	const char *assert;

} TEST_PATH_Note_t;

int main(void)
{
    TEST_PATH_Optimize();

    return 0;
}


// Delimiters
#define D0 ""
#define D1 "/"
#define D2 "\\"
// Names
#define N0 "."
#define N1 ".."
#define N2 "abc"

static TEST_PATH_Note_t TEST_PATH_Optimize_arr[] =
{
	// Here are posibly combinations of TASK

	// D D
	{"",   ""},		// D0 D0         ATTENTION
	{"/",  "/"},	// D0 D1
	{"\\", "/"},	// D0 D2

	{"/",   "/"},	// D1 D0
	{"//",  "/"},	// D1 D1
	{"/\\", "/"},	// D1 D2

	{"\\",   "/"},	// D2 D0
	{"\\/",  "/"},	// D2 D1
	{"\\\\", "/"},	// D2 D2

	// D N
	{".",   "."},		// D0 N0
	{"..",  ".."},		// D0 N1
	{"abc", "abc"},		// D0 N2

	{"/.",   "/"},		// D1 N0
	{"/..",  "/.."},	// D1 N1
	{"/abc", "/abc"},	// D1 N2

	{"\\.",   "/"},		// D2 N0
	{"\\..",  "/.."},	// D2 N1
	{"\\abc", "/abc"},	// D2 N2

	// N D
	{".",   "."},		// N0 D0
	{"./",  "."},		// N0 D1
	{".\\", "."},		// N0 D2

	{"..",   ".."},		// N1 D0
	{"../",  ".."},		// N1 D1
	{"..\\", ".."},		// N1 D2

	{"abc",   "abc"},	// N1 D0
	{"abc/",  "abc"},	// N1 D1
	{"abc\\", "abc"},	// N1 D2

	// D0 - no using
	// D2 - no using

// Delimiters
#define D1 "/"
// Names
#define N0 "."
#define N1 ".."
#define N2 "abc"

	// D N D
	{"/./",   "/"},		// D1 N0 D1				ATTENTION
	{"/../",  "/.."},	// D1 N1 D1
	{"/abc/", "/abc"},	// D1 N2 D1

	// N D N
	{"./.",     "."},			// N0 D1 N0
	{"./..",    ".."},			// N0 D1 N1
	{"./abc",   "abc"},			// N0 D1 N2

	{"../.",    ".."},			// N1 D1 N0
	{"../..",   "../.."},		// N1 D1 N1
	{"../abc",  "../abc"},		// N1 D1 N2

	{"abc/.",   "abc"},			// N2 D1 N0
	{"abc/..",  "."},			// N2 D1 N1       ATTENTION
	{"abc/abc", "abc/abc"},		// N2 D1 N2

	// N D N D
	{"././",   "."},			// N0 D1 N0 D1
	{"./../",  ".."},			// N0 D1 N1 D1
	{"./abc/", "abc"},			// N0 D1 N2 D1

	{".././",   ".."},			// N1 D1 N0 D1
	{"../../",  "../.."},		// N1 D1 N1 D1
	{"../abc/", "../abc"},		// N1 D1 N2 D1

	{"abc/./",   "abc"},		// N2 D1 N0 D1
	{"abc/../",  "."},			// N2 D1 N1 D1
	{"abc/abc/", "abc/abc"},		// N2 D1 N2 D1

	// D N D N
	{"/./.",   "/"},		// D1 N0 D1 N0       ATTENTION
	{"/./..",  "/.."},		// D1 N0 D1 N1
	{"/./abc", "/abc"},		// D1 N0 D1 N2

	{"/../.",   "/.."},		// D1 N1 D1 N0
	{"/../..",  "/../.."},		// D1 N1 D1 N1
	{"/../abc", "/../abc"},	// D1 N1 D1 N2

	{"/abc/.",   "/abc"},		// D1 N2 D1 N0
	{"/abc/..",  "/"},			// D1 N2 D1 N1         ATTENTION
	{"/abc/abc", "/abc/abc"},	// D1 N2 D1 N2

	// Test back slashes
	{"/\\/\\///", "/"}, ///< Reduce slash
	{"\\/\\//\\", "/"}, ///< Reduce slash

	// Random tests
	{"abc/abc/..", "abc"},
	{"../abc/..", ".."},
	{"/../../abc/..//abc2/", "/../../abc2"},

	{0, 0} //Terminator
};

static int TEST_PATH_Optimize(void)
{
    printf("%s():\n", __FUNCTION__);

    TEST_PATH_Note_t *arr = TEST_PATH_Optimize_arr;
    const int count = sizeof(TEST_PATH_Optimize_arr) / sizeof(TEST_PATH_Note_t) - 1;

	static char buf[256];
	int err_count = 0;
	for (int i = 0; arr[i].task != NULL; i++)
    {
        printf("%d/%d.\n", i + 1, count);
        printf("In:     \"%s\"\n", arr[i].task);
		printf("Assert: \"%s\"\n", arr[i].assert);

		strncpy(buf, arr[i].task, sizeof(buf));
        PATH_OptimizePath(buf);

        printf("Result: \"%s\"\n", buf);

        if (strcmp(buf, arr[i].assert) == 0) printf("OK\n\n");
        else
        {
            printf("ERR\n\n");
            err_count++;
        }
    }

    fprintf(stderr, "Errors: %d/%d\n", err_count, count);

    return err_count;
}


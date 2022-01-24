
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../compile.h"
#include "../path.h"

static int test_PATH_Normalize(void);


int test_path(void)
{
    int res = test_PATH_Normalize();

    return res;
}



static int test_PATH_Normalize(void)
{
	static const char *arr[] =
	{
		"",
		"",

		"////",
		"/",

		"./",
		"",

		"../",
		"..",

		"..",
		"..",

		"/..",
		"/..",

		"/../",
		"/..",

		"abc/..",
		"",

		"/abc/..",
		"/",

		"/abc/../",
		"/",

		"abc/abc/..",
		"abc",

		"../abc/..",
		"..",

		"/../../abc/..//abc2/",
		"/../../abc2",

		0 //Terminator
	};

    printf("%s():\n", __FUNCTION__);

	size_t len = (sizeof(arr) - 1) / sizeof(arr[0]);
	assert(len > 0);

	int count = len / 2;

	char buf[256];
	int res = 0;
	for (int i = 0; i < len; i+=2)
    {
        printf("%d/%d)\n", i/2 + 1, count);
        printf("In:    \"%s\"\nCheck: \"%s\"\n", arr[i], arr[i + 1]);

		strncpy(buf, arr[i], sizeof(buf));
        PATH_Normalize(buf);
        printf("Res:   \"%s\"\n", buf);

        if (strcmp(buf, arr[i + 1]) == 0)
        {
            printf("\e[32mOK\e[0m\n\n");
        }
        else
        {
            printf("\e[31mERR\e[0m\n\n");
            res++;
        }
    }

    printf("Errors: %d\n", res);

    return res;
}


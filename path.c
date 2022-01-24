
#include <assert.h>
#include <string.h>
#include <stddef.h>
#include "path.h"

size_t PATH_Normalize(char *path)
{
    assert(path != NULL);

    char *ptr_w = path;
    char *ptr_r;
    unsigned short lvl = 0; //Count of normal "abc" like folders in the path
	char f_slash_need = 0;  //Flag is 1 - if pointer ptr_w on end position of dir name
							//0 - after slash

	if (path[0] == '/' || path[0] == '\\')
	{
		path[0] = '/';
		ptr_w++;
	}

	ptr_r = strtok(ptr_w, "/\\");
    while (ptr_r != NULL)
    {
        if (strcmp(ptr_r, ".") == 0) ;
        else if (strcmp(ptr_r, "..") == 0)
        {
        	if (lvl > 0)
			{
				// Go back, stay at position /^abc
				ptr_w -= 2;
				if (lvl > 1) while (ptr_w[-1] != '/') ptr_w--;
				else while (ptr_w[-1] != '/' && ptr_w > path) ptr_w--;

				f_slash_need = 0;
				lvl--;
			}
			else
			{
				// Keep /..
				if (f_slash_need)
				{
					*ptr_w = '/';
					ptr_w++;
				}

				*ptr_w = '.';
				ptr_w++;
				*ptr_w = '.';
				ptr_w++;

				f_slash_need = 1;
				//memcpy(ptr_w, ptr_r, 2);
				//ptr_w += 2;
			}
        }
        else
        {
            // Keep "/abc"
            if (f_slash_need)
			{
				*ptr_w = '/';
				ptr_w++;
			}

            int len = strlen(ptr_r);
			memmove(ptr_w, ptr_r, len);
            ptr_w += len;

            lvl++;
            f_slash_need = 1;
        }

        ptr_r = strtok(NULL, "/\\");
    }

	if (!f_slash_need && ptr_w > path + 1) ptr_w--;

	//Ending
	*ptr_w = '\0';

	return ptr_w - path;
}


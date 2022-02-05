
#include <assert.h>
#include <string.h>
#include <stddef.h>
#include "path.h"

#define memzero_ptr(ptr) memset(ptr,  0, sizeof(*ptr))
#define memzero_arr(arr) memset(arr,  0, sizeof(arr))
#define memzero_t(obj)   memset(&obj, 0, sizeof(obj))

size_t PATH_OptimizePath(char *path)
{
    assert(path != NULL);
    static char delims[] = "/\\";

    char *ptr_w = path;
    char *ptr_r;
    unsigned short lvl = 0; // Count of normal "abc" like folders in the path
	char f_slash_need = 0;  // Flag is 1 - if pointer ptr_w on end position of dir name
							//      is 0 - after slash

	// It's only one case with "" result
	if ( path[0] == 0 ) return 0;

	if (path[0] == '/' || path[0] == '\\')
	{
		path[0] = '/';
		ptr_w++;
	}

	ptr_r = strtok(ptr_w, delims);
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
				//memcpy(ptr_w, ptr_r, 2);
				//ptr_w += 2;

				f_slash_need = 1;
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

        ptr_r = strtok(NULL, delims);
    }

	if (ptr_w >= path + 2)
	{
		// Deleting end slash
		if (!f_slash_need) ptr_w--;
	}

	if (ptr_w == path)
	{
		*ptr_w = '.';
		ptr_w++;
	}

	// Set ending
	*ptr_w = '\0';

	return ptr_w - path;
}

size_t PATH_OptimizeSlash(char *path)
{
	assert(path != NULL);

	char *ptr = path;
	while ( (ptr = strchr(ptr, '\\')) )
		*ptr = '/';

	return strlen(path);
}

static
char * memrchr(const char *src, int ch, size_t len)
{
	for (const char *ptr = src + len; ptr >= src; ptr--)
		if (*ptr == ch)
			return (char*)ptr;

	return NULL;
}

void PATH_ParsePath(const char *path, size_t len, PATH_PathInfo_t *inf)
{
	assert(inf != NULL);

	memzero_ptr(inf);

	char *ptr = memchr(path, '/', len);
	if (ptr == NULL)
	{
		inf->name.str = (char *)path;
		inf->name.len = len;
	}
	else
	{
		inf->dir.str = (char *)path;
		inf->dir.len = ptr - path;
		inf->name.str = ptr + 1;
		inf->name.len = len - inf->dir.len - 1;
	}
}

void PATH_ParseName(const char *name, size_t len, PATH_NameInfo_t *inf)
{
	assert(inf != NULL);
	assert(name != NULL);

	memzero_ptr(inf);
	if (len == 0) return;

	char *ptr = memrchr(name, '.', len);
	if (ptr != NULL)
	{
		inf->bname.str = (char *)name;
		inf->bname.len = ptr - name;
		inf->ext.str = ptr + 1;
		inf->ext.len = len - inf->bname.len - 1;
	}

	ptr = memchr(name, '.', len);
	if (ptr != NULL)
	{
		inf->sname.str = (char *)name;
		inf->sname.len = ptr - name;
		inf->tag.str = ptr + 1;
		inf->tag.len = len - inf->bname.len - 1;
	}
}


void PATH_ParseTag(const char *tag, size_t len, char **out_tags)
{
	assert(tag != NULL);
	assert(out_tags != NULL);

	char *ptr = memchr(tag, '.', len);
	while (ptr != NULL)
	{


		ptr++;
		ptr = memchr(ptr, '.', len - (ptr - tag));
	}





	*out_tags = tag;

}

void PATH_ParseDir(const char *dir,  size_t len, char **out_dirs)
{
	assert(dir != NULL);
	assert(out_dirs != NULL);

	*out_dirs = dir;
}


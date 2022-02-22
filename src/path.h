#ifndef _PATH_H_
#define _PATH_H_

#include <glib.h>

/*!
    \defgroup PATH
    \brief Is the main PathINFo functions
    @{
*/

typedef struct
{
    char *str;
    size_t len;
} PATH_SubString_t;

typedef struct
{
	PATH_SubString_t bname;
	PATH_SubString_t ext;
	PATH_SubString_t sname;
	PATH_SubString_t tag;

} PATH_NameInfo_t;

typedef struct
{
	//char *path;
	//size_t path_len;

	PATH_SubString_t dir;
	PATH_SubString_t name;

	//PATH_SubString_t bname;
	//PATH_SubString_t ext;

	//PATH_SubString_t sname;
	//PATH_SubString_t tag;

	//int dirs_count;
	//int tags_count;

} PATH_PathInfo_t;

/// \brief Fills the structure PathInfo_t with \param[path]
void PATH_GetPathInfo(PATH_PathInfo_t *ptr, const char *path);


/*!
	\brief Optimize @path, always reduce length.
	The function optimizes
	\param[path] Buffer with input path. Output is here too. The function always makes path shorter or equal length
	\return length of new path (buffer size must be more 1 byte for '\0')
*/
size_t PATH_OptimizePath(char *path);
size_t PATH_OptimizeSlash(char *path);

void PATH_ParsePath(const char *path, size_t len, PATH_PathInfo_t *inf);
void PATH_ParseName(const char *name, size_t len, PATH_NameInfo_t *inf);
void PATH_ParseTag (const char *tag,  size_t len, GArray *out_tags);
void PATH_ParseDir (const char *dir,  size_t len, GArray *out_dirs);

int PATH_GoUp(char *path, char flags);

/*! @} */

#endif // _PATH_H_

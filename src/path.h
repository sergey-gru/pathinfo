#ifndef _PATH_H_
#define _PATH_H_

typedef struct
{
    short base;
    short len;
} PATH_Fragment_t;

typedef struct
{
    short path_len;
    short dir_len;

    PATH_Fragment_t ext;
    PATH_Fragment_t ext_full;
    PATH_Fragment_t base_name;

} PATH_PathInfo_t;

/// Fill the structure PathInfo_t with @path
void PATH_GetPathInfo(PATH_PathInfo_t *ptr, const char *path);

/// \brief Normalize @path, always reduce length.
/// @return: length of new path
size_t PATH_Normalize(char *path);
int    PATH_GoUp(char *path, char flags);
short  PATH_GetFileName(const char *path);


#endif // _PATH_H_

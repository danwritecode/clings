#ifndef WINDIRENT_H
#define WINDIRENT_H
#define DIR int

#include <string.h>
#include <stdlib.h>
#include <fileapi.h>
#include <windows.h>
struct dirent {
	size_t d_ino;
	int d_type;
	char *d_name;

};
int alphasort(const struct dirent **a, const struct dirent **b);
int scandir(const char *path, struct dirent ***namelist, void *unused, int (*compar)(const struct dirent **, const struct dirent **));
#endif
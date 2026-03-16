#include "windirent.h"

const int DIR_TYPE_CODE = 4;

int alphasort(const struct dirent **a, const struct dirent **b) {
	return strcoll((*a)->d_name,(*b)->d_name);
}

int scandir(
	const char *path, 
	struct dirent ***namelist, 
	void *unused, 
	int (*compar)(const struct dirent **, const struct dirent **)
) {
	size_t nmsize = sizeof(struct dirent);
	int index = 0;
	**namelist = malloc(nmsize);
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile(path,&FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) return -1;
	(*namelist)[0]->d_ino = FindFileData.dwFileAttributes;
	(*namelist)[0]->d_name = FindFileData.cFileName;
	if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) (*namelist)[0]->d_type = DIR_TYPE_CODE;
	else (*namelist)[0]->d_type = 0;
	while(FindNextFile(hFind, &FindFileData)) {
		index++;
		**namelist = realloc(namelist, nmsize + sizeof(struct dirent));
		(*namelist)[index]->d_ino = FindFileData.dwFileAttributes;
		(*namelist)[index]->d_name = FindFileData.cFileName;
		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) (*namelist)[index]->d_type = DIR_TYPE_CODE;
		else (*namelist)[index]->d_type = 0;
	}
	qsort(**namelist, index+1, sizeof(struct dirent), alphasort);
	FindClose(hFind);
	return 1;
}
int win_count_dir(char *dir)
{
    int dir_count;
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile(dir,&FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) return -1;
	while(FindNextFile(hFind, &FindFileData)) {
		if (!strcmp(FindFileData.cFileName, ".") || !strcmp(FindFileData.cFileName, ".."))
            continue; /* skip self and parent */
        dir_count++;
	}
	FindClose(hFind);
	return dir_count;
}

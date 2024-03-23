#ifndef PACKER_H
#define PACKER_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

#define DEF_SIZE 256
#define PATH_SIZE 1024

typedef struct {

} Resource;

typedef struct {

	Resource *items;
	size_t size;
	size_t used;
} ResourceList;

typedef struct {

	char **paths;
	size_t paths_used;
	size_t paths_size; 

	ResourceList images;
	ResourceList audio;
} Pack;

void pack(const char *path);
void pack_get_paths(Pack *pack, const char *parent);
void pack_add_path(Pack *pack, char path[PATH_SIZE]);
ResourceList resource_list_new(int size);
void resource_list_add(ResourceList *list, Resource resource);

#endif // !PACKER_H

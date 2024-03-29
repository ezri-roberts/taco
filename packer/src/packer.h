#ifndef PACKER_H
#define PACKER_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

#define LIST_SIZE 256
#define PATH_SIZE 1024

#define RES_TYPES 3
#define RES_TYPE_UNDEFINED 0
#define RES_TYPE_IMAGE 1
#define RES_TYPE_AUDIO 2
#define RES_TYPE_SCRIPT 3

typedef struct {

	uint8_t type;
	char *data;

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
	size_t images_size;
	size_t audio_size;
} Pack;

void pack(const char *path);
void pack_get_paths(Pack *pack, const char *parent);
void pack_add_path(Pack *pack, char path[PATH_SIZE]);
void pack_add_resource(Pack *pack, const char path[PATH_SIZE]);
void pack_destroy(Pack *pack);
Resource resource_new(const char path[PATH_SIZE]);
ResourceList resource_list_new(int size);
void resource_list_add(ResourceList *list, Resource resource);
Resource* resource_list_get(ResourceList *list, int index);
void resource_list_destroy(ResourceList *list);
char* _read_file(const char *path);
const char* _get_ext(const char *path);
uint8_t _get_ext_type(const char *ext);

#endif // !PACKER_H

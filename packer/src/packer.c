#include "packer.h"

static const char* file_types[3][3] = {
	{"png", "jpg", "jpeg"},
	{"mp3", "wav", "ogg"},
	{"txt"},
};

void pack(const char *path) {

	Pack pack;

	pack.images = resource_list_new(LIST_SIZE);
	pack.audio = resource_list_new(LIST_SIZE);

	pack.paths = malloc(LIST_SIZE * sizeof(char*));
	pack.paths_used = 0;
	pack.paths_size = LIST_SIZE;

	pack_get_paths(&pack, path);
	pack_destroy(&pack);
}

void pack_get_paths(Pack *pack, const char *parent) {

	DIR *dir;
	struct dirent *entry;
	struct stat file_stat;

	// Open the directory
	dir = opendir(parent);
	if (dir == NULL) {
		perror("Error opening directory");
	}

	// Read directory entries
	while ((entry = readdir(dir)) != NULL) {

		// Ignore "." and ".." entries
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
			continue;
		}

		char full_path[PATH_SIZE];
		snprintf(full_path, sizeof(full_path), "%s/%s", parent, entry->d_name);

        // Get file information
        if (stat(full_path, &file_stat) == -1) {
            perror("Error getting file information");
            continue;
        }

        // Check if the current item is a directory using stat
        if (S_ISDIR(file_stat.st_mode)) {
			pack_get_paths(pack, full_path);
        } else {
            printf("File: %s | ", full_path);
			pack_add_resource(pack, full_path);
        }
	}

	// Close the directory
	closedir(dir);
}

void pack_add_resource(Pack *pack, const char path[PATH_SIZE]) {

	Resource res = resource_new(path);
	ResourceList *list;

	switch (res.type) {
		case RES_TYPE_IMAGE:
			list = &pack->images;	
			pack->images_size++;
		case RES_TYPE_AUDIO:
			list = &pack->audio;	
			pack->audio_size++;
	}

	resource_list_add(list, res);
}

void pack_add_path(Pack *pack, char path[PATH_SIZE]) {

	if (pack->paths_used == pack->paths_size) {
		pack->paths_size *= 2;
		pack->paths = realloc(pack->paths, pack->paths_size * sizeof(char*));
	}

	pack->paths[pack->paths_used++] = path;
}

void pack_destroy(Pack *pack) {

	free(pack->paths);
	pack->paths_used = 0;
	pack->paths_size = 0;

	resource_list_destroy(&pack->images);
	resource_list_destroy(&pack->audio);
}

Resource resource_new(const char path[PATH_SIZE]) {

	Resource res;

	const char *ext = _get_ext(path);
	res.type = _get_ext_type(ext);

	printf("Type: %d | Ext: %s | ", res.type, ext);

	res.data = _read_file(path);
	free(res.data);

	return res;
}

ResourceList resource_list_new(int size) {

	ResourceList list;

	list.items = malloc(size * sizeof(Resource));
	list.used = 0;
	list.size = size;

	return list;
}

void resource_list_add(ResourceList *list, Resource resource) {

	if (list->used == list->size) {
		list->size *= 2;
		list->items = realloc(list->items, list->size * sizeof(Resource));
	}

	list->items[list->used++] = resource;
}

Resource* resource_list_get(ResourceList *list, int index) {
	return &list->items[index];
}

void resource_list_destroy(ResourceList *list) {

	free(list->items);
	list->used = 0;
	list->size = 0;
}

char* _read_file(const char *path) {

	FILE *file;
	char *buffer = NULL;
	size_t buffer_size = 0;
	size_t bytes_read;

	// Open the file in binary read mode
	file = fopen(path, "rb");
	if (file == NULL) {
		perror("Error opening file");
	}

	// Get the file size by seeking to the end of the file and then back to the beginning
	fseek(file, 0, SEEK_END);
	buffer_size = ftell(file);
	rewind(file);

	// Allocate memory for the buffer based on the file size
	buffer = (char *)malloc(buffer_size * sizeof(char));
	if (buffer == NULL) {
		perror("Error allocating memory");
		fclose(file);
	}

	// Read data from the file into the buffer
	bytes_read = fread(buffer, 1, buffer_size, file);
	if (bytes_read != buffer_size) {
		perror("Error reading file");
		free(buffer);
		fclose(file);
	}

	printf("Bytes Read: %zu\n", bytes_read);

	// Free the allocated memory and close the file
	fclose(file);

	return buffer;
}

const char* _get_ext(const char *path) {

	const char *dot = strrchr(path, '.');
	if(!dot || dot == path) return "";
	return dot + 1;
}

uint8_t _get_ext_type(const char *ext) {

	for (int i = 0; i < RES_TYPES; i++) {
		for (int j = 0; j < RES_TYPES; j++) {

			const char *e = file_types[i][j];
			if (strcmp(e, ext)) return i + 1;
		}
	}

	return RES_TYPE_UNDEFINED;
}

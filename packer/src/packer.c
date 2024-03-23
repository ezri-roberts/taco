#include "packer.h"

void pack(const char *path) {

	Pack pack;

	pack.images = resource_list_new(DEF_SIZE);
	pack.audio = resource_list_new(DEF_SIZE);

	pack.paths = malloc(DEF_SIZE * sizeof(char*));
	pack.paths_used = 0;
	pack.paths_size = DEF_SIZE;

	pack_get_paths(&pack, path);
}

void pack_get_paths(Pack *pack, const char *parent) {

	DIR *dir;
	struct dirent *entry;
	struct stat file_stat;

	// Open the directory
	dir = opendir(parent);
	// if (dir == NULL) {
	// 	perror("Error opening directory");
	// }

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
            // printf("Directory: %s\n", full_path);
			pack_get_paths(pack, full_path);
        } else {
            printf("File: %s\n", full_path);
			// pack_add_path(pack, full_path);
        }

		// If you want the full path, you can concatenate the directory path
		// with the file name like this:
		// printf("File path: %s/%s\n", "path_to_your_directory", entry->d_name);
	}

	// Close the directory
	closedir(dir);
}

void pack_add_path(Pack *pack, char path[PATH_SIZE]) {

	if (pack->paths_used == pack->paths_size) {
		pack->paths_size *= 2;
		pack->paths = realloc(pack->paths, pack->paths_size * sizeof(char[PATH_SIZE]));
	}
	pack->paths[pack->paths_used++] = path;
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

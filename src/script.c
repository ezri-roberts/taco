#include "script.h"
#include <stdlib.h>

void script_read(Script *script, const char *path) {

    script->file = fopen(path, "r");

    if (script->file == NULL) {
        printf("Error: Could not open file %s\n", path);
        exit(1);
    }

    fseek(script->file, 0, SEEK_END);
    script->size = ftell(script->file);
    fseek(script->file, 0, SEEK_SET);

    script->buffer = malloc(script->size + 1);
    if (script->buffer == NULL) {
        printf("Error: Could not allocate memory for file %s\n", path);
        exit(1);
    }

    size_t read = fread(script->buffer, 1, script->size, script->file);
    if (read < script->size) {
        printf("Error: Could not read file %s\n", path);
        exit(1);
    }

    script->buffer[script->size] = '\0';

    fclose(script->file);
}

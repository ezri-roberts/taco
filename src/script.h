#ifndef SCRIPT_H
#define SCRIPT_H

#include <stdio.h>

typedef struct {
	FILE *file;
	size_t size;
	char *buffer;
} Script;

void script_read(Script *script, const char *path);

#endif // SCRIPT_H

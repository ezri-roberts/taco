#ifndef SCENE_H
#define SCENE_H

typedef struct {

	void (*on_attach)();
	void (*on_detach)();
	void (*on_update)();

} Scene;

Scene scene_new();

#endif // !SCENE_H

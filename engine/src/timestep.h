#ifndef TIMESTEP_H
#define TIMESTEP_H

#include "shrpch.h"
#include "sokol_time.h"

typedef struct shrtimestep {
	u64 start;
	f32 last;
	f32 time;
	f32 frame;
	f32 delta;
} shrtimestep;

shrtimestep* shrtimestep_new();
void shrtimestep_destroy(shrtimestep *timestep);
void shrtimestep_start(shrtimestep *timestep);
void shrtimestep_end(shrtimestep *timestep);

#endif // !TIME_STEP

#include "timestep.h"
#include "shrpch.h"

shrtimestep* shrtimestep_new() {

	shrtimestep *timestep = malloc(sizeof(shrtimestep));

	timestep->last = 0;
	timestep->start = 0;
	timestep->frame = 0.0f;
	timestep->time = 0.0f;

	// stm_setup();

	return timestep;
}

void shrtimestep_destroy(shrtimestep *timestep) {
	free(timestep);
	timestep = NULL;
}

void shrtimestep_start(shrtimestep *timestep) {

	// timestep->time = (f32)sapp_frame_count();
	// timestep->delta = timestep->time - timestep->last;
	// timestep->last = timestep->time;

	// u64 count = sapp_frame_count();
	// f64 dur = (f64)sapp_frame_duration();
	//
	// SHR_INFO("Count: %i, Duration: %lf", count, dur);

	// f32 sec = stm_sec(timestep->delta);
	// f32 mil = stm_ms(timestep->delta);
	// SHR_INFO("Delta: %fs (%fms)", sec, mil);
}

void shrtimestep_end(shrtimestep *timestep) {

}

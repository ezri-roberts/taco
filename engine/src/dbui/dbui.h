#ifndef DBUI_H
#define DBUI_H

#include "../layer.h"
#include "shrpch.h"
#include "microui.h"
#include "atlas.inl"

typedef struct {
    float r, g, b;
} dbui_color;

typedef struct {

	mu_Context mu_ctx;
	char logbuf[64000];
    int logbuf_updated;
    dbui_color bg;

	shrlayer *layer;

} dbui_state;

void dbui_init(dbui_state *state);
void dbui_update(dbui_state *state);
void dbui_begin(int disp_width, int disp_height);
void dbui_end(void);
bool dbui_event(dbui_state *state, const shrevent *event);
void dbui_draw(void);
void dbui_push_quad(mu_Rect dst, mu_Rect src, mu_Color color);
void dbui_draw_rect(mu_Rect rect, mu_Color color);
void dbui_draw_text(const char* text, mu_Vec2 pos, mu_Color color);
void dbui_draw_icon(int id, mu_Rect rect, mu_Color color);
int dbui_get_text_width(const char* text, int len);
int dbui_get_text_height(void);
void dbui_set_clip_rect(mu_Rect rect);

void dbui_test_window(dbui_state *state);

// callbacks
int microui_text_width_cb(mu_Font font, const char* text, int len);
int microui_text_height_cb(mu_Font font);

#endif // !DBUI_H

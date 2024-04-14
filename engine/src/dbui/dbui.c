#include "dbui.h"

static sg_image atlas_img;
static sg_sampler atlas_smp;
static sgl_pipeline pip;

static const char key_map[512] = {
    [SAPP_KEYCODE_LEFT_SHIFT]       = MU_KEY_SHIFT,
    [SAPP_KEYCODE_RIGHT_SHIFT]      = MU_KEY_SHIFT,
    [SAPP_KEYCODE_LEFT_CONTROL]     = MU_KEY_CTRL,
    [SAPP_KEYCODE_RIGHT_CONTROL]    = MU_KEY_CTRL,
    [SAPP_KEYCODE_LEFT_ALT]         = MU_KEY_ALT,
    [SAPP_KEYCODE_RIGHT_ALT]        = MU_KEY_ALT,
    [SAPP_KEYCODE_ENTER]            = MU_KEY_RETURN,
    [SAPP_KEYCODE_BACKSPACE]        = MU_KEY_BACKSPACE,
};

void dbui_init(DBUIState *state) {

    // atlas image data is in atlas.inl file, this only contains alpha
    // values, need to expand this to RGBA8
    uint32_t rgba8_size = ATLAS_WIDTH * ATLAS_HEIGHT * 4;
    uint32_t* rgba8_pixels = (uint32_t*) malloc(rgba8_size);
    for (int y = 0; y < ATLAS_HEIGHT; y++) {
        for (int x = 0; x < ATLAS_WIDTH; x++) {
            int index = y*ATLAS_WIDTH + x;
            rgba8_pixels[index] = 0x00FFFFFF | ((uint32_t)atlas_texture[index]<<24);
        }
    }
    atlas_img = sg_make_image(&(sg_image_desc){
        .width = ATLAS_WIDTH,
        .height = ATLAS_HEIGHT,
        .data = {
            .subimage[0][0] = {
                .ptr = rgba8_pixels,
                .size = rgba8_size
            }
        }
    });
    atlas_smp = sg_make_sampler(&(sg_sampler_desc){
        // LINEAR would be better for text quality in HighDPI, but the
        // atlas texture is "leaking" from neighbouring pixels unfortunately
        .min_filter = SG_FILTER_NEAREST,
        .mag_filter = SG_FILTER_NEAREST,
    });
    pip = sgl_make_pipeline(&(sg_pipeline_desc){
        .colors[0].blend = {
            .enabled = true,
            .src_factor_rgb = SG_BLENDFACTOR_SRC_ALPHA,
            .dst_factor_rgb = SG_BLENDFACTOR_ONE_MINUS_SRC_ALPHA
        }
    });

    free(rgba8_pixels);

	// setup microui
    mu_init(&state->mu_ctx);
    state->mu_ctx.text_width = microui_text_width_cb;
    state->mu_ctx.text_height = microui_text_height_cb;
}

void dbui_update(DBUIState *state) {

	mu_begin(&state->mu_ctx);
	dbui_test_window(state);
	mu_end(&state->mu_ctx);

	dbui_begin(sapp_width(), sapp_height());
	mu_Command* cmd = 0;
	while(mu_next_command(&state->mu_ctx, &cmd)) {
		switch (cmd->type) {
			case MU_COMMAND_TEXT: dbui_draw_text(cmd->text.str, cmd->text.pos, cmd->text.color); break;
			case MU_COMMAND_RECT: dbui_draw_rect(cmd->rect.rect, cmd->rect.color); break;
			case MU_COMMAND_ICON: dbui_draw_icon(cmd->icon.id, cmd->icon.rect, cmd->icon.color); break;
			case MU_COMMAND_CLIP: dbui_set_clip_rect(cmd->clip.rect); break;
		}
	}
	dbui_end();
}

void dbui_event(DBUIState *state, const shrevent *event) {

    sapp_event data = event->data;

    switch (data.type) {
        case SAPP_EVENTTYPE_MOUSE_DOWN:
            mu_input_mousedown(&state->mu_ctx, (int)data.mouse_x, (int)data.mouse_y, (1<<data.mouse_button));
            break;
        case SAPP_EVENTTYPE_MOUSE_UP:
            mu_input_mouseup(&state->mu_ctx, (int)data.mouse_x, (int)data.mouse_y, (1<<data.mouse_button));
            break;
        case SAPP_EVENTTYPE_MOUSE_MOVE:
            mu_input_mousemove(&state->mu_ctx, (int)data.mouse_x, (int)data.mouse_y);
            break;
        case SAPP_EVENTTYPE_MOUSE_SCROLL:
            mu_input_scroll(&state->mu_ctx, 0, (int)data.scroll_y);
            break;
        case SAPP_EVENTTYPE_KEY_DOWN:
            mu_input_keydown(&state->mu_ctx, key_map[data.key_code & 511]);
            break;
        case SAPP_EVENTTYPE_KEY_UP:
            mu_input_keyup(&state->mu_ctx, key_map[data.key_code & 511]);
            break;
        case SAPP_EVENTTYPE_CHAR:
            {
                // don't input Backspace as character (required to make Backspace work in text input fields)
                if (data.char_code == 127) { break; }
                char txt[2] = { (char)(data.char_code & 255), 0 };
                mu_input_text(&state->mu_ctx, txt);
            }
            break;
        default:
            break;
    }
}

void dbui_begin(int disp_width, int disp_height) {
    sgl_defaults();
    sgl_push_pipeline();
    sgl_load_pipeline(pip);
    sgl_enable_texture();
    sgl_texture(atlas_img, atlas_smp);
    sgl_matrix_mode_projection();
    sgl_push_matrix();
    sgl_ortho(0.0f, (float) disp_width, (float) disp_height, 0.0f, -1.0f, +1.0f);
    sgl_begin_quads();
}

void dbui_end(void) {
    sgl_end();
    sgl_pop_matrix();
    sgl_pop_pipeline();
}

void dbui_draw(void) {
    sgl_draw();
}

void dbui_push_quad(mu_Rect dst, mu_Rect src, mu_Color color) {
    float u0 = (float) src.x / (float) ATLAS_WIDTH;
    float v0 = (float) src.y / (float) ATLAS_HEIGHT;
    float u1 = (float) (src.x + src.w) / (float) ATLAS_WIDTH;
    float v1 = (float) (src.y + src.h) / (float) ATLAS_HEIGHT;

    float x0 = (float) dst.x;
    float y0 = (float) dst.y;
    float x1 = (float) (dst.x + dst.w);
    float y1 = (float) (dst.y + dst.h);

    sgl_c4b(color.r, color.g, color.b, color.a);
    sgl_v2f_t2f(x0, y0, u0, v0);
    sgl_v2f_t2f(x1, y0, u1, v0);
    sgl_v2f_t2f(x1, y1, u1, v1);
    sgl_v2f_t2f(x0, y1, u0, v1);
}

void dbui_draw_rect(mu_Rect rect, mu_Color color) {
    dbui_push_quad(rect, atlas[ATLAS_WHITE], color);
}

void dbui_draw_text(const char* text, mu_Vec2 pos, mu_Color color) {
    mu_Rect dst = { pos.x, pos.y, 0, 0 };
    for (const char* p = text; *p; p++) {
        mu_Rect src = atlas[ATLAS_FONT + (unsigned char)*p];
        dst.w = src.w;
        dst.h = src.h;
        dbui_push_quad(dst, src, color);
        dst.x += dst.w;
    }
}

void dbui_draw_icon(int id, mu_Rect rect, mu_Color color) {
    mu_Rect src = atlas[id];
    int x = rect.x + (rect.w - src.w) / 2;
    int y = rect.y + (rect.h - src.h) / 2;
    dbui_push_quad(mu_rect(x, y, src.w, src.h), src, color);
}

int dbui_get_text_width(const char* text, int len) {
    int res = 0;
    for (const char* p = text; *p && len--; p++) {
        res += atlas[ATLAS_FONT + (unsigned char)*p].w;
    }
    return res;
}

int dbui_get_text_height(void) {
    return 18;
}

void dbui_set_clip_rect(mu_Rect rect) {
    sgl_end();
    sgl_scissor_rect(rect.x, rect.y, rect.w, rect.h, true);
    sgl_begin_quads();
}

// callbacks
int microui_text_width_cb(mu_Font font, const char* text, int len) {
    (void)font;
    if (len == -1) {
        len = (int) strlen(text);
    }
    return dbui_get_text_width(text, len);
}

int microui_text_height_cb(mu_Font font) {
    (void)font;
    return dbui_get_text_height();
}

void dbui_test_window(DBUIState *state) {

	mu_Context *ctx = &state->mu_ctx;
    /* do window */
    if (mu_begin_window(ctx, "Demo Window", mu_rect(40, 40, 300, 450))) {
        mu_Container *win = mu_get_current_container(ctx);
        win->rect.w = mu_max(win->rect.w, 240);
        win->rect.h = mu_max(win->rect.h, 300);

        /* window info */
        if (mu_header(ctx, "Window Info")) {
            mu_Container *win = mu_get_current_container(ctx);
            char buf[64];
            mu_layout_row(ctx, 2, (int[]) { 54, -1 }, 0);
            mu_label(ctx,"Position:");
            sprintf(buf, "%d, %d", win->rect.x, win->rect.y); mu_label(ctx, buf);
            mu_label(ctx, "Size:");
            sprintf(buf, "%d, %d", win->rect.w, win->rect.h); mu_label(ctx, buf);
        }

        /* labels + buttons */
        if (mu_header_ex(ctx, "Test Buttons", MU_OPT_EXPANDED)) {
            mu_layout_row(ctx, 3, (int[]) { 86, -110, -1 }, 0);
            mu_label(ctx, "Test buttons 1:");
            if (mu_button(ctx, "Button 1")) { TC_TRACE("Pressed Button 1"); }
            if (mu_button(ctx, "Button 2")) { TC_TRACE("Pressed button 2"); }
            mu_label(ctx, "Test buttons 2:");
            if (mu_button(ctx, "Button 3")) { TC_TRACE("Pressed button 3"); }
            if (mu_button(ctx, "Popup")) { mu_open_popup(ctx, "Test Popup"); }
            if (mu_begin_popup(ctx, "Test Popup")) {
                mu_button(ctx, "Hello");
                mu_button(ctx, "World");
                mu_end_popup(ctx);
            }
        }

        /* tree */
        if (mu_header_ex(ctx, "Tree and Text", MU_OPT_EXPANDED)) {
            mu_layout_row(ctx, 2, (int[]) { 140, -1 }, 0);
            mu_layout_begin_column(ctx);
            if (mu_begin_treenode(ctx, "Test 1")) {
                if (mu_begin_treenode(ctx, "Test 1a")) {
                    mu_label(ctx, "Hello");
                    mu_label(ctx, "world");
                    mu_end_treenode(ctx);
                }
                if (mu_begin_treenode(ctx, "Test 1b")) {
                    if (mu_button(ctx, "Button 1")) { TC_TRACE("Pressed button 1"); }
                    if (mu_button(ctx, "Button 2")) { TC_TRACE("Pressed button 2"); }
                    mu_end_treenode(ctx);
                }
                mu_end_treenode(ctx);
            }
            if (mu_begin_treenode(ctx, "Test 2")) {
                mu_layout_row(ctx, 2, (int[]) { 54, 54 }, 0);
                if (mu_button(ctx, "Button 3")) { TC_TRACE("Pressed button 3"); }
                if (mu_button(ctx, "Button 4")) { TC_TRACE("Pressed button 4"); }
                if (mu_button(ctx, "Button 5")) { TC_TRACE("Pressed button 5"); }
                if (mu_button(ctx, "Button 6")) { TC_TRACE("Pressed button 6"); }
                mu_end_treenode(ctx);
            }
            if (mu_begin_treenode(ctx, "Test 3")) {
                static int checks[3] = { 1, 0, 1 };
                mu_checkbox(ctx, "Checkbox 1", &checks[0]);
                mu_checkbox(ctx, "Checkbox 2", &checks[1]);
                mu_checkbox(ctx, "Checkbox 3", &checks[2]);
                mu_end_treenode(ctx);
            }
            mu_layout_end_column(ctx);

            mu_layout_begin_column(ctx);
            mu_layout_row(ctx, 1, (int[]) { -1 }, 0);
            mu_text(ctx, "Lorem ipsum dolor sit amet, consectetur adipiscing "
                "elit. Maecenas lacinia, sem eu lacinia molestie, mi risus faucibus "
                "ipsum, eu varius magna felis a nulla.");
            mu_layout_end_column(ctx);
        }

        /* background color sliders */
        if (mu_header_ex(ctx, "Background Color", MU_OPT_EXPANDED)) {
            mu_layout_row(ctx, 2, (int[]) { -78, -1 }, 74);
            /* sliders */
            mu_layout_begin_column(ctx);
            mu_layout_row(ctx, 2, (int[]) { 46, -1 }, 0);
            mu_label(ctx, "Red:");   mu_slider(ctx, &state->bg.r, 0, 255);
            mu_label(ctx, "Green:"); mu_slider(ctx, &state->bg.g, 0, 255);
            mu_label(ctx, "Blue:");  mu_slider(ctx, &state->bg.b, 0, 255);
            mu_layout_end_column(ctx);
            /* color preview */
            mu_Rect r = mu_layout_next(ctx);
            mu_draw_rect(ctx, r, mu_color(state->bg.r, state->bg.g, state->bg.b, 255));
            char buf[32];
            sprintf(buf, "#%02X%02X%02X", (int) state->bg.r, (int) state->bg.g, (int) state->bg.b);
            mu_draw_control_text(ctx, buf, r, MU_COLOR_TEXT, MU_OPT_ALIGNCENTER);
        }

        mu_end_window(ctx);
    }
}

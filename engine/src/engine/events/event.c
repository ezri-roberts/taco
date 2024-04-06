#include "event.h"

Event event_new(const EventType type, const sapp_event *data) {

	Event event;
	event.type = type;
	event.data = *data;

	int cat_key_input = EVENT_CATEGORY_KEYBOARD | EVENT_CATEGORY_INPUT;
	int cat_mouse_input = EVENT_CATEGORY_MOUSE | EVENT_CATEGORY_INPUT;
	int cat_mouse_btn = EVENT_CATEGORY_MOUSE | EVENT_CATEGORY_MOUSE_BUTTON
		| EVENT_CATEGORY_INPUT;

	switch (event.type) {
		case EVENT_NONE: break;
		case KEY_PRESS: 			event.category = cat_key_input; 			 break;
		case KEY_RELEASE: 			event.category = cat_key_input; 			 break;
		case MOUSE_MOVE: 			event.category = EVENT_CATEGORY_MOUSE; 		 break;
		case MOUSE_SCROLL: 			event.category = cat_mouse_input; 			 break;
		case MOUSE_PRESS:  			event.category = cat_mouse_btn; 			 break;
		case MOUSE_RELEASE: 		event.category = cat_mouse_btn; 			 break;
		case WINDOW_RESIZE:			event.category = EVENT_CATEGORY_APPLICATION; break;
		case WINDOW_CLOSE:			event.category = EVENT_CATEGORY_APPLICATION; break;
		case WINDOW_FOCUS:			event.category = EVENT_CATEGORY_APPLICATION; break;
		case WINDOW_UNFOCUS:		event.category = EVENT_CATEGORY_APPLICATION; break;
		case WINDOW_MOVE:			event.category = EVENT_CATEGORY_APPLICATION; break;
		case APP_TICK:				event.category = EVENT_CATEGORY_APPLICATION; break;
		case APP_UPDATE:			event.category = EVENT_CATEGORY_APPLICATION; break;
		case APP_RENDER:			event.category = EVENT_CATEGORY_APPLICATION; break;
	}

	return event;
}

void event_tostring(char *str, const Event *e) {

	char type[128];

	switch (e->type) {
		case KEY_PRESS: 	 sprintf(type, "Key Press");	  break;
		case KEY_RELEASE: 	 sprintf(type, "Key Release");	  break;
		case MOUSE_MOVE: 	 sprintf(type, "Mouse Move");	  break;
		case MOUSE_SCROLL: 	 sprintf(type, "Mouse Scroll");	  break;
		case MOUSE_PRESS:  	 sprintf(type, "Mouse Press"); 	  break;
		case MOUSE_RELEASE:  sprintf(type, "Mouse Release");  break;
		case WINDOW_RESIZE:	 sprintf(type, "Window Resize");  break;
		case WINDOW_CLOSE:	 sprintf(type, "Window Close");   break;
		case WINDOW_FOCUS:	 sprintf(type, "Window Focus");   break;
		case WINDOW_UNFOCUS: sprintf(type, "Window Unfocus"); break;
		case WINDOW_MOVE:	 sprintf(type, "Window Move"); 	  break;
		case APP_TICK:		 sprintf(type, "App Tick"); 	  break;
		case APP_UPDATE:	 sprintf(type, "App Update"); 	  break;
		case APP_RENDER:	 sprintf(type, "App Render"); 	  break;
	}

	sprintf(str, "%s", type);
}

bool event_in_category(const Event *e, const EventCategory category) {
	return e->category & category;
}

bool event_dispatch(Event *e, const EventType type, const EventCallback callback, void *data) {

	if (type == e->type && callback != NULL) {

		// Log out event info.
		char event_str[128];
		event_tostring(event_str, e);

		e->handled = callback(e, data);

		return true;
	}

	return false;
}

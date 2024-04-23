#include "event.h"

shrevent shrevent_new(const shrevent_type type, const sapp_event *data) {

	shrevent event;
	event.type = type;
	event.data = *data;
	event.handled = false;

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

void shrevent_tostring(char *str, const shrevent *event) {

	char type[128];

	switch (event->type) {
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

bool shrevent_in_category(const shrevent *event, const shrevent_category category) {
	return event->category & category;
}

bool shrevent_dispatch(shrevent *event, const shrevent_type type, const shrevent_callback callback, void *data) {

	if (type == event->type && callback != NULL) {

		// Log out event info.
		char event_str[128];
		shrevent_tostring(event_str, event);
		TC_INFO("Dispatch Event '%s'", event_str);

		event->handled = callback(event, data);

		return event->handled;
	}

	return false;
}

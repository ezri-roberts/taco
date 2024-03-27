#include "event.h"

Event event_new(EventType type) {

	Event e;
	e.type = type;

	int cat_key_input = EVENT_CATEGORY_KEYBOARD | EVENT_CATEGORY_INPUT;
	int cat_mouse_input = EVENT_CATEGORY_MOUSE | EVENT_CATEGORY_INPUT;
	int cat_mouse_btn = EVENT_CATEGORY_MOUSE | EVENT_CATEGORY_MOUSE_BUTTON
		| EVENT_CATEGORY_INPUT;

	switch (e.type) {
		case EVENT_NONE: break;
		case KEY_PRESS: 			e.category = cat_key_input; 			 break;
		case KEY_RELEASE: 			e.category = cat_key_input; 			 break;
		case MOUSE_MOVE: 			e.category = EVENT_CATEGORY_MOUSE; 		 break;
		case MOUSE_SCROLL: 			e.category = cat_mouse_input; 			 break;
		case MOUSE_PRESS:  			e.category = cat_mouse_btn; 			 break;
		case MOUSE_RELEASE: 		e.category = cat_mouse_btn; 			 break;
		case WINDOW_RESIZE:			e.category = EVENT_CATEGORY_APPLICATION; break;
		case WINDOW_CLOSE:			e.category = EVENT_CATEGORY_APPLICATION; break;
		case WINDOW_FOCUS:			e.category = EVENT_CATEGORY_APPLICATION; break;
		case WINDOW_UNFOCUS:		e.category = EVENT_CATEGORY_APPLICATION; break;
		case WINDOW_MOVE:			e.category = EVENT_CATEGORY_APPLICATION; break;
		case APP_TICK:				e.category = EVENT_CATEGORY_APPLICATION; break;
		case APP_UPDATE:			e.category = EVENT_CATEGORY_APPLICATION; break;
		case APP_RENDER:			e.category = EVENT_CATEGORY_APPLICATION; break;
	}

	return e;
}

void event_tostring(char *str, Event *e) {

	char type[256];

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

	sprintf(str, "Event Type: %s.", type);
}

bool event_in_category(Event *e, EventCategory category) {
	return e->category & category;
}

void event_dispatch(Event *e, EventCallback callback) {

	// event->handled = callback(event);
	// Dispatch event?
}

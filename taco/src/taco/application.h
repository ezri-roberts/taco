#ifndef APPLICATION_H
#define APPLICATION_H

typedef struct {

} App;

App *tc_app_new();
void tc_app_run(App *app);
App *tc_app_create(); // Defined in client.

#endif // !APPLICATION_H

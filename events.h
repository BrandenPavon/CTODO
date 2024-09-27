#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
    char cmd[1024];
    void (*func)(char args[1024]);

} cmd_handler_t;

void helpevent(char args[1024]);
void createevent(char args[1024]);
void viewevent(char args[1024]);
void quitevent(char args[1024]);
void exitevent(char args[1024]);

extern int running;
extern ctodo_t * ctodo_arr;

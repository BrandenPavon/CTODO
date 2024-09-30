#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "ctodo.h"
#include "events.h"
#include "essentials.h"

#include "config.h"

ctodo_t * ctodo_arr;

int running = 0;
#define STARTING_CACHE 16
int ctodo_cachenum = STARTING_CACHE;
/* ACTUAL STATIC */
static cmd_handler_t handle_cmds[] = {
    {"quit", quitevent},
    {"exit", exitevent},
    {"create", createevent},
    {"view", viewevent},
    {"help", helpevent}
};

void runsetup(void) {
    time_t unixtime = time(NULL);
    printf("Unix time is %ld \n", unixtime);
    FILE* file = fopen(calfp, "r");
    if (file == NULL) {
        exit(1);
    }
    char c;
    for (c = getc(file); c != EOF; c = getc(file)) {
        if (c == '\n') {
            ctodo_cachenum += 1;
        }
    
    }
    fclose(file);
    file = fopen(calfp, "r");
    fillCTODO(file, ctodo_cachenum); 
    fclose(file);
    running = 1;
}

void runloop(void) {
    char buffer[1024];
    while(running) {
        printf("> ");
        if(fgets(buffer, sizeof(buffer), stdin) != NULL) {
            cmd_handler_t *handler;
            for (handler = handle_cmds; handler->func != NULL; handler++) {
                    if (strncmp(buffer,handler->cmd,strlen(handler->cmd)) == 0) {
                        handler->func(buffer);
                        break;
                    }
            }
        }
    }
}

void runcleanup(void) {
    free(ctodo_arr);
    printf("CLEANUP DONE \n");

}

int main(int argc, char *argv[]) {
    runsetup();
    runloop();
    runcleanup();
    return EXIT_SUCCESS;
}

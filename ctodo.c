#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "ctodo.h"
#include "events.h"
#include "essentials.h"

#include "config.h"

ctodo_t ** ctodo_arr;

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
    char line[4096];
    char c;
    for (c = getc(file); c != EOF; c = getc(file)) {
        if (c == '\n') {
            ctodo_cachenum += 1;
        }
    
    }
    ctodo_arr = malloc(sizeof(ctodo_t)*ctodo_cachenum);
    printf("%d \n", ctodo_cachenum);
    if (file != NULL) {
        int i = 0;
        while (fgets(line, sizeof(line), file)) {
            char * tmp1 = strdup(line);
            char * eventname = getfield(tmp1, 2);
            char * tmp2 = strdup(line);
            char * eventtime = getfield(tmp2, 1);
            char * tmp3 = strdup(line);
            char * eventdesc = getfield(tmp3, 3); 
            ctodo_arr[i] = malloc(sizeof(ctodo_t));
            if (populateTodo(ctodo_arr[i], eventname, eventdesc, (long int) eventtime, 0) == -1) {
                fprintf(stderr, "[ERROR] CAN NOT POPULATE CTODO\n");
                break;
            }
            printf("%s, %s, %s \n", eventname, eventtime, eventdesc);
            free(tmp1);
            free(tmp2);
            free(tmp3);
            i++;
        }
        fclose(file);
    }
    else {
        fprintf(stderr, "Unable to open file!\n");
    }
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
    for (int i = 0; i < 0; ++i) {free(ctodo_arr[i]);}

}

int main(int argc, char *argv[]) {
    runsetup();
    runloop();
    runcleanup();
    return EXIT_SUCCESS;
}

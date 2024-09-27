#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "ctodo.h"

char* getfield(char* line, int num)
{
    char* tok;
    for (tok = strtok(line, ";");
            tok && *tok;
            tok = strtok(NULL, ";\n"))
    {
        if (!--num) {
            return tok;
        }
    }
    return NULL;
}




int populateTodo(ctodo_t *ctodo, char * en, char * ed, long int et, short int es) {
    if (!ctodo) { return -1; }
    ctodo->eventname = en;
    ctodo->eventdesc = ed;
    ctodo->eventtime = et;
    ctodo->eventstatus = es;
    return 0;
}

time_t string_to_seconds(const char *timestamp_str)
{
    struct tm tm;
    time_t seconds;

    if (timestamp_str != NULL && sscanf(timestamp_str, "%d-%d-%d %d:%d:%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday, &tm.tm_hour, &tm.tm_min, &tm.tm_sec) == 6) {
        tm.tm_year -= 1900;
        tm.tm_mon -= 1;
        tm.tm_isdst = -1;
seconds = mktime(&tm);
        if (seconds == (time_t)-1) {
            printf("reading time from %s failed\n", timestamp_str);
        }
        return seconds;
    } else {
        return (time_t) -1;
    }
}

int scanandcheck(char buf[], int size) {
    if(fgets(buf, size, stdin) != NULL && buf[0] != '\n') {
        return 0;
    } else {
        return 1;
    }
}


int fillCTODO(FILE * fp, int ctodo_arrsize) {
    char line[4096];
    ctodo_arr =  (ctodo_t *) malloc(sizeof(ctodo_t)*ctodo_arrsize);
    printf("%d \n", ctodo_arrsize);
    int i = 0;
    while (fgets(line, sizeof(line), fp)) {
        char * tmp1 = strdup(line);
        char * eventname = getfield(tmp1, 2);
        char * tmp2 = strdup(line);
        char * eventtime = getfield(tmp2, 1);
        char * tmp3 = strdup(line);
        char * eventdesc = getfield(tmp3, 3); 
        if (populateTodo(&ctodo_arr[i], eventname, eventdesc, (long int) eventtime, 0) == -1) {
            fprintf(stderr, "[ERROR] CAN NOT POPULATE CTODO\n");
            break;
        }
        free(tmp1);
        free(tmp2);
        free(tmp3);
        i++;
    }
    return 0;
}

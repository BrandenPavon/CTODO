#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "ctodo.h"

int populateTodo(ctodo_t *ctodo, char * en, char * ed, long int et, short int es) {
    if (!ctodo) { return -1; }
    ctodo->eventname = en;
    ctodo->eventdesc = ed;
    ctodo->eventtime = et;
    ctodo->eventstatus = es;
    return 0;
}

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



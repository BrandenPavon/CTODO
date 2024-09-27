#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "ctodo.h"
#include "config.h"
#include "essentials.h"
void viewevent(char args[1024]) { 
    char eventname[256];
    printf("[event name] ");
    if(fgets(eventname, sizeof(eventname), stdin) != NULL && eventname[0] != '\n') {
        for(int i = 0; i<1 ;i++) {

        }
    }
    return;
}
void helpevent(char args[1024]) { 
    printf("What do you need help with? \n");
    return;
}
void createevent(char args[1024]) { 
    char eventname[256];
    char eventdesc[1024];
    char eventtime[256];
    // day,month,year,hour,minute,second
    printf("[event name] ");
    if(fgets(eventname, sizeof(eventname), stdin) != NULL && eventname[0] != '\n') {
        printf("[event description] ");
        if(fgets(eventdesc, sizeof(eventdesc), stdin) != NULL && eventdesc[0] != '\n'){
            printf("[event time] [YEAR-MONTH-DAY HOUR:MINUTE:SECOND] ");
            if(fgets(eventtime, sizeof(eventtime), stdin) != NULL && eventtime[0] != '\n') {
                printf("%ld\n", string_to_seconds(eventtime));
                eventname[strcspn(eventname, "\n")] = 0;
                eventdesc[strcspn(eventdesc, "\n")] = 0;
                FILE *fptr;
                fptr = fopen(calfp,"a");
                fprintf(fptr, "%ld; %s; %s\n", string_to_seconds(eventtime), eventname, eventdesc);
                ctodo_cachenum++;
                fillCTODO(fptr, ctodo_cachenum);
                fclose(fptr);
            }
            
        }   
    }
    return;
}
void quitevent(char args[1024]) { 
    running = 0;
    return;
}
void exitevent(char args[1024]) { 
    running = 0;
    return;
}


typedef struct {
    char * eventname;
    char * eventdesc;
    long int eventtime;
    short int eventstatus;
} ctodo_t;


void runsetup(void);
void runloop(void);
void runcleanup(void);

extern int running;
extern ctodo_t ** ctodo_arr;


typedef struct {
    char cmd[1024];
    void (*func)(char args[1024]);

} cmd_handler_t;

typedef struct {
    char * eventname;
    char * eventdesc;
    long int eventtime;
    short int eventstatus;
} ctodo_t;



void helpevent(char args[1024]);
void createevent(char args[1024]);
void quitevent(char args[1024]);
void poopevent(char args[1024]);
void runsetup(void);
void runloop(void);


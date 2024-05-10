#ifndef API_H
#define API_H









 void API_call(char* command, char* name, int PID, char* metric);


struct ProcessList ListReadWrite(char* command);

double readTotal(char* command);


void* loop_thread(void *arg);

void loopOver();







#endif

#ifndef API_H
#define API_H









char* API_call(char* command);


struct ProcessList ListReadWrite(char* command);

double readTotal(char* command);


void* loop_thread(void *arg);

void loopOver();







#endif

#ifndef PROCESSLIST_H
#define PROCESSLIST_H

#define MAX_PROCESSES 1024

#include "Process.h"

struct ProcessList processList;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct ProcessList {
    
    struct Process processes[MAX_PROCESSES];
    int numProcesses;
};


struct ProcessList getUpdatedList(){
     pthread_mutex_lock(&mutex);
   
     

     return processList;
     pthread_mutex_unlock(&mutex2);
}

void getProcessList(struct ProcessList *processList);


void getUsage(struct Process *process);
void printProcessInfo(const struct Process *process);
void* printProcessList(void *size);
void updateList();


struct ProcessList ListReadWrite(char* command);




#endif // TOP_INFO_H



#ifndef PROCESSLIST_H
#define PROCESSLIST_H

#define MAX_PROCESSES 1024

#include "Process.h"
#include "MainList.h"
#include <pthread.h>




struct ProcessList {
    
    struct Process processes[MAX_PROCESSES];
    int numProcesses;
};



extern void getProcessList(struct ProcessList *processList);


void getUsage(struct Process *process);
void printProcessInfo(const struct Process *process);
void* printProcessList(void *size);



struct ProcessList ListReadWrite(char* command);




#endif // TOP_INFO_H



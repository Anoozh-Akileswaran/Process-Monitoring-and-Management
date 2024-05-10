#ifndef MANAGEMENT_TOOL_H
#define MANAGEMENT_TOOL_H
#include <stdbool.h>

//creates a new process basesd on the input and in case of failure->return false
bool create(char* name);

//Terminate a existing process
bool terminate(int PID);

//pause and resume a thread
bool pause_resume(int choice, int pid); 
















#endif

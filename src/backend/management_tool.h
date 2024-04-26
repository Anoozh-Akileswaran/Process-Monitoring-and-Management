#ifndef MANAGEMENT_TOOL_H
#define MANAGEMENT_TOOL_H

//creates a new process basesd on the input and in case of failure->return false
bool create_procoess(char* name);

//Terminate a existing process
bool terminate_process(int PID);

//pause a thread
bool pause_process(int PID);


//resume a process, which was paused
bool resume_process(int PID);
















#endif

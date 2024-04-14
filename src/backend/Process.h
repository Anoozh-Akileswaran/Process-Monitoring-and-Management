#ifndef TOP_INFO_H
#define TOP_INFO_H

#define MAX_NAME_LENGTH 50

struct Process {
    int pid;                // Process ID
    char name[MAX_NAME_LENGTH]; // Process name
    char state;             // Process state (R, S, Z, etc.)
    double cpuUsage;        // CPU usage (%)
    double memUsage;        // Memory usage (KiB)
    double memo_%;	    // Memory usage (%)
    int Priority;	    // Priority
    char time_cpu[MAX_NAME_LENGTH]; //CPU usage time


};

// Function to get top processes' information
int getTopProcesses(struct Process processes[], int numProcesses);










#endif // TOP_INFO_H

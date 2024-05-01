#ifndef PROCESS_H
#define PROCESS_H

#define MAX_NAME_LENGTH 256

struct Process {
    int pid;                // Process ID
    char user[MAX_NAME_LENGTH]; // Process name
    int nice;			//Nice value
    int virt;			//virtuel memory
    int res;			// resid. memory
    int shr;			//shared memory 
    char state;             // Process state (R, S, Z, etc.)
    double cpuUsage;        // CPU usage (%)
    double memUsage;        // Memory usage (KiB)
    double memUsagePercentage;	    // Memory usage (%)
    int priority;	    // Priority
    char time_cpu[MAX_NAME_LENGTH]; //CPU usage time
    char name[MAX_NAME_LENGTH];

};

// Function to get top processes' information
int getTopProcesses(struct Process processes[], int numProcesses);










#endif // PROCESS_H

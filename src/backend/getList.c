#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include "Process.h"
#include "ProcessList.h"




#define MAX_LINE_LENGTH 2048


// Function to get process PIDs
void getProcessPIDs(struct ProcessList *processList) {
    DIR *dir = opendir("/proc");
    if (dir == NULL) {
        perror("Failed to open directory");
        exit(EXIT_FAILURE);
    }
    
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (atoi(entry->d_name) != 0) {
            processList->pids[processList->numProcesses++] = atoi(entry->d_name);
        }
    }
    
    closedir(dir);
}




// Function to populate the ProcessList by parsing top command output
void populateProcessList(struct ProcessList *processList) {
    FILE *fp;
    char line[MAX_LINE_LENGTH];
    fp = popen("top -b -n 1", "r");
    if (fp == NULL) {
        perror("popen() error");
        exit(EXIT_FAILURE);
    }
    // Skipping the header lines
    for (int i = 0; i < 7; i++) {
        fgets(line, sizeof(line), fp);
    }
    // Parsing process information
    while (fgets(line, sizeof(line), fp) != NULL && processList->number_Process < MAX_PROCESSES) {
        struct Process process;
	//printf(line);
        if (sscanf(line, "%d %s %d %d %d %d %d %c %lf %lf %s %[^\n]", 
                  &process.pid, &process.user, &process.priority, &process.nice, &process.virt, &process.res, &process.shr,
                   &process.state, &process.cpuUsage, &process.memUsagePercentage,
                   &process.time_cpu, &process.name) == 12) {
            // Adding the process to the processList
            processList->processes[processList->number_Process++] = process;
        }
    }
    pclose(fp);
}

int main() {
    struct ProcessList processList; // Now the definition of struct ProcessList is known
    processList.number_Process = 0;
    populateProcessList(&processList);

    // Example usage: printing process information
    for (int i = 0; i < processList.number_Process; i++) {
        printf("PID: %d, User: %s, Priority: %d, Nice: %d, VIRT: %d, RES: %d, SHR: %d, State: %c, CPU Usage: %f%, Mem Usage: %f%, Time CPU: %s, Command: %s\n", 
                  processList.processes[i].pid, processList.processes[i].user, processList.processes[i].priority, processList.processes[i].nice,
                  processList .processes[i].virt, processList.processes[i].res, processList.processes[i].shr, processList.processes[i].state,
                  processList.processes[i].cpuUsage, processList.processes[i].memUsagePercentage, processList.processes[i].time_cpu, processList.processes[i].name);

    }

	return 0;
}

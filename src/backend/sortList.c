#include <stdio.h>
#include <stdlib.h>
#include <Process.h>
#include <ProcessList.h>
#include <string.h>
#include "monitor_tool.h"


// Function to convert CPU time in hh:mm:ss format to seconds
int timeToSeconds(const char *timeStr) {
    int hours, minutes, seconds;
    sscanf(timeStr, "%d:%d:%d", &hours, &minutes, &seconds);
    return hours * 3600 + minutes * 60 + seconds;
}






// Custom coTmparison functions for qsort
int compareByPID(const void *a, const void *b){
    const Process *processA = (const Process *)a;
    const Process *processB = (const Process *)b;
    
    if (processA->pid < processB->pid) return 1;
    if (processA->pid > processB->pid) return -1;
    return 0;


}


int compareByCpu(const void *a, const void *b) {
    const Process *processA = (const Process *)a;
    const Process *processB = (const Process *)b;

    if (processA->cpuUsage < processB->cpuUsage) return 1;
    if (processA->cpuUsage > processB->cpuUsage) return -1;
    return 0;
}

int compareByRam(const void *a, const void *b) {
    const Process *processA = (const Process *)a;
    const Process *processB = (const Process *)b;

    if (processA->memUsage < processB->memUsage) return 1;
    if (processA->memUsage > processB->memUsage) return -1;
    return 0;
}

int compareByRam_percentage(const void *a, const void *b) {
    const Process *processA = (const Process *)a;
    const Process *processB = (const Process *)b;

    if (processA->memo_% < processB->memUsage) return 1;
    if (processA->memo_% > processB->memUsage) return -1;
    return 0;
}

int compareByPriority(const void *a, const void *b){
    const Process *processA = (const Process *)a;
    const Process *processB = (const Process *)b;
    
    if (processA->Priority < processB->Priority) return 1;
    if (processA->Priority > processB->Priority) return -1;
    return 0;


}

int compareByCPUTime(const void *a, const void *b){
    const Process *processA = (const Process *)a;
    const Process *processB = (const Process *)b;
    
    if (timeToSeconds(processA->time_cpu) < timeToSeconds(processB->time_cpu)) return 1;
    if (timeToSeconds(processA->time_cpu) > timeToSeconds(processB->time_cpu)) return -1;
    return 0;


}





// Sort function for ProcessList
void sortProcessList(ProcessList *list, int (*compareFunc)(const void *, const void *)) {
    qsort(list->processes, list->size, sizeof(Process), compareFunc);
}

int main() {
    // Initialize a sample ProcessList
    ProcessList list;
    list.size = 3;
    list.processes = malloc(list.size * sizeof(Process));

    // Sample processes with CPU and RAM usage
    list.processes[0] = (Process){.pid = 1, .name = "process1", .cpuUsage = 10.5, .ramUsage = 200.0};
    list.processes[1] = (Process){.pid = 2, .name = "process2", .cpuUsage = 5.0, .ramUsage = 150.0};
    list.processes[2] = (Process){.pid = 3, .name = "process3", .cpuUsage = 15.0, .ramUsage = 250.0};

    // Sort by CPU usage
    sortProcessList(&list, compareByCpu);
    printf("Sorted by CPU usage:\n");
    for (size_t i = 0; i < list.size; ++i) {
        printf("PID: %d, Name: %s, CPU Usage: %.2f, RAM Usage: %.2f\n",
               list.processes[i].pid, list.processes[i].name,
               list.processes[i].cpuUsage, list.processes[i].ramUsage);
    }

    // Sort by RAM usage
    sortProcessList(&list, compareByRam);
    printf("\nSorted by RAM usage:\n");
    for (size_t i = 0; i < list.size; ++i) {
        printf("PID: %d, Name: %s, CPU Usage: %.2f, RAM Usage: %.2f\n",
               list.processes[i].pid, list.processes[i].name,
               list.processes[i].cpuUsage, list.processes[i].ramUsage);
    }

    // Free allocated memory
    free(list.processes);

    return 0;
}


void sortList(char* metric, ProcessList *processList){
   switch(metric){

	case "PID":
	     sortProcessList(&processList, compareByPID);
	   break;

	case "CPUusage":
             sortProcessList(&processList, compareByCpu);
           break;
	
	case "Ramusage":
             sortProcessList(&processList, compareByRAM);
           break;

	case "RAMusage_percentage":
             sortProcessList(&processList, compareByRAM_percentage);
           break;

	case "Priority":
             sortProcessList(&processList, compareByPriority);
           break;

	case "CPUTime":
             sortProcessList(&processList, compareByCPUTime);
           break;
	
   }



}

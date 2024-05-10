#include <stdio.h>
#include <stdlib.h>
#include "Process.h"
#include "ProcessList.h"
#include <string.h>
#include "monitor_tool.h"
#include <stdbool.h>
#include "MainList.h"

// Function to convert CPU time in hh:mm:ss format to seconds
int timeToSeconds(const char *timeStr) {
    int hours, minutes, seconds;
    sscanf(timeStr, "%d:%d:%d", &hours, &minutes, &seconds);
    return hours * 3600 + minutes * 60 + seconds;
}






// Custom coTmparison functions for qsort
int compareByPID(const void *a, const void *b){
    const struct Process *processA = (const struct Process *)a;
    const struct Process *processB = (const struct Process *)b;
    
    if (processA->pid < processB->pid) return 1;
    if (processA->pid > processB->pid) return -1;
    return 0;


}


int compareByCpu(const void *a, const void *b) {
    const struct Process *processA = (const struct Process *)a;
    const struct Process *processB = (const struct Process *)b;

    if (processA->cpuUsage < processB->cpuUsage) return 1;
    if (processA->cpuUsage > processB->cpuUsage) return -1;
    return 0;
}

int compareByRam(const void *a, const void *b) {
    const struct Process *processA = (const struct Process *)a;
    const struct Process *processB = (const struct Process *)b;

    if (processA->memUsage < processB->memUsage) return 1;
    if (processA->memUsage > processB->memUsage) return -1;
    return 0;
}

int compareByRam_percentage(const void *a, const void *b) {
    const struct Process *processA = (const struct Process *)a;
    const struct Process *processB = (const struct Process *)b;
    if (processA->memUsagePercentage < processB->memUsagePercentage) return 1;
    if (processA->memUsagePercentage > processB->memUsagePercentage) return -1;
    return 0;
}

int compareByPriority(const void *a, const void *b){
    const struct Process *processA = (const struct Process *)a;
    const struct Process *processB = (const struct Process *)b;
    
    if (processA->priority < processB->priority) return 1;
    if (processA->priority > processB->priority) return -1;
    return 0;


}

/*
int compareByCPUTime(const void *a, const void *b){
    const struct Process *processA = (const struct Process *)a;
    const struct Process *processB = (const struct Process *)b;
    
    if (timeToSeconds(processA->time_cpu) < timeToSeconds(processB->time_cpu)) return 1;
    if (timeToSeconds(processA->time_cpu) > timeToSeconds(processB->time_cpu)) return -1;
    return 0;


}
*/




// Sort function for ProcessList
void sortProcessList(struct ProcessList *list, int (*compareFunc)(const void *, const void *)) {
    qsort(list->processes, list->numProcesses, sizeof(struct Process), compareFunc);
}



bool sortList(int metric){
   switch(metric){

	case 1:
	     sortProcessList(&processList, compareByPID);
	   break;

	case 2:
             sortProcessList(&processList, compareByCpu);
           break;
	
	case 3:
             sortProcessList(&processList, compareByRam);
           break;

	case 4:
             sortProcessList(&processList, compareByRam_percentage);
           break;

	case 5:
             sortProcessList(&processList, compareByPriority);
           break;

	case 6:
             //sortProcessList(&processList, compareByCPUTime);
           break;
	
   }
  return true;



}

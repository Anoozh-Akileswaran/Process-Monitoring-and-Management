#include <stdio.h>
#include <stdlib.h>
#include <Process.h>
#include <ProcessList.h>
#include <string.h>
#include "monitor_tool.h"
#include <stdbool>

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



bool sortList(char* metric){
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
  return true



}

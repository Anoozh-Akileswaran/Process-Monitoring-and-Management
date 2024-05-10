#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <pthread.h>
#include "Process.h"
#include "ProcessList.h"
#include "MainList.h"

#define MAX_NAME_LENGTH 256
#define MAX_PROCESSES 2048
//Offical


int range = 20;
pthread_mutex_t mutex_gp2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_gp2_2 = PTHREAD_MUTEX_INITIALIZER;



// Function to get process list
void getProcessList(struct ProcessList *processList) {
    DIR *dir = opendir("/proc");
    if (dir == NULL) {
        perror("Failed to open directory");
        exit(EXIT_FAILURE);
    }
    
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (atoi(entry->d_name) != 0) {
            struct Process process;
            process.pid = atoi(entry->d_name);
            strcpy(process.name, entry->d_name); // Placeholder name
            processList->processes[processList->numProcesses++] = process;
        }
    }
    
    closedir(dir);
}

// Function to get CPU and memory usage using top command
void getUsage(struct Process *process) {
    char command[256];
    sprintf(command, "top -b n 1 -p %d", process->pid);
    
    FILE *pipe = popen(command, "r");
    if (pipe == NULL) {
        perror("Failed to execute command");
        return;
    }
    
    char line[1024];
        // Skipping the header lines
    for (int i = 0; i < 7; i++) {
        fgets(line, sizeof(line), pipe);
    }
    
     pthread_mutex_lock(&mutex_gp2);
    if (fgets(line, sizeof(line), pipe) != NULL) {
        // Parse the line to get CPU and memory usage
        printf(line);
        sscanf(line, "%d %s %d %d %d %d %d %c %lf %lf %s %s", 
                  &process->pid, &process->user, &process->priority, &process->nice, &process->virt, &process->res, &process->shr,
                   &process->state, &process->cpuUsage, &process->memUsagePercentage,
                   &process->time_cpu, &process->name);
    
    } else {
        printf("No data received for PID: %d\n", process->pid);
    }
    
     pclose(pipe);
     pthread_mutex_unlock(&mutex_gp2);
}

// Function to print process information
void printProcessInfo(const struct Process *process) {
    pthread_mutex_lock(&mutex_gp2_2);
    printf("PID: %d\n", process->pid);
    printf("Name: %s\n", process->name);
    printf("CPU Usage: %.2f%%\n", process->cpuUsage);
    printf("Priority: %d\n", process->priority);
    printf("Memory Usage: %.2f KiB\n", process->memUsage);
    printf("Memory Usage_percentage: %f %\n", process->memUsagePercentage);
    printf("CPU-Usage Time: %s\n", process->time_cpu);
    printf("\n");
    pthread_mutex_unlock(&mutex_gp2_2);
   
}

// Function to print process list
void* printProcessList(void *size) {
	int s = (int *) size;
	printf("s: %d", s);
    for (int i = (s-1)*range; i < s*range-1; ++i) {
        printf("Process %d:\n", i + 1);
        getUsage(&processList.processes[i]);
        printProcessInfo(&processList.processes[i]);
    }
}



void updateList() {
    processList.numProcesses = 0;
    getProcessList(&processList);
    int size = (int) 250/range;
    pthread_t threads[size];
    for(int i = 0; i<size; ++i){
    	if (pthread_create(&threads[i], NULL, printProcessList, (void *) i+1) != 0) {
    	    printf("I am here");
            perror("pthread_create");
          
        }
    	
    
    }
    for (int i = 0; i < size; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
        }
    }
    
    
    
    
     
    
}


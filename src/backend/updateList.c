#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PROCESSES 100

//adapt your code according to your implementation

void updateProcessList() {

    FILE* fp = popen("ps -e -o pid,comm", "r");
    if (!fp) {
        perror("Failed to run ps command");
        return;
    }

    char line[256];
    int pid;
    char name[256];

    // Clear existing process list
    numProcesses = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "PID")) {  // Skip header line
            continue;
        }

        sscanf(line, "%d %s", &pid, name);

        processList[numProcesses].pid = pid;
        strncpy(processList[numProcesses].name, name, sizeof(processList[numProcesses].name) - 1);
        numProcesses++;

        if (numProcesses >= MAX_PROCESSES) {
            break;
        }
    }

    pclose(fp);
}

void *checkProcess() {
    while (1) {
        updateProcessList();
	/*
        printf("Process List:\n");
        printf("--------------\n");

        for (int i = 0; i < numProcesses; i++) {
            printf("PID: %d, Name: %s\n", processList[i].pid, processList[i].name);
        }

        printf("--------------\n\n");
	*/

        sleep(2);  // Update every 2 seconds
    }

    return 0;
}

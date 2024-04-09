#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

void printRunningProcesses() {
    // Open a pipe to read the output of the 'ps' command
    FILE *pipe = popen("ps -eo pid,comm,%cpu,%mem --sort=-%cpu", "r");
    if (pipe == NULL) {
        perror("Error opening pipe");
        return;
    }

    char line[MAX_LINE_LENGTH];
    // Read and discard the header line
    fgets(line, sizeof(line), pipe);

    // Read and print each line of 'ps' output
    printf("%-8s%-20s%-8s%-8s\n", "PID", "COMMAND", "CPU(%)", "MEM(%)");
    while (fgets(line, sizeof(line), pipe)) {
        int pid;
        char command[50];
        float cpu, mem;
        // Parse the line to extract PID, command, CPU percentage, and memory percentage
        if (sscanf(line, "%d %s %f %f", &pid, command, &cpu, &mem) == 4) {
            printf("%-8d%-20s%-8.2f%-8.2f\n", pid, command, cpu, mem);
        }
    }

    pclose(pipe);
}

int main() {
    printf("Running Processes:\n");
    printRunningProcesses();
    return 0;
}

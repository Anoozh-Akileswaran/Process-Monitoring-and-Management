#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "plot_tool.h"
#include "MainList.h"
#include "MainTotalValues.h"


#define PATH_MAX 256
#define MAX_BUFFER 256

// Function to read total RAM size from /proc/meminfo
int readTotalRAM() {
  FILE *fp;
    char buffer[MAX_BUFFER];
    int total_memory;

    // Open a pipe to execute the free command
    fp = popen("free -m | awk 'NR==2 {print $2}'", "r");
    if (fp == NULL) {
        perror("popen");
        exit(EXIT_FAILURE);
    }

    // Read the output of free
    if (fgets(buffer, MAX_BUFFER, fp) != NULL) {
        // Parse total memory value
        sscanf(buffer, "%d", &total_memory);
    }

    // Close the pipe
    pclose(fp);

    return total_memory;
}

// Function to read free RAM size from /proc/meminfo
int readUsedRAM() {
    FILE *fp;
    char buffer[MAX_BUFFER];
    int used_memory;

    // Open a pipe to execute the free command
    fp = popen("free -m | awk 'NR==2 {print $3}'", "r");
    if (fp == NULL) {
        perror("popen");
        exit(EXIT_FAILURE);
    }

    // Read the output of free
    if (fgets(buffer, MAX_BUFFER, fp) != NULL) {
        // Parse used memory value
        sscanf(buffer, "%d", &used_memory);
    }

    // Close the pipe
    pclose(fp);

    return used_memory;

} 










// Function to read total CPU time
// Function to read total CPU usage from /proc/stat
// Function to get total CPU usage using sar -u command
double getTotalCpuUsage() {
    FILE *pipe = popen("sar -u 1 1 | grep 'Average:'", "r");
    if (!pipe) {
        perror("Error opening pipe");
        exit(EXIT_FAILURE);
    }

    char line[256];
    fgets(line, sizeof(line), pipe);  // Read the "Average:" line

    pclose(pipe);

    printf("Debug: Read line: %s\n", line);  // Debugging print

    // Parse the line to extract CPU usage
    char label[10];
    double user, nice, system, iowait, steal, idle;

    if (sscanf(line, "%s %*s %lf %lf %lf %lf %lf %lf", 
               label, &user, &nice, &system, &iowait, &steal, &idle) != 7) {
        perror("Error parsing sar output");
        exit(EXIT_FAILURE);
    }

    printf("%f\n",idle);
    // Calculate total CPU usage (excluding idle time)
    double totalCpuUsage = (user + nice + system + iowait + steal) / 100.0;

    return 100-idle;
}


unsigned long long getusedMemory() {
// Function to read memory info
 FILE *file = fopen("/proc/meminfo", "r");
    if (!file) {
        perror("Error opening /proc/meminfo");
        exit(EXIT_FAILURE);
    }

    char line[256];
    unsigned long long memTotal = 0, memAvailable = 0;

    // Read lines until both MemTotal and MemAvailable are found
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "MemTotal:", 9) == 0) {
            sscanf(line + 9, "%llu", &memTotal);
        } else if (strncmp(line, "MemAvailable:", 13) == 0) {
            sscanf(line + 13, "%llu", &memAvailable);
        }

        if (memTotal && memAvailable) {
            break;
        }
    }

    fclose(file);

    // Calculate available memory
    unsigned long long usedMemory = memTotal - memAvailable;

    return usedMemory;
}



void getTotal() {

printf("I am here4\n");
    long totalRAM = readTotalRAM();
    int usedRam = readUsedRAM();
  

    double total_used_ram =  ((double)  usedRam / totalRAM) * 100;

    total_ram = total_used_ram;
    total_Mem = usedRam;
    printf("Total RAM_used: %ld MB\n", total_Mem);
    printf("Total RAM_existing: %ld MB\n", totalRAM);
    printf("RAM Usage Percentage: %.2f%%\n", total_ram);

    total_cpu = getTotalCpuUsage();
    printf("Total CPU Usage: %f\n", total_cpu); 
    printf("I am here\n");




}










/*
int main() {
    unsigned long long prevTotalCPUTime, currTotalCPUTime, totalCPUTimeDiff;
    double totalCPUTimeUsage;

    prevTotalCPUTime = readTotalCPUTime();
    sleep(1);  // Wait for 1 second
    currTotalCPUTime = readTotalCPUTime();

    totalCPUTimeDiff = currTotalCPUTime - prevTotalCPUTime;
    totalCPUTimeUsage = ((double)totalCPUTimeDiff / sysconf(_SC_CLK_TCK)) * 100.0;

    printf("Total CPU Usage: %.2f%%\n", totalCPUTimeUsage);

    return 0;
}
*/

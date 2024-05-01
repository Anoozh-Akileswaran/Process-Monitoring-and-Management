#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "plot_tool.h"

#define PATH_MAX 256


// Function to read total RAM size from /proc/meminfo
long readTotalRAM() {
    FILE *file = fopen("/proc/meminfo", "r");
    if (file == NULL) {
        perror("Error opening /proc/meminfo");
        exit(EXIT_FAILURE);
    }

    char line[PATH_MAX];
    long totalRAM = 0;

    // Find the line with "MemTotal" information
    while (fgets(line, PATH_MAX, file) != NULL) {
        if (sscanf(line, "MemTotal: %ld kB", &totalRAM) == 1) {
            break;
        }
    }

    fclose(file);

    // Convert total RAM from kB to bytes
    return totalRAM * 1024;
}

// Function to read free RAM size from /proc/meminfo
long readFreeRAM() {
    FILE *file = fopen("/proc/meminfo", "r");
    if (file == NULL) {
        perror("Error opening /proc/meminfo");
        exit(EXIT_FAILURE);
    }

    char line[PATH_MAX];
    long freeRAM = 0;

    // Find the line with "MemFree" information
    while (fgets(line, PATH_MAX, file) != NULL) {
        if (sscanf(line, "MemFree: %ld kB", &freeRAM) == 1) {
            break;
        }
    }

    fclose(file);

    // Convert free RAM from kB to bytes
    return freeRAM * 1024;
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
    long totalRAM = readTotalRAM();
    long freeRAM = readFreeRAM();
    long absRam = (long) totalRAM - freeRAM;

    total_ram = ((long) usedRAM / absRam) * 100;

    
    printf("Total RAM: %ld bytes\n", totalRAM);
    printf("Used RAM: %ld bytes\n", usedRAM);
    printf("RAM Usage Percentage: %.2f%%\n", ramUsagePercentage);

    total_cpu = getTotalCpuUsage();
    printf("Total CPU Usage: %.2f%%\n", total_cpu); 


   return true;
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

#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Function to read total CPU time
unsigned long long readTotalCPUTime() {
    FILE* file = fopen("/proc/stat", "r");
    if (!file) {
        perror("Failed to open /proc/stat");
        return 0;
    }

    char buffer[256];
    unsigned long long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
    unsigned long long total;

    fgets(buffer, sizeof(buffer), file);
    sscanf(buffer, "cpu %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu",
           &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal, &guest, &guest_nice);

    total = user + nice + system + idle + iowait + irq + softirq + steal;
    fclose(file);

    return total;
}
// Function to read memory info
unsigned long long readMemoryInfo(const char* field) {
    FILE* file = fopen("/proc/meminfo", "r");
    if (!file) {
        perror("Failed to open /proc/meminfo");
        return 0;
    }

    char buffer[256];
    unsigned long long value = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        if (strstr(buffer, field)) {
            sscanf(buffer, "%*s %llu", &value);
            break;
        }
    }

    fclose(file);
    return value;
}

/*
int main() {
    unsigned long long totalMem, freeMem, totalMemUsed;

    totalMem = readMemoryInfo("MemTotal:");
    freeMem = readMemoryInfo("MemFree:");

    totalMemUsed = totalMem - freeMem;

    printf("Total Memory: %llu kB\n", totalMem);
    printf("Total Memory Used: %llu kB\n", totalMemUsed);

    return 0;
}
*/












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

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include "MainList.h"
bool terminate(int pid) {
    // PID of the process to be terminated

    // Send termination signal to the process
    if (kill(pid, SIGKILL) == 0) {
        printf("Process with PID %d terminated successfully.\n", pid);
    } else {
        perror("Error terminating process");
        return 1;
    }

    return 0;
}

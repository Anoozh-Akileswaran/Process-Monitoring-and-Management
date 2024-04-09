#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main() {
    // PID of the process to be terminated
    pid_t pid;
    
    // Get PID from user input
    printf("Enter PID of the process to terminate: ");
    scanf("%d", &pid);

    // Send termination signal to the process
    if (kill(pid, SIGKILL) == 0) {
        printf("Process with PID %d terminated successfully.\n", pid);
    } else {
        perror("Error terminating process");
        return 1;
    }

    return 0;
}

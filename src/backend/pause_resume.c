#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main() {
    int pid;
    int choice;

    printf("Enter the process ID: ");
    scanf("%d", &pid);

    printf("Choose an action:\n");
    printf("1. Pause process\n");
    printf("2. Resume process\n");
    printf("Enter choice (1 or 2): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            // Send SIGSTOP to pause the process
            if (kill(pid, SIGSTOP) == 0) {
                printf("Successfully paused process %d\n", pid);
            } else {
                perror("kill");
                exit(EXIT_FAILURE);
            }
            break;
        
        case 2:
            // Send SIGCONT to resume the process
            if (kill(pid, SIGCONT) == 0) {
                printf("Successfully resumed process %d\n", pid);
            } else {
                perror("kill");
                exit(EXIT_FAILURE);
            }
            break;

        default:
            printf("Invalid choice\n");
            break;
    }

    return 0;
}

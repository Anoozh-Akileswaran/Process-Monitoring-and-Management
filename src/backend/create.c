#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    char program[100];
    
    // Prompt the user to enter the program name
    printf("Enter the program name: ");
    scanf("%s", program);

    // Fork a child process
    pid_t pid = fork();

    if (pid == -1) {
        // Fork failed
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // Child process
        // Execute the specified program
        if (execlp(program, program, NULL) == -1) {
            perror("execvp");
            return 1;
        }
    } else {
        // Parent process
        // Wait for the child process to finish
        int status;
        waitpid(pid, &status, 0);
        printf("Child process finished.\n");
    }

    return 0;
}

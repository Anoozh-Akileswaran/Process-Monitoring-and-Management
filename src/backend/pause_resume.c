#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <stdbool>


bool pause_resume(int choice, int pid) {

    switch (choice) {
        case 1:
            // Send SIGSTOP to pause the process
            if (kill(pid, SIGSTOP) == 0) {
                return true;
            } else {
                return false;
            }
            break;
        
        case 2:
            // Send SIGCONT to resume the process
            if (kill(pid, SIGCONT) == 0) {
                return true;
            } else {
                return false;
            }
            break;
    }

    return false;
}

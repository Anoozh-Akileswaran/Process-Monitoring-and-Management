#ifndef TOP_INFO_H
#define TOP_INFO_H

#define MAX_NAME_LENGTH 50

struct ProcessList {
    
    struct Process ProcessList[MAX_NAME_LENGTH];
    int number_Process;
};

// Function total amount of  CPU used
double getTotalProcess(struct ProcessList processlist);











#endif // TOP_INFO_H



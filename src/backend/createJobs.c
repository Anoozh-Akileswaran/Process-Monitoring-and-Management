#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* address_of_create_jobs = "/home/anoozh/Desktop/Operating-System/Project/PMM/Process-Monitoring-and-Management/src/backend/createJob.sh ";

void createJobs(char* jobs, char* parameter, int min, int hour, int days, int month, int weekday){

	 // Open the crontab file for editing
	 
    char min_str[10];
    snprintf(min_str, sizeof(min_str), "%d", min);
    char hour_str[10];
    char days_str[10];
    char month_str[10];
    char weekdays_str[10];
	 
    FILE *crontab = popen("crontab -", "w");
    if (crontab == NULL) {
        perror("Error opening crontab");
        return 1;
    }
    char time[40]; // Declare a character array to hold the concatenated string
    char space[2] = " ";
    char star[5] = "*";
    char new_line[3];
    
    // Initialize time with an empty string
    time[0] = '\0';
    char command[400];
    command[0] = '\0';
    new_line[0]= '\n';

    strcat(time, space);
    strcat(time, star);
    strcat(time, space);
    strcat(time, star);
    strcat(time, space);
    strcat(time, star);
    strcat(time, space);
    strcat(time, star);
    strcat(time, space);
    strcat(time, star);
    strcat(time, space);
    
    ///////////////////
    strcat(command, time);
    strcat(command, space);
    strcat(command, address_of_create_jobs);
    strcat(command, jobs);
    strcat(command, space);
    strcat(command, parameter);
    strcat(command, new_line);
    
    
    
/*     
    char* time = strcat(strcat(min, " "), (char)(hour));
    time = strcat(strcat(time, " "), (char)(days));
    time = strcat(strcat(time, " "), (char)(month));
    time = strcat(strcat(time, " "), (char)(weekday));
 */   
        // Add a new cron job to the crontab file
    fprintf(crontab, command);

    // Close the crontab file
    if (pclose(crontab) == -1) {
        perror("Error closing crontab");
        return 1;
    }

    printf("Cron job added successfully.\n");


    return 0;
    
}


int main(int argc, char *argv[]){
  printf("%d \n", argc);
  char* process = argv[1];
  printf("%s \n, %s\n, %s\n, %s\n, %s\n, %s\n", argv[1], argv[2], argv[3], argv[4], argv[5], argv[6] );
  char* parameter = argv[2];
    char* min = argv[3];
  char* hour= argv[4];
    char* days = argv[5];
  char* month = argv[6];
  char* weekdays = argv[7];
 
  createJobs(process, parameter, atoi(min), atoi(hour), atoi(days), atoi(month), atoi(weekdays));




}

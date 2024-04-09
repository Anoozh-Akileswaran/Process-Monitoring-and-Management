#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *cronFile;
    //whole address for
 

    // Open the cron job file in write mode
    cronFile = fopen("my_cron_job", "w");

    if (cronFile == NULL) {
        perror("Error creating cron job file");
        return 1;
    }

    // Write the cron job command to the file
    fprintf(cronFile, "# Cron job created by my C program\n");
    fprintf(cronFile, "*/1 * * * * echo \"Hello World\" >> /home/anoozh/Desktop/Operating-System/Project/file.txt\n");
    fprintf(cronFile, "# End of cron job\n");

    // Close the file
    fclose(cronFile);

    // Install the cron job
    system("crontab my_cron_job");

    printf("Cron job installed successfully.\n");

    return 0;
}

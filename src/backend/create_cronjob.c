#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdbool.h>

bool searchExecutable(const char *partialName, const char *directoryPath, char* parameter) {
    DIR *dir;
    struct dirent *entry;

    // Open the directory
    dir = opendir(directoryPath);
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    // Loop through directory entries
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, partialName) != NULL) {
            printf("%s/%s\n", directoryPath, entry->d_name);
	    printf("%s\n",entry->d_name);
            int status = system(strcat(strcat(entry->d_name, " "), parameter));
	    if(status == -1){
		return false;
	    }else{
		printf("Command executed\n");
		return true; 
		break;
	    }
        }
    }

    // Close the directory
    closedir(dir);
    return false;
}

bool create(char* name, char* parameter) {
    char partialName[256];  // Maximum length for the partial name
    const char *directories[] = {"/usr/bin", "/usr/local/bin"};  // Directories to search

    // Get the partial name from the user
    //printf("Enter the partial name: ");
    //fgets(partialName, sizeof(partialName), stdin);
    
    // Remove newline character from fgets
    size_t len = strlen(name);
    if (len > 0 && name[len - 1] == '\n') {
        name[len - 1] = '\0';
    }
    bool executed;
    // Search for executables in each directory
    for (size_t i = 0; i < sizeof(directories) / sizeof(directories[0]); ++i) {
        executed = searchExecutable(name, directories[i], parameter);
     if(executed==true){
        return true;
     }

    }

    return false;
}

int main(int argc, char *argv[]){

  char* process = argv[1];
  char* parameter = argv[2];
  create(process, parameter);




}

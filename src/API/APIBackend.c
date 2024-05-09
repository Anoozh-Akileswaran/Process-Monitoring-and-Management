#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <pthread.h>
#include "Process.h"
#include "ProcessList.h"
#include "API.h"
#include "monitor_tool.h"
#include "management_tool.h"
#include "plot_tool.h"
#include <stdbool.h>
#include <unistd.h>

pthread_mutex_t mutex_API = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_API2 = PTHREAD_MUTEX_INITIALIZER;

enum API_command {
     CREATE,
     TERMINATE,
     PAUSE,
     RESUME,
     SORT,
     TOTAL_CPU,
     TOTAL_RAM,
     TOTAL_MEMORY
     
}

//command= CREATE, SORT, PAUSE
//name = input for create
//pid = input for terminate, resume, pause
//metric = input for sort
bool API_call(char* command, char* name, int PID, char* metric){

    if (strcmp(command, "CREATE") == 0) {
        return create(char* name);
    } else if (strcmp(command, "TERMINATE") == 0) {
       
        return terminate(pid); 
    } else if (strcmp(command, "PAUSE") == 0) {
    	return pause_resume(1,pid);
       
    } else if (strcmp(command, "RESUME") == 0) {
    	return pause_resume(2,pid);
        
    } else if (strcmp(command, "SORT") == 0) {
    
    	return sortList(metric)
       
    } else {
        printf("Invalid command.\n");
    }







}







//Protect accessing List
//For reading and writing
struct ProcessList ListReadWrite(char* command){
    pthread_mutex_lock(&mutex_API);
    
    if (strcmp(command, "R")==0){
       //Command "R"
        pthread_mutex_unlock(&mutex_API);
    	return getUpdatedList();
    }else if(strcmp(command, "W")==0){
    //Command "W"
    	updateList();
    	pthread_mutex_unlock(&mutex_API);
    	return getUpdatedList()
    }else if(strcmp(command, "S")){
    
      	sortList(char* metric)
      	updateList();
      	pthread_mutex_unlock(&mutex_API);
      	return getUpdatedList()
    	
    }
    
    
}


//Can be used to read total values with "GTM" or "GTC" 
 double readTotal(char* command){
    pthread_mutex_lock(&mutex_API2);
 
   //GET TOTAL MEMORY
    if(strcmp(command, "GTM") == 0){
    		
    	pthread_mutex_unlock(&mutex_API2);
    	return total_cpu;
    //GETTOTALCPU
    }else if(strcmp(command, "GTC") == 0){
    
    
    	pthread_mutex_unlock(&mutex_API2);
    	return total_ram;
    }
    
    //update all values
    else if(strcmp(command, "U") == 0){
    
    	void getTotal();
    	pthread_mutex_unlock(&mutex_API2);
    	return o
    }
 
 
 
 
 
 }
    
    
    
    
void* loop_thread(void *arg){
        while (1){
    	
    		pthread_mutex_lock(&mutex_API2);
    		void readTotal("U");
    		pthread_mutex_unlock(&mutex_API2)
    		ListReadWrite("W");
    		sleep(3)
    
    	}
    
    
 
    }
    

//Create a thread, which loops over and
//Main-function     
void loopOver(){
  
    pthread_t thread_API;
    if (pthread_create(&thread_API, NULL, loop_thread, NULL) != 0){
    
    	 fprintf(stderr, "Error creating thread\n");
         return EXIT_FAILURE;
    
    
    }
    

    
}







































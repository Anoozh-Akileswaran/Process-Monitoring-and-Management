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
#include "MainList.h"
#include "MainTotalValues.h"



pthread_mutex_t mutex_API = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_API2 = PTHREAD_MUTEX_INITIALIZER;



//command= CREATE, SORT, PAUSE
//name = input for create
//pid = input for terminate, resume, pause
//metric = input for sort

 void API_call(char* command, char* name, int PID, char* metric){

    if (strcmp(command, "CREATE") == 0) {
         create(name);
    } else if (strcmp(command, "TERMINATE") == 0) {
       
        terminate(PID); 
    } else if (strcmp(command, "PAUSE") == 0) {
    	pause_resume(1,PID);
       
    } else if (strcmp(command, "RESUME") == 0) {
    	pause_resume(2,PID);
        
    } else if (strcmp(command, "SORT") == 0) {
    
    	sortList(metric);
       
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
    	//pthread_mutex_unlock(&mutex_API2);
    	return getUpdatedList();
    }else if(strcmp(command, "S")){
    
      	//sortList(metric);
      	pthread_mutex_unlock(&mutex_API);
      	return getUpdatedList();
    	
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
    else if(strcmp(command, "UPDATE") == 0){
    	getTotal();
    	//pthread_mutex_unlock(&mutex_API2);
    	return 0;
    }
 
 
 
 
 
 }
    
    
    
    
void* loop_thread(void *arg){
        while (true){
    		
    		
    		readTotal("UPDATE");
    		pthread_mutex_unlock(&mutex_API2);
    		
    		//ListReadWrite("W");
    		//pthread_mutex_unlock(&mutex_API);
    		sleep(3);
    		 //pthread_exit(NULL);	
    
    	}
    
    
 
}
    

//Create a thread, which loops over and
//Main-function     
void loopOver(){
 
    pthread_t thread_API;
    if (pthread_create(&thread_API, NULL, loop_thread, NULL) != 0){
    	 fprintf(stderr, "Error creating thread\n");
         //return EXIT_FAILURE;
    
    
    }
      if (pthread_join(thread_API, NULL) != 0) {
        perror("pthread_join");
        return 1;
    }
  

    
}


extern struct ProcessList getUpdatedList(){
    pthread_mutex_t mutex_process = PTHREAD_MUTEX_INITIALIZER;
     
     pthread_mutex_lock(&mutex_process);
   
     
     pthread_mutex_unlock(&mutex_process);
     return processList;
     
}







int main(){
	
	API_call("RESUME", " ", 12889, " ");
	return 0;

}







































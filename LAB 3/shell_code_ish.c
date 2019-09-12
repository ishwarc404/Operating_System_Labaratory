#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

//this whole function is basically doing the job of argv and argc
char** spl(char* line)
{  
    char *token = strtok(line, " "); //here instead of using a character datastructure, we are just using a pointer
    char **wd = malloc(6*sizeof(char*)); 

    /* DYNAMICALLY CREATING A 2D ARRAY
    char **array1 = malloc(nrows * sizeof(char *)); // Allocate row pointers
    for(i = 0; i < nrows; i++)
         array1[i] = malloc(ncolumns * sizeof(char));  // Allocate each row separately
         //WE ARE DOING THIS ONLY IN LINE 22
    */

    int i = 0;
    while (token != NULL) //while the pointer token does not point to nothing
    { 
        //puts(token);
        wd[i] = token; //put the first arg in wd[0] and continue
        
        /*If you pass a non-NULL value, you are asking it to start tokenizing a different string.
        If you pass a NULL value, you are asking to continue tokenizing the same thing as before.*/
        token = strtok(NULL, " ");
        
        //puts(token);
        i++; //increment the value of i to store value in 2nd 3rd 4th row respectively as they come //6 values at most
    } 

  	wd[i] = (char*)0; 

    return wd; //return the 2d array pointer
}

int main(void) {
    char line[1024];
    char **args = malloc(8*sizeof(char*)); //this 2d pointer basicall = wd 
    while(1) 
    {
        printf("$NEWSHELL ");
        if(!fgets(line, 1024, stdin)) break;
        //if(!scanf("%s",line)) break;
        char *p = strchr(line, '\n'); //gets a pointer to \n 
        if (p) *p = 0;
        if(strcmp(line, "exit")==0) break; //if exit is entered, end program by breaking out
        args = spl(line); //split the input line into its arguments

   	int processid = fork();    //create a child process       
        if(processid==0) {       //if child process created        
            execvp(args[0], args); //execute
            perror("Error"); //else error //thses are system calls
            exit(1);
        } 
        else {                    
            wait(NULL);
        }
        
        
    }

    return 0;
}



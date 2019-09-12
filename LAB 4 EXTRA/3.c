
#include<stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 

int main() 
{ 
	// Create a child process	 
	int pid = fork(); 

	if (pid > 0) 
	{
		printf("in parent process"); 
		printf("Parent: %d ---> Child: %d \n",getppid(),getpid());
		sleep(10); //sleep makes the child alive for 30 secs, so parents dies
		printf("Parent: %d ---> Child: %d \n",getppid(),getpid());
		
	}

	// Note that pid is 0 in child process 
	// and negative if fork() fails 
	else if (pid == 0) 
	{ 
		
	} 

	return 0; 
} 


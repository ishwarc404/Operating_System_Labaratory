
#include<stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 

int main() 
{ 
	// Create a child process
	
	int pid = fork(); 

	if (pid > 0) 
	{
		char c;
		for(c='A';c<='Z';c++)
		{
		 printf("%c\n",c);
		 sleep(2);
		
		}
		
	}

	// Note that pid is 0 in child process 
	// and negative if fork() fails 
	else if (pid == 0) 
	{ 
		char c;
		for(c='a';c<='z';c++)
		{
		 printf("%c\n",c);
		 sleep(2);
		
		}
	} 

	return 0; 
} 


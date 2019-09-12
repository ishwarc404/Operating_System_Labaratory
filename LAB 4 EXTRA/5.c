
#include<stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 

int glo[5] = {1,1,1,1,1};
int main() 
{ 
	// Create a child process
	
	int pid = fork(); 
	int loc[5] = {1,1,1,1,1};
	if (pid > 0) 
	{
		int c;
		for(c=0;c<5;c++)
		{
		 glo[c] = 9;
		  loc[c] = 9;
		 printf("%d\n",glo[c]);
		 printf("%d\n",loc[c]);
		}
		
	}

	// Note that pid is 0 in child process 
	// and negative if fork() fails 
	else if (pid == 0) 
	{ 
		printf("Child:");
		int c;
		for(c=0;c<5;c++)
		{
		 //glo[c] = 9;
		 printf("%d\n",glo[c]);
		  printf("%d\n",loc[c]);
		}
	} 

	return 0; 
} 


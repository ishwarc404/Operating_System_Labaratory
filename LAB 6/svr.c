#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h> 	
#include <dirent.h>

#include <pthread.h>          // Threads, link with lpthread
#include <semaphore.h>        // Semaphore init(), sem_wait() and sem_post()


#define LIST "list"
#define GET "get"


//THREADING VARIABLES
void *Producer();
void *Consumer();
int BufferIndex=0;
char *BUFFER;
int read_check;

int sockfd = 0;				        // listen - listen file descriptor
int connfd = 0;					// connect - connect file descriptor
char recvBuff[256];	
unsigned char buff[256] = {0};


int main(void)
{
			
	struct sockaddr_in serv_addr;			// A sockaddr_in is a structure containing an internet address. 					// This structure is defined in <netinet/in.h>.
	char sendBuff[1024];
	int numrv;
	char filename[1024];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);	// listen - listen for connections on a socket
							// AF_INET refers to the address family ipv4. 
							// The SOCK_STREAM means connection oriented TCP protocol.

	//printf("Socket retrieve success\n");

  	memset(&serv_addr, '0', sizeof(serv_addr));	// memset() is used to fill a block of memory with a particular value.
	memset(sendBuff, '0', sizeof(sendBuff));

	serv_addr.sin_family = AF_INET;			// A sockaddr_in is a structure containing an internet address. 
							// This structure is defined in <netinet/in.h>.

	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);	
	serv_addr.sin_port = htons(5050);		// port:5050

	bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));	//        bind - bind a name to a socket


	if (listen(sockfd, 10) == -1)			// listen - listen for connections on a socket
  	{
		printf("Failed to listen\n");
		return -1;
  	}
    else
    printf("In the server");
	while (1)
  	{


		// If client sends a GET

		if (strcmp(GET, recvBuff) == 0)	// Compares string GET received from recvBuff sent by client
		{


			//thread code

				pthread_t ptid,ctid;
				BUFFER=(char *) malloc(sizeof(char) * 256);   

			    pthread_create(&ptid,NULL,Producer,NULL);
				pthread_create(&ctid,NULL,Consumer,NULL);
				
				pthread_join(ptid,NULL);
				pthread_join(ctid,NULL);

				sleep(3);		// Suspend for 3 seconds
			

					
		}
			
    }
		
       
  	return 0;
}



//PRODUCER AND CONSUMER CODE
void *Producer()
{    

	read(connfd,recvBuff,sizeof(recvBuff));
    // TODO:  Read the name of the file sent by the client using the connfd file descriptor.
	char filename[256];
	int n=read(connfd,recvBuff,sizeof(recvBuff));

	// TODO:  Copy the file name sent from the recbuff to a filename string and later open the file using open system call.
	int file=open(recvBuff,O_RDONLY);
	/*TODO:  Read data from file and send it */

	/*TODO:  First read file in chunks of 256 bytes */
	
	//we read the contents of the "file" into the variable buffer in chucks of 256 bytes
	read_check = read(file,buff,sizeof(buff));
	/*TODO:  If read was success, send data to the client using connfd*/
	//if read_check is 1, send data to the user    
    
}

void *Consumer()
{
    printf("in the consumer");

    if(read_check>0)
	{
		write(connfd,buff,sizeof(buff));
	}
}
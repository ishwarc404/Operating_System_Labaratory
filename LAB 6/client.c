

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#define LIST "list"
#define GET "get"

int main(int argc, char **argv) 
{
	int sockfd = 0;					// sockfd - socket file descriptor
	int bytesReceived = 0;				// Bytes received from server
	char recvBuff[256];				// Buffer to receive bytes from server

	memset(recvBuff, '0', sizeof(recvBuff));	// memset() is used to fill a block of memory with a particular value.

	struct sockaddr_in serv_addr;			// A sockaddr_in is a structure containing an internet address. 
							// This structure is defined in <netinet/in.h>.

		  /* Create a socket first */

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 		// Create socket
	{
		printf("\n Error : Could not create socket \n");
	        return 1;
  	}


	  /* Initialize sockaddr_in data structure */

	serv_addr.sin_family = AF_INET;				
	serv_addr.sin_port = htons(5050);  			// port:5050
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");	// local host IP address: 127.0.0.1


	  /* Attempt a connection */

	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) // connect - initiate a connection on a socket.
	{
		printf("\n Error : Connect Failed \n");
		return 1;
	}
	int fr;
	if (strcmp(LIST, argv[1]) == 0)		// Compares string LIST received from argument given by client
  	{
		
		
		// TODO:  Send LIST to the server using the write() system call using the "sockfd" file descriptor
		write(sockfd,LIST,256);
		// TODO:  Use read() system call within a loop to read from the server using the "sockfd" file descriptor
		//int fr=read(sockfd,recvBuff,256);
		//printf("%s\n",recvBuff);
		while(fr=read(sockfd,recvBuff,256))
		{
			//fr=read(sockfd,recvBuff,256);
			printf("%s\n",recvBuff);
		}
			
  	}

		 /*Create file where data will be stored */

	if (strcmp(GET, argv[1]) == 0)		// Compares string GET received from argument given by client
	{
		printf("In the get of client\n");
		// TODO:  Send GET to the server using the "sockfd" file descriptor
		// TODO:  Send the filename to the server using the "sockfd" file descriptor
		// TODO:  Create a file with the same name as sent by client with get argument using the open() system call using appropriate flags 
                          // to save the file contents received from server from the recBuff

		/*TODO:  Receive data in chunks of 256 bytes */
    		// TODO:  Use the read() system call within a loop to fetch the contents of the file from the server using sockfd
		// TODO:  Use the write() system call to write those contents in the file which was created above.
		fr=write(sockfd,argv[1],256);
		fr=write(sockfd,argv[2],256);
		int file=open(argv[2],O_CREAT);
		while(1)
		{
			fr=read(sockfd,recvBuff,256);

			if(fr==0)
			{
				puts("done");
				break;
			}
			printf("%s\n",recvBuff);
			write(file,recvBuff,256);
		}
		
    	}
  

	return 0;
}

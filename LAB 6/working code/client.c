#include <arpa/inet.h>	//inet_addr
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
	int bytesReceived = 0;			// Bytes received from server
	char recvBuff[256];				// Buffer to receive bytes from server

	memset(recvBuff, '0', sizeof(recvBuff));	// memset() is used to fill a block of memory with a particular value.

	struct sockaddr_in serv_addr;				// A sockaddr_in is a structure containing an internet address. 
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

	/*Create file where data will be stored */

	if (strcmp(GET, argv[1]) == 0)		// Compares string GET received from argument given by client
	{
		// TODO:  Send GET to the server using the "sockfd" file descriptor
		write(sockfd, argv[1], sizeof(argv[1]));
		sleep(3);
		// TODO:  Send the filename to the server using the "sockfd" file descriptor
		int val = write(sockfd, (const char*) argv[2], strlen(argv[2])+1);
		printf("val: %d\n", val);
		// TODO:  Create a file with the same name as sent by client with get argument using the open() system call using appropriate flags 
		// to save the file contents received from server from the recBuff
		int newfd = open("test_out.txt",O_WRONLY|O_CREAT,0777);
		// TODO:  Receive data in chunks of 256 bytes
		int bytesWritten = 0;
		int bytesRead = 256;
		// TODO:  Use the read() system call within a loop to fetch the contents of the file from the server using sockfd
		// TODO:  Use the write() system call to write those contents in the file which was created above.
		while(bytesRead >= 256)
		{
			bytesRead = read(sockfd, recvBuff, sizeof(recvBuff));
			printf("Bytes read :%d\n", bytesRead);
			bytesWritten += write(newfd, recvBuff, bytesRead);
		}
		close(newfd);
		printf("Bytes written: %d\n", bytesWritten);
    }
	return 0;
}






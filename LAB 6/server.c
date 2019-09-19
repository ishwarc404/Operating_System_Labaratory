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

int main(void)
{		
	struct sockaddr_in serv_addr;			// A sockaddr_in is a structure containing an internet address. 
							// This structure is defined in <netinet/in.h>.
	char sendBuff[1024];
	int numrv;
	char filename[1024];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);	// listen - listen for connections on a socket
							// AF_INET refers to the address family ipv4. 
							// The SOCK_STREAM means connection oriented TCP protocol.

	printf("Socket retrieve success\n");

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

	while (1)
  	{
		connfd = accept(sockfd, (struct sockaddr *)NULL, NULL);

		// TODO:  Read if the client wants a GET or a LIST using a read() systemcall.
		//printf("data recieved");
		int data ;
		data = read(connfd,recvBuff,sizeof(recvBuff));
		

		// If client sends a GET

		if (strcmp(GET, recvBuff) == 0)	// Compares string GET received from recvBuff sent by client
		{
			sleep(3);		// Suspend for 3 seconds
			
			// TODO:  Read the name of the file sent by the client using the connfd file descriptor.
			char filename[256];
			int n=read(connfd,recvBuff,sizeof(recvBuff));

			// TODO:  Copy the file name sent from the recbuff to a filename string and later open the file using open system call.
			int file=open(recvBuff,O_RDONLY);
			     /*TODO:  Read data from file and send it */

			while (1)
		        {
			        /*TODO:  First read file in chunks of 256 bytes */

			        unsigned char buff[256] = {0};
					//we read the contents of the "file" into the variable buffer in chucks of 256 bytes
					int read_check = read(file,buff,sizeof(buff));
			        /*TODO:  If read was success, send data to the client using connfd*/
					//if read_check is 1, send data to the user
					if(read_check>0)
					{
						write(connfd,buff,sizeof(buff));
					}
		        }
				close(file);
				close(connfd);
        }

			    // If client sends a LIST
	
		if (strcmp(LIST, recvBuff) == 0)	// Compares string LIST received from recvBuff sent by client
		{ 
			      			// If list is sent by the client.
		      DIR *d;
		      
		      struct dirent *dir;	
			
		      d = opendir(".");		// Open the current directory. "." means current directory
		      
		
		      if (d)			// d points to the current directory
		      {

				while ((dir = readdir(d)) != NULL)	// read the current directory until end of directory
				{
					printf("somthing is sent");
				         // TODO:  send the names of the file using the write() system call using connfd.
					 write(connfd,dir->d_name,sizeof(dir->d_name));
  					 // TODO:  Use man page of readdir to figure out how to use the "dir" variable
				}
				closedir(d);	// Close the current directory
		     }
		}
                close(connfd);		// Close the socket connection
		sleep(1);		// Suspend for 1 second
         }   
  	         return 0;
}
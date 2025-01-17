#include <stdio.h>
#include <stdlib.h>  	      // strlen function
#include <string.h>           // strlen function
#include <sys/socket.h>       // socket system calls
#include <unistd.h>           // write system calls
#include <arpa/inet.h>        // inet_addr structure
#include <fcntl.h>            // O_RDONLY flag
#include <pthread.h>          // Threads, link with lpthread
#include <semaphore.h>        // Semaphore init(), sem_wait() and sem_post()

#define BUF_LEN 4096		// Buffer Length constant size

int *new_sock;			// Pointer variable to Client socket

pthread_t t_producer;		// Producer Thread Variable
pthread_t t_consumer;		// Consumer Thread Variable

sem_t buf_mutex, empty_count, fill_count;	// Mutex variables
						// buf_mutex checks buffer LOCKED(0) or UNLOCKED(1)
						// empty_count checks buffer EMPTY(0) or NOTEMPTY(1)
						// fill_count checks buffer FULL(0) or NOTFULL(1)

char buff[BUF_LEN];				// Character buffer array
int server_socket, client_sock, c;		// Client and Server Socket variable

struct sockaddr_in server, client;		// Address structure for Client and Server


int produce()
{
  // TODO:  Use open() system call to open the file and write it to a character buffer "buff"
    // open(client_sock,buff,BUF_LEN);
    int fd=open("text.txt",O_RDONLY);
    int r=read(fd,buff,256);
    printf("In producer\n");
}

int consume()
{
    sleep(3);

    int sock = *(int *)new_sock;

    write(sock, buff, BUF_LEN);

    printf("In consumer %s",buff);

    // TODO:  Read from the buffer written in produce() function and send it to client using write() system call, using the "sock" file descriptor.
}

void* producer(void *args)
{
	// TODO:  Use the three mutex variables, use sem_wait() and sem_post()
    sem_wait(&buf_mutex);
    //if(sem_wait(fill_count))
    // if(strlen(buff)>BUF_LEN){
    //     sem_wait(&empty_count);   //wait on full
    // }
    sem_wait(&empty_count);

	printf("\nProducer Created\n");	
	produce();  //critical section
    sem_post(&fill_count);
    sem_post(&buf_mutex);
	return NULL;
}


void* consumer(void *args)
{
	// TODO:  Use the three mutex variables, use sem_wait() and sem_post()
    sem_wait(&buf_mutex);
    // if(strlen(buff)==0){
    //     sem_post(&empty_count);
    // }
    //wait till it is 
    sem_wait(&fill_count);
	printf("Consumer Created\n\n");
	consume();
    sem_post(&empty_count);
    sem_post(&buf_mutex);

	return NULL;
}

int main(void) 
{
	server_socket = socket(AF_INET, SOCK_STREAM, 0);    	// Create socket

	if (server_socket == -1) 				// Check create Socket ERROR=-1
    	{
	      	printf("\nCould not create Socket\n");
    	}

        puts("\nSocket created\n");				// Print Socket Created Sucessfully	

		// Prepare the sockaddr_in structure

        server.sin_family = AF_INET;				// Intialize Address Family
        server.sin_addr.s_addr = INADDR_ANY;			// Intialize Address Type
        server.sin_port = htons(5050);				//Port No :5050

		// Bind socket with sockaddr_in structure

        if(bind(server_socket, (struct sockaddr *)&server, sizeof(server))<0) 
        {
           perror("\nBind Failed. Error\n");	// Print the bind ERROR=-1 message

           return 1;
        }

        puts("\nBind Done\n");			// Bind Successful

        for (size_t i = 0; i < BUF_LEN; i++) 	// Intialize Buffer with 0
        {
           buff[i] = 0;
        }

        listen(server_socket, 3);		// Server Listens, Backlog=3 Clients

        c = sizeof(struct sockaddr_in);

        // Accept and incoming connection

        puts("Waiting for incoming connections...");

        client_sock=accept(server_socket,(struct sockaddr *)&client,(socklen_t *)&c); // Server accepts connection

        new_sock = malloc(1);			// Allocate memory to pointer variable to Client socket

       *new_sock = client_sock;			// Assigning Client socket variable to newly created pointer variable.

       int err;					// Error variable

       sem_init(&buf_mutex, 0, 1);		// Intialize buf_mutex to 1(BUFFER UNLOCKED/FREE), 0 means Threads
       sem_init(&fill_count, 0, 0);		// Intialize fill_count to 0 (BUFFER FULL)
       sem_init(&empty_count, 0, BUF_LEN); 	// Intialize empty_count to BUF_LEN=4096 (EMPTY)

    // TODO: Create 2 threads t_producer and t_consumer, with producer() and consumer() as their callback functions.
    
    pthread_create(&t_producer,NULL,producer,(void*)&t_producer);
    pthread_create(&t_consumer,NULL,consumer,(void*)&t_consumer);
    // TODO: Join the 2 threads
    pthread_join(t_producer,NULL);
    pthread_join(t_consumer,NULL);
	close(server_socket); 		// Server Wait/Join for Producer Thread to complete
        close(client_sock);		// Server Wait/Join for Consumer Thread to complete

	return 0;
}


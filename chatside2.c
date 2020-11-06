#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>

#define PORT 8000

void *receiving_function(void *ptr);
void *user_input(void *ptr);
int sockfd;
struct sockaddr_in my_addr;
struct sockaddr_in to_addr;
int my_addrlen;
int to_addrlen;

int main(){
	printf("Started\n");
	
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0))<0){
		perror("Socket Creation Failed");
		exit(0);
	}
	
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(PORT);
	my_addr.sin_addr.s_addr = inet_addr("127.0.0.2");
	memset(&(my_addr.sin_zero),'\0', 8); 
	printf("My Address Assigned\n");
	my_addrlen = sizeof(struct sockaddr_in);
	
	to_addr.sin_family = AF_INET;
	to_addr.sin_port = htons(PORT);
	to_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(&(to_addr.sin_zero),'\0', 8); 
	printf("To Address Assigned\n");
	to_addrlen= sizeof(struct sockaddr_in);	
	int ret;
	if(ret = bind(sockfd, (struct sockaddr*) &my_addr, sizeof(struct sockaddr))){
		perror("Bind Failed");
		exit(0);
	}

	pthread_t thread1, thread2;
	pthread_create(&thread1, NULL, receiving_function, (void*) "Receiving\0");
	pthread_create(&thread2, NULL, user_input, (void*) "Waiting for User Input\0");
	
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
}


void *receiving_function(void* ptr){
	printf("Receiving Activated\n");
	char* message=malloc(sizeof(char)*100);		
	while(1){	
		memset(message,'\0', 100);	
		recvfrom(sockfd, message, 100, 0, (struct sockaddr*) &to_addr,(socklen_t*) &my_addrlen);
		printf("Received: %s", message);
		printf("\n");
	}
}

void *user_input(void* ptr){
	char* message=malloc(sizeof(char)*100);	
	while(1){
		memset(message,'\0', 100);		
		//printf("Enter your message to send\n");	
		fgets(message, 100, stdin);
		message[strlen(message)-1]='\0';
		//printf("%s Message Sending\n", message);
		int ret = sendto(sockfd,  message, strlen(message), 0, (struct sockaddr*) &to_addr, (socklen_t) to_addrlen);
		if(ret==0){
			perror("Error while sending");
		}
		//printf("Message Sent\n");
	}
}


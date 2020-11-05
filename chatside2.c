#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#define PORT 8100



	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in *my_addr;
	my_addr->sin_family = AF_INET;
	my_addr->sin_port = htons(8080);
	inet_aton("10.0.0.6", &(my_addr->sin_addr));
	memset(&(my_addr->sin_zero),'\0', 8); 
	
	struct sockaddr_in *to_addr;
	to_addr->sin_family = AF_INET;
	to_addr->sin_port = htons(PORT);
	inet_aton("10.0.0.5", &(to_addr->sin_addr));
	memset(&(to_addr->sin_zero),'\0', 8); 

	bind(sockfd, (struct sockaddr*) my_addr, sizeof(stuct sockaddr));	

	// TODO: Create two processes. One will wait for message to come and when it comes, it will show the message. Other will wait for the user to send a message and when the user sends a message, it will handle the process.

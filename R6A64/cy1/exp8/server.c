#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>

void main(int argc, char* argv[]) {
	int server_fd, code;
	struct sockaddr_in serv_addr, cli_addr;
	
	int PORT;
	
	if(argc == 2)
		PORT = atoi(argv[1]);
	else {
		printf("Enter Time Server port!\n");
		exit(1);
	}
	
	printf("Concurrent Time Server\n");
	
	if((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("Socket creation failed!\n");
		exit(1);
	}
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(PORT);
	
	if(bind(server_fd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
		printf("Binding failed!\n");
		exit(1);
	}
	
	int len = sizeof(cli_addr);
	
	while(1) {
    		if(recvfrom(server_fd, &code, sizeof(int), 0, (struct sockaddr*) &cli_addr, &len) < 0) {
    			printf("Receive failed!\n");
			exit(1);
		} else if (fork() == 0) {
			printf("Received time request.\n");
			
			time_t now = time(0);
			char* str = ctime(&now);
			
			if(sendto(server_fd, str, (strlen(str) + 1) * sizeof(char), 0, (struct sockaddr*) &cli_addr, len) < 0) {
				printf("Sending failed!\n");
				exit(1);
			} else {
				printf("Time reply sent.\n");
			}
			
			return;
    		}
    	}
    	
    	close(server_fd);
}

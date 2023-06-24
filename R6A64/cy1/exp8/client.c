#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

void main() {
	struct sockaddr_in serv_addr;
	int client_fd, PORT, code = 101, len = sizeof(serv_addr);
	char time[30];
	
	printf("Time Client\n");
	
	if((client_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("Socket creation failed!\n");
		exit(1);
	}
	
	while(1) {
		printf("Enter Time Server port: ");
		scanf("%d", &PORT);
		
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = INADDR_ANY;
		serv_addr.sin_port = htons(PORT);
		
		if(sendto(client_fd, &code, sizeof(int), 0, (struct sockaddr*) &serv_addr, len) < 0) {
			printf("Sending failed!\n");
			exit(1);
		} else {
			if(recvfrom(client_fd, time, 30 * sizeof(char), 0, (struct sockaddr*) &serv_addr, &len) < 0) {
	    			printf("Receive failed!\n");
				exit(1);
			} else {
				printf("Received time from Time Server %d: %s", PORT, time);
	    		}
		}
	}
	
    	close(client_fd);
}


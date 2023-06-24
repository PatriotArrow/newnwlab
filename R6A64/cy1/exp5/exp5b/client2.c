#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 8000
#define PORT1 8001

void main() {
	int client_fd;
	struct sockaddr_in serv_addr;
	struct sockaddr_in cli_addr;
	int num, opt, len = sizeof(serv_addr);
	
	printf("Enter 1 (TCP) or 2 (UDP): ");
	scanf("%d", &opt);
	
	if(opt == 1)
		printf("TCP Client\n");
	else if(opt == 2)
		printf("UDP Client\n");
	else {
		printf("Invalid input!\n");
		exit(1);
	}
	
	if(opt == 1) {
		if((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
			printf("Socket creation failed!\n");
			exit(1);
		} else {
			printf("Client socket created.\n");
		}
	} else {
		if((client_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
			printf("Socket creation failed!\n");
			exit(1);
		} else {
			printf("Client socket created.\n");
		}
	}
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(PORT);
	
	cli_addr.sin_family = AF_INET;
	cli_addr.sin_addr.s_addr = INADDR_ANY;
	cli_addr.sin_port = htons(PORT1);
	
	if(opt == 1) {
		if(connect(client_fd, (struct sockaddr*) &serv_addr, len) < 0) {
			printf("Connection failed!\n");
			exit(1);
		} else {
			printf("Connection established.\n");
		}
	}
	
	if(opt == 1) {
		if(recv(client_fd, &num, sizeof(int), 0) < 0) {
			printf("Receive failed!\n");
			exit(1);
		} else {
			printf("Squared number received: %d\n", num);
		}
	} else {
		if(bind(client_fd, (struct sockaddr*) &cli_addr, sizeof(cli_addr)) < 0) {
			printf("Socket binding failed!\n");
			exit(1);
		} else {
			printf("Socket binded.\n");
		}
		
		if(recvfrom(client_fd, &num, sizeof(int), 0, (struct sockaddr*) &serv_addr, &len) < 0) {
			printf("Receive failed!\n");
			exit(1);
		} else {
			printf("Squared number received: %d\n", num);
		}
	}
	
	close(client_fd);
}

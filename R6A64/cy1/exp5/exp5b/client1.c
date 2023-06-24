#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 8000

void main() {
	int client_fd;
	struct sockaddr_in serv_addr;
	int num, opt;
	
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
	
	if(opt == 1) {
		if(connect(client_fd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
			printf("Connection failed!\n");
			exit(1);
		} else {
			printf("Connection established.\n");
		}
	}
	
	printf("Enter integer: ");
	scanf("%d", &num);
	
	if(opt == 1) {
		if(send(client_fd, &num, sizeof(int), 0) < 0) {
			printf("Send failed!\n");
			exit(1);
		} else {
			printf("Integer sent: %d\n", num);
		}
	} else {
		if(sendto(client_fd, &num, sizeof(int), 0, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
			printf("Send failed!\n");
			exit(1);
		} else {
			printf("Integer sent: %d\n", num);
		}
	}
	
	close(client_fd);
}

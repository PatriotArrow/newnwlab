#include <arpa/inet.h>  
#include <stdio.h>  
#include <string.h>  
#include <sys/socket.h>  
#include <unistd.h>  
#define PORT 8080  
int main(int argc, char const* argv[])  
{  
       int sock = 0, valread, client_fd;  
       struct sockaddr_in serv_addr;  
       char* hello = "Hello message from client";  
       char buffer[1024] = { 0 };  
       if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
       {  
               printf("\n Socket creation error \n");  
               return -1;  
       }   
       else
       {
       		printf("\nSocket created\n");
       }
       serv_addr.sin_family = AF_INET;  
       serv_addr.sin_port = htons(PORT);  
       // Convert IPv4 and IPv6 addresses from text to binary form  
       if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {  
               printf("\nInvalid address/ Address not supported \n");  
               return -1;  
       }  
       if ((client_fd  = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {  
               printf("\nConnection Failed \n");  
               return -1;  
       }  
       else
       {
       		printf("\nConnection successful\n");
       }
       send(sock, hello, strlen(hello), 0);  
       printf("Hello message sent\n");  
       valread = read(sock, buffer, 1024);  
       printf("%s\n", buffer);   
       close(client_fd);  
       return 0;  
}  

#include<arpa/inet.h>
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
int main()
{
	char message[100];
	int clsoc=socket(AF_INET,SOCK_STREAM,0);
	if(clsoc==-1)
	{
		printf("Failed to create socket");
	}
	struct sockaddr_in server;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_family= AF_INET;
	server.sin_port=htons(8000);
	if(connect(clsoc,(struct sockaddr*)&server,sizeof(server))<0)
	{
		printf("Connection failed\n");
		return -1;
	}
	printf("Connected to Haiku server successfully\n\n");
	printf("Requesting haiku...\n\n\nHaiku poem:\n\n");
	recv(clsoc,message,sizeof(message),0);
	printf("%s\n",message);
	close(clsoc);
	return 0;
}

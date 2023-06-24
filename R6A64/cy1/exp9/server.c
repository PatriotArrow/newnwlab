#include<arpa/inet.h>
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
int main()
{
	char message[100]="Friday comes in bright\nFills my heart with such delight\nSoon my feet take flight\n";
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		printf("Socket C");
	}
	struct sockaddr_in server;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_family=AF_INET;
	server.sin_port=htons(8000);
	if(bind(sockfd,(struct sockaddr*)&server,sizeof(server))<0)
	{
		printf("Binding failed\n");
		return -1;
	}
	if(listen(sockfd,10)<0)
	{
		printf("Listen failed\n");
		return -1;
	}
	int c=sizeof(server);
	int sockfdnew=accept(sockfd,(struct sockaddr*)&server,(socklen_t*)&c);
	printf("\nHaiku poem:\n\n");
	send(sockfdnew,message,sizeof(message),0);
	printf("%s\n",message);
	close(sockfd);
	return 0;
}

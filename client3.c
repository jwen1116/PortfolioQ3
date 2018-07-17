#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int sd;
	struct sockaddr_in addr_server;
	char client_mes[2000],reply_server[2000];


	sd=socket(PF_INET,SOCK_STREAM,0);
	if (sd==-1)
	{
		printf("Socket cannot be created!");
	}
	puts("Socket created");

	addr_server.sin_family=AF_INET;
	addr_server.sin_port=htons(33333);
	addr_server.sin_addr.s_addr=inet_addr("127.0.0.1");


	if (connect(sd,(struct sockaddr *)&addr_server,sizeof(addr_server)) < 0)
	{
		perror("Error!Fail to connect!");
		return 1;
	}
	puts("Connected\n");

	if (recv(sd,reply_server,2000,0) >0){
		printf("%s",reply_server);
		memset(reply_server,0,2000);
	}

	if (recv(sd,reply_server,2000,0) >0){
		printf("%s",reply_server);

		memset(reply_server,0,2000);
	}


	while(1)
	{
		printf("Enter the word you would like me to repeat:");
		scanf("%s",client_mes);

		if (send(sd,client_mes,strlen(client_mes),0) < 0)
		{
			puts("Fail to send");
			return 1;
		}

		if (recv(sd,reply_server,2000,0) < 0)
		{
			puts("Fail to recv");
			break;
		}
		else{	
			printf("Server reply: %s\n\n",reply_server);
			memset(reply_server,0,2000);
		}
	}

	close(sd);
	return 0;
}



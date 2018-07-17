#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


void *connection_handler(void *);


int main(int argc,char *argv[]){
	int sd,cs,c,*new_sock;
	struct sockaddr_in addr_server,addr_client;

	sd=socket(PF_INET,SOCK_STREAM,0);

	if (sd==-1){
		perror("Socket cannot be created");
	}
	puts("Socket created");

	
	addr_server.sin_family=AF_INET;
	addr_server.sin_port=htons(33333);
	addr_server.sin_addr.s_addr=INADDR_ANY;

	if (bind(sd,(struct sockaddr *)&addr_server,sizeof(addr_server))<0)
	{
		perror("Error! Bind failed.");
		return 1;
	}
	puts("Bind done!");

	listen(sd,20);

	puts("Waiting for incoming connections...");
	c=sizeof(struct sockaddr_in);

	while ((cs=accept(sd,(struct sockaddr *)&addr_client,(socklen_t*)&c)))
	{
		puts("Connection accepted");

		pthread_t pthread_id;
		new_sock=malloc(1);
		*new_sock=cs;
		if (pthread_create(&pthread_id,NULL,connection_handler,(void*) new_sock) <0)
		{
			perror("Thread cannot be created!");
			return 1;
		}
		puts("Handler assigned!");
	}

	if (cs<0)
	{
		perror("Accept failed!");
		return 1;
	}

	return 0;
}


void *connection_handler(void *sd)
{
	int sock=*(int*)sd;
	int read_len;
	char *mes,client_mes[2000];

	mes="Hello! Welcome to Linux! I am the one who responsible in handling connection\n";
	write(sock,mes,strlen(mes));


	mes="Try typing something! I will repeat what you have typed.\n\n";
	write(sock,mes,strlen(mes));

	while ((read_len=recv(sock,client_mes,2000,0))>0)
	{
		write(sock,client_mes,strlen(client_mes));
		memset(client_mes,0,2000);
	}

	if (read_len==0)
	{
		puts("Client disconnected");
		fflush(stdout);
	}
	else if (read_len==-1)
	{
		perror("Fail to recv");
	}

	free(sd);

	return 0;
}

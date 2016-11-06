#include<stdio.h>
#include<stdlib.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<time.h>

int main(int argc , char *argv[])
{
	int socket_desc ,client_socket, c,read_size,i=0,j=0;
	struct sockaddr_in server , client;
	char *message,client_message[2000],*a,*answer,num_str[4];

	unsigned seed;
	seed=(unsigned)time(NULL);
	srand(seed);
	char ran_num[4]={rand()%10,rand()%10,rand()%10,rand()%10};
	for (i=0;i<4;i++)
	{
		while (j<4)
		{
			if (i==j)
				j=j+1;
			else
			{
				if (ran_num[i] == ran_num[j])
				{
					ran_num[i]=rand()%10;
					j=0;
				}
				else
					j=j+1;
			}
		}
		j=0;
	}
	

	for (i=0;i<4;i++)
	{
		printf("%d",ran_num[i]);
	}
    
	printf("\n");
	
	
	
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8888 );
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("bind failed");
		return 1;
	}
	puts("bind done");
	//Listen
	listen(socket_desc , 3);
	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	client_socket=accept(socket_desc,(struct sockaddr *)&client,(socklen_t*)&c);
	if (client_socket<0)
	{
		perror("accept failed");
	return 1;
	}
	puts("Connection accepted");
	
	
	//Reply to the client
	while ((read_size=recv(client_socket,client_message,2000,0))>0)
	{
		int A=0,B=0;

		for (i=0;i<4;i++)
		{
			for (j=0;j<4;j++)
			{
				if (ran_num[i]+48 == client_message[j])
				{
					if (i==j)
					{
						A=A+1;
					}
					else
					{
						B=B+1;
					}
				}
			}
		}

		if (A == 4)
		{
			answer="Correct";
			write(client_socket,answer,strlen(answer));
			break;
		}
		else
		{
			char *reply;
			if (A==0 && B==0)
				reply="0A0B";
			else if(A==0 && B==1)
				reply="0A1B";
			else if(A==0 && B==2)
				reply="0A2B";
			else if(A==0 && B==3)
				reply="0A3B";
			else if(A==0 && B==4)
				reply="0A4B";
			else if(A==1 && B==0)
				reply="1A0B";
			else if(A==1 && B==1)
				reply="1A1B";
			else if(A==1 && B==2)
				reply="1A2B";
			else if(A==1 && B==3)
				reply="1A3B";
			else if(A==2 && B==0)
				reply="2A0B";
			else if(A==2 && B==1)
				reply="2A1B";
			else if(A==2 && B==2)
				reply="2A2B";
			else if(A==3 && B==0)
				reply="3A0B";
			write(client_socket ,reply, strlen(reply));
		}

		if (read_size==0)
		{
			puts("client dissconnected");
			fflush(stdout);
		}
		else if (read_size==-1)
		{
			puts("recv failed");
		}
	}
	return 0;
}

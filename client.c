#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
int main(int argc,char *argv[])
{
int socket_desc,new_socket;
struct sockaddr_in server;
char message[1000],server_reply[2000];

socket_desc = socket(AF_INET,SOCK_STREAM,0);
if (socket_desc==-1)
{
printf("could not create socket");
}
server.sin_addr.s_addr=inet_addr("127.0.0.1");
server.sin_family=AF_INET;
server.sin_port=htons(8888);

if (connect(socket_desc,(struct sockaddr *)&server,sizeof(server))<0)
{
puts ("connect error");
return 1;
}
puts ("connected\n");

while(1)
{
printf("please enter four numbers to play the game : ");
scanf("%s",message);
if (send(socket_desc,message,strlen(message),0)<0)
{
puts("send failed");
return 1;
}
if (recv(socket_desc,server_reply,2000,0)<0)
{
puts("recv failed");
}

puts(server_reply);

if (strlen(server_reply)>4)
break;
}
return 0;
}

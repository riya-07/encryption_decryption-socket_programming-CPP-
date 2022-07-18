/*
Project : Encyrption via Socket Programming
Team members : Varda Desai 19070122191
               Riya 19070122139
               Tanushree Ganorkar 19070122059
               Rohit Raj 19070122141
               Shibani Sahoo 19070122157
               Shaasvata Vishal 19070122151
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8787

//function to get string length
int stlen(char *a)
{
  int c=0;
  for(;a[c]!='\0';c++);
  return c;
}

//function to perform encyrption or decryption Ceaser Cypher Method
void update(char *a,char *b)
{
  if(a[0]=='1')
  {
    for(int i=0; b[i]!='\0';i++)
    {
      if(b[i]!=' ') b[i]+=3;
    }
  }
  else if(a[0]=='2')
  {
    for(int i=0; b[i]!='\0';i++)
    {
      if (b[i]!=' ') b[i]-=3;
    }
  }
  else
  {
     b="Invalid input, sorry for inconvinience but you would have to reconnect with the server";
  }
}


int main()
{
  int server_fd, new_socket, valread;
  struct sockaddr_in address;
  int opt=1;
  int addrlen=sizeof(address);
  char buffer1[1024]={0};
  char *hello="Hello client!\nPlease send me your choice:\n\t1 for encryption\n\t2 for decryption";
  char buffer2[2]={0};
  char *req="Please enter the string you want me to work upon!";
  char buffer3[200]={0};

  //creating socket file descriptor
  if((server_fd=socket(AF_INET,SOCK_STREAM,0))==0)
  {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  //forcefully attaching socket to the PORT
  if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT,&opt, sizeof(opt)))
  {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  address.sin_family=AF_INET;
  address.sin_addr.s_addr=INADDR_ANY;
  address.sin_port=htons(PORT);

  //binding, listening and accepting the first request the socket
  if(bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
  {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }
  if(listen(server_fd,3)<0)
  {
    perror("listen");
    exit(EXIT_FAILURE);
  }
  if((new_socket=accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen))<0)
  {
    perror("accept");
    exit(EXIT_FAILURE);
  }
  valread=read(new_socket,buffer1, 1024);
  printf("%s\n",buffer1);
  send(new_socket, hello, stlen(hello),0);
  printf("Replied to the client\n");
  valread=read(new_socket,buffer2,2);
  printf("This was the clients input: %s\n",buffer2);
  send(new_socket, req, stlen(req),0);
  printf("Requested the client to provide the string\n");
  valread=read(new_socket,buffer3,200);
  printf("This was the clients string: %s\n",buffer3);
  update(buffer2,buffer3);
  send(new_socket,buffer3, stlen(buffer3),200);
  printf("Sent the appropriate response\n");
  return 0;
}

/*
Project : Encyrption via Socket Programming
Team members : Varda Desai 19070122191
               Riya 19070122139
               Tanushree Ganorkar 19070122059
               Rohit Raj 19070122141
               Shibani Sahoo 19070122157
               Shaasvata Vishal 19070122151
*/

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#define PORT 8787

//function to get string length
int stlen(char *a)
{
  int c=0;
  for(;a[c]!='\0';c++);
  return c;
}

int main()
{
  int sock=0, valread;
  struct sockaddr_in serv_addr;
  char *hello="Hello from client";
  char buffer1[1024]={0};
  char buffer2[1024]={0};
  char ch[2],msg[200],buffer3[200];
  char *choice=ch;
  char *str=msg;
  if((sock=socket(AF_INET,SOCK_STREAM,0))<0)
  {
    printf("\nSocket creation error\n");
    return -1;
  }
  serv_addr.sin_family=AF_INET;
  serv_addr.sin_port=htons(PORT);

  if(inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr)<=0)
  {
    printf("\ninvalid address/address not supported\n");
    return -1;
  }
  if(connect(sock,(struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
  {
    printf("\nconnection failed\n");
    return -1;
  }
  send(sock, hello, stlen(hello),0);
  printf("Hello message sent\n");
  valread=read(sock, buffer1, 1024);
  printf("%s\n",buffer1);
  scanf("%s",ch);
  send(sock, choice, stlen(choice),0);
  printf("Choice sent successfully\n");
  fflush(stdin);
  valread=read(sock, buffer2,1024);
  printf("%s\n",buffer2);
  char empty;
  scanf("%c", &empty);
  scanf("%[^\n]%*c",msg);
  send(sock, str, stlen(str),0);
  printf("String sent successfully\n");
  valread=read(sock, buffer3,200);
  printf("The manipulated string given by the server is : %s\n",buffer3);
  return 0;
}

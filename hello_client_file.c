#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>


void error_handling(char* message);


int main(int argc, char* argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	char buf[1024];
	int len;
	int fd= -1;
	int i;
	
	if (argc != 3)
	{
		printf("USage: %s <IP> <port>\n",argv[0]);
		exit(1);
	}
	
	
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1){
		error_handling("socket() error");
	}
	
	//initializing the server's address and port
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]); //argv[1] = ip infomation
	serv_addr.sin_port = htons(atoi(argv[2])); //argv[2] = port infomation
	
	printf("Press enter\n");
	getchar();
	//connecting to server
	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
	{
		error_handling("connect() error");
	}
	
	
	fd = open("received.txt", O_CREAT | O_WRONLY, S_IRWXU);
	if(fd == -1){
		error_handling("error opening file");
		goto ERROR;
	}
	
	printf("Receiving a file from a server \n");
	i=0;
	
	while((len =read(sock,buf,sizeof(buf)))>0)
	{
		printf(" - receiving %d-th chunk\n", i+1);
		i+=1;
			
		if(write(fd, buf, len) !=len){
			error_handling("read() error!");
			goto ERROR;
		}
	}
	printf("Receiving completed\n");
	
ERROR:
	if(fd !=-1){
		close(fd);
	}
	close(sock);
	return 0;
}
	//reading a message from the server
	
	
void error_handling(char* message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1)	;
	}

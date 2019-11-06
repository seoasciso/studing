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
	int serv_sock;		//socket accepting the incoming requests
	int clnt_sock;		//socket which is real communicationg socket
	int cnt_i;
	int fd = -1;
	int n;
	
	struct sockaddr_in serv_addr;	//server IP, port
	struct sockaddr_in clnt_addr;	//client IP, port
	socklen_t clnt_addr_size;
	char buf[1024];
	
	if(argc != 2){
		printf("Usage: %s <port>\n", argv[0]);
		exit(1);
	}
	
	serv_sock =socket(PF_INET, SOCK_STREAM, 0); //domain, type ,protocol 
	if (serv_sock == -1){
		error_handling("socket() error");
	}
	memset(&serv_addr,0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // IP random haldang
	serv_addr.sin_port = htons(atoi(argv[1]));
	
	if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
		error_handling("bind() error");
	}
	
	if(listen(serv_sock,5) == -1){
		error_handling("listen() error");
	}
	
	clnt_addr_size = sizeof(clnt_addr);
	clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
	//clnt socket == communicate socket
	
	if(clnt_sock == -1){
		error_handling("accept() error");
	}
	
	
	fd = open("test2.txt", O_RDONLY, S_IRWXU);
	if(fd == -1){
		printf("open() error\n")
		goto ERROR;
	}
	
	printf("Sending a file to the connected client\n");
	cnt_i =0;
	while((n = read(fd,buf, sizeof(buf)))>0){
		printf("- sending %d-th chunk\n", cnt_i+1);
		cnt_i += 1;
		if(write(clnt_sock,buf, n) != n){
			printf("write() error\n")
			goto ERROR;
		}
	}
	printf("Sending Completed\n");
	
	
ERROR:
	if(fd !=-1){
		close(fd);
	}
	close(clnt_sock);
	close(serv_sock);
	return 0;
}


	
void error_handling(char* message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1)	;
	}

//E0F

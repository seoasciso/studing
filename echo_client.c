#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 128
void error_handling(char *message);

int main(int argc, char *argv[]){
	int sock;
	int str_len;
	struct sockaddr_in serv_adr;	//server IP, port
	
	char message[BUF_SIZE+1] = {0x00,};
		
	if(argc != 3){
		printf("Usage: %s <port>\n", argv[0]);
		exit(1);
	}
	
	sock =socket(PF_INET, SOCK_STREAM, 0); //domain, type ,protocol 
	if (sock == -1){
		error_handling("socket() error");
	}
	memset(&serv_adr,0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr(argv[1]); // IP random haldang
	serv_adr.sin_port = htons(atoi(argv[2]));
	
	
	
	if (connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) ==-1)
		error_handling("connect error!");
	else{
		puts("Connected ..");
	}
	
	while(1){
		printf("Input message(Q or q to quit)\n");
		fgets(message, BUF_SIZE, stdin);
		
		if(!strcmp(message, "q\n")|| !strcmp(message, "Q\n"))
		{
			break;
		}
		write(sock, message, strlen(message));
		str_len = read(sock, message, BUF_SIZE);
		message[str_len] = '\0';
		printf("Message from server: %s\n", message);
	}
	
	close(sock);
	return 0;
}

void error_handling(char* message){
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1)	;
}
//E0F

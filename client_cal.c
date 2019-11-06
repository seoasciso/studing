#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char* message);
void error_handling1(char* message1);
void error_handling2(char* message2);
void error_handling3(char* message3);

int main(int argc, char* argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	char message[64];
	int str_len;
	
	int dataA, dataB;
	
	
	
	if (argc != 3){
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
	
	
	printf("Input two numbers to be added: \n");

	
	
	scanf("%d%d", &dataA, &dataB);
	//network ordering
	
	
	write(sock, &dataA, sizeof(int));
	write(sock, &dataB, sizeof(int));
	
	
	
	
	/*while(1){
		str_len = read(sock, message, sizeof(message));	
		if(str_len == EOF){
			error_handling("read() error!");
		}
		if(str_len>0){
			printf("Message from server: %s \n", message);
		}
		else{
			break;
		}
		str_len = 0;
	}*/
	
	read(sock, &result, sizeof(result));
	result = ntohl(result);
	printf("%d\n", result);
	
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

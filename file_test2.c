#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>

void ErrorHandling(char* message);

void ErrorHandling(char* message){
	fputs(message, stderr); // stdout also okay
	fputc('\n', stderr); //fputc
	exit(1);
}

int main(int argc, char *argv[])
{
	int fd1 =-1, fd2 =-1;
	int n;
	char buf[1024];
	
	if(argc!=3){
		printf("argument error");
		goto ERROR;
	}
	//file descripter for test.txt
	fd1 = open(argv[1], O_RDONLY, S_IRWXU);
	if(fd1 == -1){
	printf("open() error");
	}
	
	//file descriptor for copied.txt
	fd2 = open(argv[2], O_CREAT|O_WRONLY, S_IRWXU);
	if(fd2 == -1){
	printf("open() error");
	}
	
	
	while((n= read(fd1, buf, sizeof(buf))) >0){
		if(write(fd2, buf, n) != n){
			printf("write() error\n");
			goto ERROR;
		}
	} //file copy ==> in 5 line


ERROR:
	if(fd1 !=-1){
		close(fd1);
	}
	if(fd2 !=-1){
		close(fd2);
	}
}

//EOF


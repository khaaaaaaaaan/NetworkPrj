//서버
//데이터 송/수신용 소켓 _sock
//메세지 송/수신용 소켓 _msg_cock

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


#define DATA_SOCK 0
#define MSG_SOCK 1

#define BACKLOG 5
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int serv_sock[2];
	int clnt_sock[2];
	char buf[256];
	struct sockaddr_in serv_addr[2];
	struct sockaddr_in clnt_addr[2];
	socklen_t clnt_addr_size;

	char message[]="Hello World!";
	
	if(argc!=2){
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	
	
	serv_sock[DATA_SOCK]=socket(PF_INET, SOCK_STREAM, 0);
	serv_sock[MSG_SOCK]=socket(PF_INET,SOCK_STREAM,0);
	if(serv_sock[DATA_SOCK] == -1 || serv_sock[MSG_SOCK] == -1){
		error_handling("socket() error");
	}
	//init serv_socks
	for(int i = 0; i < 2; i++){
		
		serv_sock[i]=socket(PF_INET, SOCK_STREAM, 0);
		if(serv_sock[i] == -1 ){
			error_handling("socket() error");
		}
	
		memset(&serv_addr[i], 0, sizeof(serv_addr[i]));
		serv_addr[i].sin_family=AF_INET;
		serv_addr[i].sin_addr.s_addr=htonl(INADDR_ANY);
		serv_addr[i].sin_port=htons(atoi(argv[1])+i);
		

		if(bind(serv_sock[i], (struct sockaddr*) &serv_addr[i], sizeof(serv_addr[i]))==-1 ){
			error_handling("bind() error");
		} 

		if(listen(serv_sock, 5)==-1){
			error_handling("listen() error");
		}
	
		clnt_addr_size=sizeof(clnt_addr);  
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr,&clnt_addr_size);
		if(clnt_sock==-1){
			error_handling("accept() error");
		}  
	}
	 
	
	write(clnt_sock, message, sizeof(message));
	int nbyte = 256;
    	size_t filesize = 0, bufsize = 0;
    	FILE *file = NULL;

    	file = fopen("test.txt", "wb");

    	bufsize = 256;

    	while(nbyte!=0) {
        	nbyte = recv(clnt_sock, buf, bufsize, 0);
        	fwrite(buf, sizeof(char), nbyte, file);		
    	}
	fclose(file);
	close(clnt_sock);	
	close(serv_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

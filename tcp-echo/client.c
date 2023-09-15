#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>


int main(){

	int sockid = socket(AF_INET , SOCK_STREAM , 0) ;
	
	struct sockaddr_in my_addr ;
	
	bzero(&my_addr , sizeof(my_addr));
	
	my_addr.sin_family = AF_INET ;
	my_addr.sin_port = htons(5000) ;
	my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	int status =connect(sockid, (struct sockaddr *) &my_addr , sizeof(my_addr));
	
	if(status ==0 ){
		printf("Connection Success Enter Msg :");
	}else{
	  printf("Connection Failed");
	}
	char sendline[100] ;
	char recvline[100] ;
	
	while(1){
	bzero(sendline,100);
	bzero(recvline,100);
	fgets(sendline ,100, stdin);
	send(sockid , sendline , 100 ,0);
	recv(sockid , recvline , 100 ,0);
	
	printf("FROM SERVER : %s" ,recvline);
	
	}
	
}

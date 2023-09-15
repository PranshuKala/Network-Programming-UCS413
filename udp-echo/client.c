#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#include <sys/socket.h>
#include <unistd.h>

#include <netinet/in.h>

#include <arpa/inet.h>


int main(){
	int sockfd = socket(AF_INET , SOCK_DGRAM , 0) ;
	
	if(sockfd > 0){
		printf("socket created successfully \n");
	}else{
		printf("Socket creation failed");
	}
	
	struct sockaddr_in serveraddr ;
	bzero(&serveraddr , sizeof(serveraddr));
	
	serveraddr.sin_family = AF_INET ;
	serveraddr.sin_port = htons(22000);
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	char buffer[100] ;
	bzero(&buffer , 100);
	while(1){
		printf("Client :");
		fgets(buffer , 100 , stdin);
		sendto(sockfd , buffer ,strlen(buffer),0 ,(struct sockaddr*)&serveraddr , sizeof(serveraddr));
		
		recvfrom(sockfd , buffer , 100 , 0 , NULL , NULL);
		printf("Server : %s", buffer);
		
		
	}
	close(sockfd);
	
}

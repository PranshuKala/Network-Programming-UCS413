#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#include <sys/socket.h>
#include <unistd.h>

#include <netinet/in.h>

#include <arpa/inet.h>

int main(){
	
	int sockfd = socket(AF_INET , SOCK_DGRAM,0);
	
	if(sockfd > 0){
		printf("socket created successfully \n");
	}else{
		printf("Socket creation failed");
	}
	
	struct sockaddr_in serveraddr , cliaddr ;
	
	bzero(&serveraddr , sizeof(serveraddr));
	
	serveraddr.sin_family = AF_INET ;
	serveraddr.sin_port = htons(22000) ;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	int b = bind( sockfd , (struct sockaddr*)&serveraddr , sizeof(serveraddr) );
	
	if(b == -1){
		printf("Binding failed \n ");
	}else{
		printf("Binding success \n");
	}
	char buffer[100];
	bzero(&buffer , 100);
	socklen_t len = sizeof(cliaddr);
	while(1){
	  ssize_t rec = recvfrom(sockfd , buffer ,100 ,0 , (struct sockaddr *)&cliaddr , &len);
	  
	  
	  sendto(sockfd , buffer , sizeof(rec) ,0 ,(struct sockaddr*)&cliaddr , len);
	  close(sockfd);
	}
	
}

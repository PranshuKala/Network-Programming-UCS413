#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>

int main(){

	int sockfd = socket(AF_INET , SOCK_DGRAM , 0);
	
	if (sockfd == -1){
		printf("Socket Creation failed \n");
	}else{
		printf("Socket Created Successfully \n") ;
	
	}
	
	struct sockaddr_in cliaddr ;
	
	cliaddr.sin_family = AF_INET ;
	cliaddr.sin_port = htons(22000);
	cliaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	char sendm[100];
	char recvm[100];
	
	int s = sizeof(cliaddr);
	while(1){
		printf("Client :");
		fgets(sendm , 100 , stdin);
		
		sendto(sockfd , sendm , strlen(sendm), 0 , (struct sockaddr*)&cliaddr , sizeof(cliaddr));
		
		sendm[strcspn(sendm, "\n")]= 0 ;
		
		if(strcmp(sendm ,"exit")==0){
			close(sockfd);
			break ;
		}
		
		recvfrom(sockfd , recvm , sizeof(recvm), 0 , (struct sockaddr*)&cliaddr , &s);
		
		printf("Server : %s", recvm);
		
		bzero(sendm ,100);
		bzero(recvm, 100);	
	}
}

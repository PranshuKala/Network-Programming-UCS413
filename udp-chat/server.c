#include <stdio.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <netinet/in.h>

int main(){
	
	int sockfd = socket(AF_INET , SOCK_DGRAM , 0);
	
	if (sockfd == -1){
		printf("Socket Creation failed \n");
	}else{
		printf("Socket Created Successfully \n") ;
	
	}
	
	struct sockaddr_in servaddr , cli;
	bzero(&servaddr, sizeof(servaddr));
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(22000);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	int b = bind (sockfd , (struct sockaddr*)&servaddr , sizeof(servaddr));
	
	if(b==-1){
		printf("Binding failed \n");
	}else{
		printf("Binding successful \n");
	
	}
	
	char sendm[100] ;
	char recvm[100] ;
	
	int len = sizeof(cli);
	
	while(1){
		recvfrom(sockfd , recvm , sizeof(recvm), 0, 
		(struct sockaddr*)&cli , &len );
		printf("Client : %s", recvm);
		
		recvm[strcspn(recvm,"\n")]= 0 ;
		
		if(strcmp(recvm,"exit")== 0){
			close(sockfd);
			break;
		}
		
		printf("Enter Reply :");
		fgets(sendm ,100 , stdin);
		
		sendto(sockfd , sendm , strlen(sendm), 0 ,       (struct  sockaddr*)&cli , sizeof(cli));
		
		bzero(sendm ,100);
		bzero(recvm, 100);
	
	}
	
	
	
	
}

#include <stdio.h>

#include <string.h>

#include <unistd.h>

#include <sys/socket.h>

#include <sys/types.h>

#include <netinet/in.h>

#include <arpa/inet.h>

int main(){
	int sockfd = socket(AF_INET , SOCK_STREAM ,0 );
	
	if(sockfd > 0){
   	printf("Socket Created Successfully \n");
        } else{
   	printf("Socket creation failed \n") ;
        }
        
        struct sockaddr_in servaddr;
        
        bzero(&servaddr ,sizeof(servaddr));
        
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(22000);
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        
        int c = connect(sockfd ,(struct sockaddr*)&servaddr , sizeof(servaddr));
        
        if(c==-1){
        	printf("Connection failed \n");
        }else{
        	printf("Connection successful \n") ;
        }
        
        char sendm[100] ;
        char recvm[100] ;
        
        while(1){
          printf("Client : ");
          fgets(sendm , sizeof(sendm) , stdin);
          
          
          send(sockfd , sendm , strlen(sendm), 0) ;
          
          sendm[strcspn(sendm, "\n")]= 0 ;
           
          if(strcmp(sendm , "exit") == 0){
             close(sockfd);
             break ;
          }
          
          recv(sockfd , recvm , sizeof(sendm),0) ;
          
          printf("From Server : %s", recvm);
          bzero(sendm,sizeof(sendm)) ;
          bzero(recvm , sizeof(recvm)) ;
        }
        
}

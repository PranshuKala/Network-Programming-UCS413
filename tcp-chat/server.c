#include <stdio.h>

#include <sys/socket.h>

#include <sys/types.h>

#include <arpa/inet.h>

#include <unistd.h>

#include <string.h>

#include <netinet/in.h>

int main(){
   
   int sockid = socket(AF_INET , SOCK_STREAM , 0);
   
   if(sockid > 0){
   	printf("Socket Created Successfully \n");
   }else{
   	printf("Socket creation failed \n") ;
   }
   
   struct sockaddr_in servaddr ;
   
   bzero(&servaddr , sizeof(servaddr));
   
   servaddr.sin_family = AF_INET;
   servaddr.sin_port = htons(22000);
   servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
   
   int b = bind(sockid , (struct sockaddr*)&servaddr , sizeof(servaddr));
   
   if(b==-1){
   	printf("Binding the socket failed ... \n");
   	
   }else{
   	printf("Binding Successfull \n");
   }
   
   int l = listen(sockid ,10) ;
   
   if( l== -1){
   	printf("The Server is not listening \n");
   }else{
        printf("The server is listening ... \n");
   }
   
   int comm_fd = accept(sockid , (struct sockaddr*)NULL , NULL);
   
   if(comm_fd > 0){
	printf("Connection Successful \n");  
   }
   
   char recvm[100] ;
   char sendm[100] ;
   
   while(1){
   	recv(comm_fd , recvm , sizeof(recvm), 0);
   	
   	printf("From Client : %s", recvm);
   	
   	recvm[strcspn(recvm , "\n")] = 0 ;
   	
   	if(strcmp(recvm , "exit")==0){
   		close(sockid);
   		break ;
   	}
   	
   	printf("Enter Reply : ");
   	fgets(sendm , sizeof(sendm) , stdin) ;
   	
   	send(comm_fd , sendm , strlen(sendm),0) ;
   	
   	bzero(sendm , sizeof(sendm)) ;
   	bzero(recvm , sizeof(recvm)) ;
   }
   
  
}



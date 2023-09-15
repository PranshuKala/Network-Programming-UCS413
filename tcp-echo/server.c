#include <stdio.h>

//for bzero
#include <string.h>

//main socket library
#include <sys/socket.h>

//for closing the socket
#include <unistd.h>

//for internet add structures
#include <netinet/in.h>

//for conversion of int to network port int
#include <arpa/inet.h>

int main(){
	
	//creation of initial socket 
	//AF_INET = IPV4 SOCKSTREAM = tcp 0 IS DEFAULT PROTOCOL
	int sockid = socket(AF_INET , SOCK_STREAM  , 0);
	
	//non negative no on successfull creation
	if(sockid < 0){
		printf("Socket creation failed \n");
	}
	
	//creates struc for sockets
	struct sockaddr_in my_addr ;
	
	//clears memory of structure
	bzero(&my_addr , sizeof(my_addr));
	
	//define structure attributes
	
	
	my_addr.sin_family = AF_INET ; //Same as sokcket family
	my_addr.sin_port = htons(5000) ; //specify port no and convert to network order
	
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY) ; //any ip address 
	
	//bind socket , socket id , convert _in(my_addr ) to sockaddr for use
	if(bind(sockid , (struct sockaddr *) &my_addr , sizeof(my_addr)) < 0){
		printf("Error in binding socket");
	}
	
	int status = listen(sockid , 5) ;
	
	if(status==0){
	   printf("The Server is listening ... \n");
	}
	
	char str[100] ;
	int s ;
	while(1){
	s = accept(sockid , (struct sockaddr *) NULL , NULL );
	bzero(str,100);
	recv(s , str ,100 ,0);
	printf("Echoing back -%s",str);
	send(s, str , strlen(str),0);
	close(s) ;
	}
			
}

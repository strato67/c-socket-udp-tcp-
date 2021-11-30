#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>  
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int sock;

    struct sockaddr_in server;
    int servlen = sizeof(server);
    //Creating socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);

//Throw error if creation fails    
    if (sock == -1) 
        printf("Error opening socket"); 
    puts("Socket created");	
//Specify socket address and port
    server.sin_addr.s_addr=inet_addr("127.0.0.1");   
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);



while(1){
    char message[1000], server_reply[2000];
    printf("Enter calculation - Format:(x op y) ");
//Get user input
    fgets (message, 100, stdin);
//Handles socket write error
    if (sendto(sock,message,strlen(message),0,(struct sockaddr*)&server,servlen)< 0){ 
         printf("Error writing to socket");
	return 1;
	} 
//Can't receive server response    
   if (recvfrom(sock,server_reply,2000,0,(struct sockaddr*)&server,&servlen)<0){
	puts("recv failed");
	break;
	}
puts("Result:");

//Server response
puts(server_reply);
}

//Close socket
close(sock);
    return 0;
}

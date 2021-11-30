// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include<arpa/inet.h>
#include <ctype.h>

int main(int argv, char *afgv[]){ 

int socket_desc, c,read_size;
long unsigned int client_socket ;
struct sockaddr_in server, client;
int clilen = sizeof(client);

// get a socket
socket_desc = socket(AF_INET, SOCK_DGRAM,0); 
if (socket_desc==-1){ 
	 printf("Could not create socket.");
}
puts("Socket created");

//fill the fields 
server.sin_addr.s_addr = inet_addr("127.0.0.1");
server.sin_family =AF_INET; 
server.sin_port = htons( 8888 ); 


//bind the socket to the port
if(bind(socket_desc,(struct sockaddr*)&server, sizeof(server))<0){ 
	perror("Bind failed.");
	return 1;
}

//start listening for incoming connections
puts("Bind done");


puts("Waiting for incoming connections...");


while(1){
	
	//Holds client message
	char client_message[1000];
	char *p = client_message;
	
	//Will hold server response
	char server_message[1000];
	
	//Get client's message
	recvfrom(socket_desc, client_message, 2000,0,(struct sockaddr*)&client, &clilen);
	
	
	int store[2]; //Storing two operands
	int count = 0;
	
	//Will store result as string
	int result = 0;
	char result_str[35];


	//Parsing client message for operand value
	while(*p){
		
		//If number is found, operand saved in store array
		if (isdigit(*p)) {
			
   			int val = strtol(p, &p, 10);
			store[count]=val;
          		count++;

        	} else {

            		p++;
		
        	}
	
	}
	
	char *a,*s,*d,*m;

	//Parsing variables to find operation type
	a = strstr(client_message, "add");
	s = strstr(client_message, "sub");
	m = strstr(client_message, "mul");
	d = strstr(client_message, "div");
	
	
	//Handling addition
        if (a != NULL){
		result = store[0]+store[1];
		sprintf(result_str, "%d \n", result);	
		strcpy(server_message,result_str);

        }
	//Handling subtraction
        if (s != NULL){
		result = store[0]-store[1];
                sprintf(result_str, "%d \n", result);
                strcpy(server_message,result_str);
        }
	//Handling multiplication
	if (m != NULL){
		result = store[0]*store[1];
		sprintf(result_str, "%d \n", result);
                strcpy(server_message,result_str);

        }
	//Handling division
	if (d != NULL){
		
		//Divide by zero exception
 		if(store[1]==0){
			strcpy(server_message,"Error 1: Can't divide by 0\n");			
		}else{
			result = store[0]/store[1];
		
			sprintf(result_str, "%d \n", result);
        	        strcpy(server_message,result_str);
	
		}

 	}
	

	//Return result back to client
	sendto(socket_desc, server_message, 2000,0,(struct sockaddr*)&client, clilen);	 
	
}
 


if(read_size==0){ 
  puts("client disconnected");
  fflush(stdout);
}

return 0;
}

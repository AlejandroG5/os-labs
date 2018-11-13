/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct{
	char operand;
	int values[10];
	int size;
}socket_package;

long add(int * values, int size){
    int i;
    long result=0;
    for(i=0;i<size;i++){
    	result+=values[i];
    }
    return result;
}
long subtract(int * values, int size){
    int i;
    long result=values[0];
    for(i=1;i<size;i++){
    	result-=values[i];
    }
    return result;
}
long multiply(int * values, int size){
    int i;
    long result=1;
    for(i=0;i<size;i++){
    	result*=values[i];
    }
    return result;
}



int main()
{
    int server_sockfd, client_sockfd,i;
    int server_len, client_len;
    struct sockaddr_un server_address;
    struct sockaddr_un client_address;
    socket_package server;
    long server_result;
 

/*  Remove any old socket and create an unnamed socket for the server.  */

    unlink("server_socket");
    server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

/*  Name the socket.  */

    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, "server_socket");
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

/*  Create a connection queue and wait for clients.  */

    listen(server_sockfd, 5);
    while(1) {
        printf("SERVER> Waiting...\n");

/*  Accept a connection.  */

        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, 
            (struct sockaddr *)&client_address, &client_len);

/*  We can now read/write to client on client_sockfd.  */

        read(client_sockfd, &server, sizeof(socket_package));
	if(server.operand=='+'){
		server_result=add(server.values,server.size);
	}
	else if(server.operand=='-'){
		server_result=subtract(server.values,server.size);
	}
	else if(server.operand=='x'){
		server_result=multiply(server.values,server.size);
	}
	else{
		server_result=-99999;
	}
	printf("SERVER> Operand: %c\n",server.operand);
	printf("SERVER> Sending Result: %ld\n",server_result);
        write(client_sockfd, &server_result, sizeof(long));
        close(client_sockfd);
    }
}


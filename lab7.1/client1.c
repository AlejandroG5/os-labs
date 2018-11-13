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

int main(int argsize, char *args[])
{
    int sockfd,i;
    int len;
    struct sockaddr_un address;
    int result;
    char ch = 'A';
    socket_package client;
    long server_res;

/*  Create a socket for the client.  */

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

/*  Name the socket, as agreed with the server.  */

    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "server_socket");
    len = sizeof(address);

/*  Now connect our socket to the server's socket.  */

    result = connect(sockfd, (struct sockaddr *)&address, len);

    if(result == -1) {
        perror("oops: client1");
        exit(1);
    }
    client.operand=*args[1];
    client.size=argsize-2;
    for(i=0;i<argsize-2;i++){
	client.values[i]=atoi(args[i+2]);
    }

/*  We can now read/write via sockfd.  */

    write(sockfd, &client, sizeof(socket_package));
    read(sockfd, &server_res, sizeof(long));
    if(server_res==-99999){
	printf("ERROR: Unsupported Operation\n");
    }
    else{
	printf("CLIENT> Result Obtained From Server: %ld\n",server_res);
    }
    close(sockfd);
    exit(0);
}

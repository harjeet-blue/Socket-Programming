#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 4444

void * dosome(void * s){

    int clientSocket, ret;
	struct sockaddr_in serverAddr;
	char buffer[100];

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0) perror("error in socket\n");


	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");


	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0) perror("error in connect\n");


    int k=0;

	while(k++ < 20){

		long long x=k;
		bzero(buffer, 100);

		sprintf(buffer, "%lld", x);

		send(clientSocket, &buffer, sizeof(buffer), 0);

		bzero(buffer, 100);

		if(recv(clientSocket, &buffer, sizeof(buffer), 0) < 0){

			printf("[-]Error in receiving data.\n");

		}else{

			printf("Server: \t%s\n", buffer);
		}
        
	}

    return NULL;

}


int main(){

    pthread_t thrd[10];
    
    for (int i = 0 ; i<10 ; i++){
        pthread_create(&thrd[i], NULL, dosome, NULL); 
    }

    for(int i = 0; i<10 ; i++){

        pthread_join(thrd[i], NULL);
    }

	return 0;
}

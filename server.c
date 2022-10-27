#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#define LOG_FILE_NAME "2a.txt"
FILE *fptr = NULL;

#define PORT 4444


unsigned long long factorial(long long n){

	unsigned long long ans = 1;
	for (int i = 1 ; i <= n ; i++){
		ans *= i;
	}
	return ans;

}


int main()
{	

	int sockfd, newsockfd, portno, n;
	char buffer[100];

	struct sockaddr_in serv_addr, client_addr;
	socklen_t client;


	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if( sockfd < 0)perror("error in opening socket\n");

	bzero((char*)&serv_addr, sizeof(serv_addr));  // clears the buffer

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(PORT);

	if( bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)perror("Error in binding\n");
	
	listen(sockfd, 5);  // 5 no of clients thta can connect to the server at a time

	client = sizeof(client_addr);

    if( fptr == NULL)fptr = fopen( LOG_FILE_NAME, "w");
	int cnt = 0;

	while(1){

		newsockfd = accept(sockfd, (struct sockaddr *) &client_addr, &client);

		if(newsockfd < 0) perror("Erron on accept\n");
		
		char *IP = inet_ntoa(client_addr.sin_addr);
		int PORT_NO = ntohs(client_addr.sin_port);

		printf("[+] Connection accepted from IP : %s  and  PORT : %d\n", IP, PORT_NO);

		fprintf(fptr,"IP : %s \nPORT : %d\n", IP, PORT_NO);

		int requests = 20;

		while (requests-- > 0)
		{	

			bzero(buffer, 100);
			n = recv(newsockfd, &buffer, 100, 0);

			printf("Client sent : %s\n", buffer);

			long num = atoi(buffer);
			unsigned long long fact = factorial(num);
			
			fprintf(fptr, "INTEGER %ld : FACTORIAL : %llu\n", num, fact );
			bzero(buffer, 100);
			sprintf(buffer, "%llu", fact);

			n = send(newsockfd, &buffer, 100, 0);
		}

		close(newsockfd);
		cnt++;

		if(cnt >= 5)break;
		printf("[-] Present client Connection terminated waiting for next connection ...! \n\n");
		
	}
	
	close(sockfd);

	return 0;

}


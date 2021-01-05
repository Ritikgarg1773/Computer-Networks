
//
// Created by Ritik garg on 07-09-2020.
//

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define PORT 9099

int main()
{
    int socketId, client;

    struct sockaddr_in server;
    int addLen = sizeof(server);

    char textTOSend[1024] = {0};
    char textToRec[1024] = {0};

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;  //127.0.0.1

    socketId = socket(AF_INET,SOCK_STREAM,0);

    if(socketId<0)
    {
        perror("Error opening Socket.");
	exit(1);
    }

    if(bind(socketId,(struct sockaddr *)&server, sizeof(server))<0)
    {
	perror("Binding Falied");
	exit(1);
    }

    listen(socketId,0);  // 0-> no. of clients

    printf("Server ready\n");

//    int *socklen_t;
    client = accept(socketId, (
            struct sockaddr *)&server, (socklen_t *)&addLen);
    if(client<0)
    {
	perror("Error on Accept");
	exit(1);
    }

    printf("Client Connected \n");

    //while(1){
    //}
    read(client, textToRec,1024);
    printf("Client : %s\n",textToRec);

    printf("Checking for the file\n");
    //textTOSend[0] = "Seraching";
//  check for the file in the directory and if found send file found
//  send the file to the client
    FILE *f;
    int words = 0;
    char c;

    if( !(f = fopen(textToRec,"r")))
    {
	printf("No File found :( \n");
	char *c1 = "-1";
	//printf("%s",c1);
	send(client, c1,strlen(c1),0);
	exit(EXIT_FAILURE);

//	&textTOSend[0] = "NO";
//	send(client, textTOSend, strlen(textTOSend),0);
    }
    else
    {
	char *c1 = "1";
	send(client,c1,strlen(c1),0);
	//f = fopen(textToRec,"r");
    	while((c = getc(f))!=EOF)
    	{
		fscanf(f, "%s", textTOSend);
		if(isspace(c) || c== '\t')
		    words++;
	}

	write(client, &words, sizeof(int));
	rewind(f);

    	char ch;
   	while(ch != EOF)
  	{
		fscanf(f, "%s", textTOSend);
	        write(client, textTOSend,1024);
		ch = fgetc(f);
        }
   	printf("File sent successfully!\n");
    }
    close(socketId);

}

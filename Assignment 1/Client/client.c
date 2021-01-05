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
#include <errno.h>
#include <ctype.h>

#define PORT 9099

int main()
{
    int sock =0;  // file descriptor
    struct sockaddr_in server;
    char textToSend[1024];
    char textToRec[1024];

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock <0)
    {
        perror("Error in opening socke");
	exit(1);
    }
	// here the socket is craeeted

    connect(sock, (struct sockaddr * )&server, sizeof(server));

    printf("You are now connected to the server\n");

    printf("Enter the file name you want: \n");
    scanf("%s", textToSend);
    char *filename = textToSend;
    FILE *receivedFile;
    int words;


    send(sock, textToSend, strlen(textToSend),0);

    printf("Checking for the file: ");
    printf("%s\n",filename);

    read(sock,textToRec,1024);
//    read(sock,&words,sizeof(int));
    //printf("%s\n", textToRec);

    char *a = textToRec;

//    char *z = "-1";
//    printf("%s %s\n",a,z);

    if(a[0] == '-')
    {
	fprintf(stderr, "File not Found\n");
	exit(EXIT_FAILURE);
    }
    else
    {
	receivedFile = fopen(filename, "w");
	read(sock,&words,sizeof(int));
	int ch = 0;
	while(ch!=words)
	{
		read(sock, textToRec, 1024);
		fprintf(receivedFile, "%s ", textToRec);
		ch++;
	}
	printf("File received successfully\n");
        fclose(receivedFile);
    }
    printf("Now closing \n");
    close(sock);


}

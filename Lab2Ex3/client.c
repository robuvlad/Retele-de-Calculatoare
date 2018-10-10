#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#define NR 1024

int main()
{
        int c;
        struct sockaddr_in server;

        c=socket(AF_INET, SOCK_STREAM, 0);
        if (c<0){
                printf("Eroare la creare socketului client\n");
                return 1;
        }

        memset(&server, 0, sizeof(server));
        server.sin_port = htons(1234);
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr("127.0.0.1");

        if (connect(c, (struct sockaddr *) &server, sizeof(server))<0){
                printf("Eroare la connect\n");
                return 1;
        }

        char *string = (char*)malloc(sizeof(char)*NR);
        char *newString = (char*)malloc(sizeof(char)*NR);
        printf("Scrie ceva: ");
        fgets(string, 100, stdin);
        send(c, string, sizeof(char)*NR, 0);

        recv(c, newString, sizeof(char)*NR, 0);
        printf("Stringul cautat: %s\n", newString);


        close(c);

        return 0;
}

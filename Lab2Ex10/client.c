#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#define NR 1024

int main()
{
        int c;
        struct sockaddr_in server;

        c = socket(AF_INET, SOCK_STREAM, 0);
        if (c < 0){
                printf("Eroare la crearea socketului client\n");
                return 1;
        }

        memset(&server, 0, sizeof(server));
        server.sin_port = htons(1234);
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr("127.0.0.1");

        if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0){
                printf("Eroare la conectare la server\n");
                return 1;
        }

        char *string1 = (char*)malloc(sizeof(char)*NR);
        char *string2 = (char*)malloc(sizeof(char)*NR);

        printf("Primul string: ");
        fgets(string1, 100, stdin);
        printf("Al doilea string: ");
        fgets(string2, 100, stdin);

        send(c, string1, sizeof(char)*NR, 0);
        send(c, string2, sizeof(char)*NR, 0);

        int foundNr;
        char character;

        recv(c, &foundNr, sizeof(int), 0);
        recv(c, &character, sizeof(char), 0);

	printf("Caracter: %c\n", character);
        printf("Nr. aparitii: %d\n", foundNr);

        close(c);

        return 0;
}

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <stdlib.h>

#define NR 1024

int main()
{
        int c;
        struct sockaddr_in server;

        c = socket(AF_INET, SOCK_STREAM, 0);
        if (c<0){
                printf("Eroare la crearea socketului client\n");
                return 1;
        }

        memset(&server, 0, sizeof(server));
        server.sin_port = htons(1234);
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr("127.0.0.1");

        if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0){
                printf("Eroare la conectarea la server\n");
                return 1;
        }

        char *string = (char*)malloc(sizeof(char)*NR);
        int number=-1;

        printf("Scrie ceva: ");
        fgets(string, 100, stdin);

        printf("%s", string);

        send(c, string, sizeof(char)*NR, 0);

        recv(c, &number, sizeof(number), 0);
        printf("Numarul de spatii: %d\n", number);

        close(c);

        return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>

int main()
{
        int c;
        struct sockaddr_in server;

        c=socket(AF_INET, SOCK_STREAM, 0);
        if (c<0){
                printf("Eroare la crearea socketului client\n");
                return 1;
        }

        memset(&server, 0, sizeof(server));
        server.sin_port = htons(1234);
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr("127.0.0.1");

        if (connect(c, (struct sockaddr *) &server, sizeof(server))<0){
                printf("Eroare la conectare\n");
                return 1;
        }

        uint16_t number;
        printf("Introduceti un numar: ");
        scanf("%hu", &number);
        number = htons(number);
        send(c, &number, sizeof(int), 0);

        int v[1024], index;

        recv(c, &index, sizeof(int), 0);
        index=ntohs(index);
        recv(c, &v, sizeof(int)*index, 0);

        for(int i=1;i<index;i++)
                printf("Numar: %d\n", v[i]);

        close(c);

        return 0;
}

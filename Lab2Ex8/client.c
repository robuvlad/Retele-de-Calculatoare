#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#define NR 1024

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
                printf("Eroare la conectarea la server\n");
                return 1;
        }

        int v1[NR], v2[NR], v3[NR];
        int number=-1, i=1, j=1, nrElem;

        printf("Primul sir. ");
        while(number){
                printf("Numar: ");
                scanf("%d", &number);
                if (number == 0)
                        break;
                v1[i++]=number;
        }

        printf("Al doilea sir. ");
        number=-1;
        while(number){
                printf("Numar: ");
 		scanf("%d", &number);
                if (number == 0)
                        break;
                v2[j++]=number;
        }

        i-=1; j-=1;

        send(c, &i, sizeof(int), 0);
        send(c, &v1, sizeof(int)*i, 0);
        send(c, &j, sizeof(int), 0);
        send(c, &v2, sizeof(int)*j, 0);

        recv(c, &nrElem, sizeof(int), 0);
        recv(c, &v3, sizeof(int)*nrElem, 0);
        for(int z=1; z<=nrElem; z++){
                if (v3[z] == 0)
                        break;
                printf("%d\n", v3[z]);
        }

        close(c);

        return 0;
}

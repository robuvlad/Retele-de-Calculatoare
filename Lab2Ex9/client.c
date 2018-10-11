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

        int vector1[NR], vector2[NR], finalVector[NR];
        int nrElem1=0, nrElem2=0, nrElemFinal;
        int number1=-1, number2=-1;

        printf("Primul sir\n");
        while(number1){
                printf("Numar: ");
                scanf("%d", &number1);
                if (number1 == 0)
                        break;
                vector1[++nrElem1] = number1;
        }

        printf("Al doilea sir\n");
        while(number2){
                printf("Numar: ");
                scanf("%d", &number2);
 		if (number2 == 0)
                        break;
                vector2[++nrElem2] = number2;
        }

        send(c, &nrElem1, sizeof(int), 0);
        send(c, &vector1, sizeof(int)*NR, 0);
        send(c, &nrElem2, sizeof(int), 0);
        send(c, &vector2, sizeof(int)*NR, 0);

        recv(c, &nrElemFinal, sizeof(int), 0);
        recv(c, &finalVector, sizeof(int)*NR, 0);
        for(int i=1; i<=nrElemFinal; i++){
                printf("%d\n", finalVector[i]);
        }

        close(c);

        return 0;
}

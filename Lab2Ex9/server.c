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
        int s;
        struct sockaddr_in server, client;
        int c, l;

        s = socket(AF_INET, SOCK_STREAM, 0);
        if (s < 0){
                printf("Eroare la crearea socketului server\n");
                return 1;
        }

        memset(&server, 0, sizeof(server));
        server.sin_port = htons(1234);
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;

        if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0){
                printf("Eroare la bind\n");
                return 1;
        }

        listen(s, 5);
        l = sizeof(client);
        memset(&client, 0, sizeof(client));

        while(1){
                c = accept(s, (struct sockaddr *) &client, &l);
                printf("S-a conectat un client\n");

                int vector1[NR], vector2[NR], finalVector[NR];
                int nrElem1, nrElem2, nrElem3=0;

                recv(c, &nrElem1, sizeof(int), MSG_WAITALL);
                recv(c, &vector1, sizeof(int)*NR, MSG_WAITALL);
                recv(c, &nrElem2, sizeof(int), MSG_WAITALL);
                recv(c, &vector2, sizeof(int)*NR, MSG_WAITALL);
 		
		int isIn=1;
                for(int i=1; i<=nrElem1; i++){
                        for(int j=1; j<=nrElem2; j++){
                                if (vector1[i] == vector2[j]){
                                        isIn=0;
                                }
                        }
                        if(isIn == 1){
                                finalVector[++nrElem3] = vector1[i];
                        }
                        isIn=1;
                }

                send(c, &nrElem3, sizeof(int), 0);
                send(c, &finalVector, sizeof(int)*NR, 0);

                close(c);
        }

        return 0;
}

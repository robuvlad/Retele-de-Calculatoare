#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>

#define NR 1024

int main()
{
        int s;
        struct sockaddr_in server, client;
        int c,l;

        s=socket(AF_INET, SOCK_STREAM, 0);
        if (s<0){
                printf("Eroare la crearea socketului server\n");
                return 1;
        }

        memset(&server, 0, sizeof(server));
        server.sin_port = htons(1234);
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;

        if (bind(s, (struct sockaddr *) &server, sizeof(server))<0){
                printf("Eroare la bind\n");
                return 1;
        }

        listen(s,5);
        l=sizeof(client);
        memset(&client, 0, sizeof(client));

        while(1){
                int v1[NR], v2[NR], i, j, v3[NR];

                c = accept(s, (struct sockaddr *) &client, &l);
                printf("S-a conectat un client\n");

                recv(c, &i, sizeof(int), MSG_WAITALL);
                recv(c, &v1, sizeof(int)*i, MSG_WAITALL);
                recv(c, &j, sizeof(int), MSG_WAITALL);
                recv(c, &v2, sizeof(int)*j, MSG_WAITALL);

                int index3=1;
		for(int index1=1; index1 <= i; index1++){
                        for(int index2=1; index2 <= j; index2++){
                                if (v1[index1] == v2[index2])
                                        v3[index3++]=v1[index1];
                        }
                }

                index3-=1;
                send(c, &index3, sizeof(int), 0);
                send(c, &v3, sizeof(int)*index3, 0);

                close(c);
        }

        return 0;
}

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
                char *string = (char*)malloc(sizeof(char)*NR);
                char *newString = (char*)malloc(sizeof(char)*NR);
                int i,lung;
                int j=0, index;

                c=accept(s, (struct sockaddr *) &client, &l);

                printf("S-a conectat un client\n");

                recv(c, string, sizeof(char)*NR, MSG_WAITALL);
                recv(c, &i, sizeof(int), MSG_WAITALL);
 		recv(c, &lung, sizeof(int), MSG_WAITALL);
                i = ntohs(i);
                lung = ntohs(lung);

                index=i;
                while(index != lung+i){
                        newString[j++] = string[index++];
                }

                send(c, newString, sizeof(char)*NR, 0);

                close(c);
        }

        return 0;
}

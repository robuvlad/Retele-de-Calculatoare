#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
                char *string = (char*)malloc(sizeof(char)*NR);
                char *carac = (char*)malloc(sizeof(char));
                int vec[NR], index=1;

                c=accept(s, (struct sockaddr *) &client, &l);

                recv(c, string, sizeof(char)*NR, MSG_WAITALL);
                recv(c, carac, sizeof(char), MSG_WAITALL);

                for(int i=0; i<strlen(string); i++){
                        if (string[i] == *carac)
                                vec[index++]=i;
		send(c, &index, sizeof(int), 0);
                send(c, &vec, sizeof(int)*index, 0);

                close(c);
        }

        return 0;
}

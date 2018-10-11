#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

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
                int v[1024], index=1;
                uint16_t number;
                c=accept(s, (struct sockaddr *) &client, &l);

                recv(c, &number, sizeof(int), MSG_WAITALL);
                number = ntohs(number);


                for(int d=1; d<= number; d++){
                        if (number%d==0)
                                v[index++]=d;
                }
                index = htons(index);
                send(c, &index, sizeof(int), 0);
		send(c, &v, sizeof(int)*index, 0);
                close(c);
        }

        return 0;
}

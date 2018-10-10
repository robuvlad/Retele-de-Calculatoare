#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdlib.h>

#define NR 1024

int main()
{
        int s;
        struct sockaddr_in server, client;
        int c, l;

        s = socket(AF_INET, SOCK_STREAM, 0);
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

        listen(s,25);

        l = sizeof(client);
        memset(&client, 0, sizeof(client));

        while(1){
                char *string = (char*)malloc(sizeof(char)*NR);
                int number=0;
                c = accept(s, (struct sockaddr *) &client, &l);
                printf("S-a conectat un client\n");

                recv(c, string, sizeof(char)*NR, MSG_WAITALL);

                printf("%s", string);
                char *p = string;
                while(*p != '\0'){
			if (*p == ' ')
                                number+=1;
                        p+=1;
                }

                send(c, &number, sizeof(number), 0);

                close(c);
        }
        return 0;
}


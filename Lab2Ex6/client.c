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

        char *string = (char*)malloc(sizeof(char)*NR);
        char *carac = (char*)malloc(sizeof(char));
        int vec[NR], nrElem;

        printf("Introduceti sir de caractere: ");
        fgets(string, 100, stdin);
        printf("Introduceti caracter: ");
        fgets(carac, 100, stdin);

        send(c, string, sizeof(char)*NR, 0);
        send(c, carac, sizeof(char), 0);

        recv(c, &nrElem, sizeof(int), 0);
        recv(c, &vec, sizeof(int)*nrElem, 0);
        for(int i=1; i<nrElem; i++){
                printf("Pozitie: %d\n", vec[i]);
        }
	 close(c);

        return 0;
}

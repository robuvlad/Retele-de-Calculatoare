#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/types.h>
#include <sys/socket.h>

#define NR 1024

int main()
{
        int s;
        struct sockaddr_in server, client;
        int c,l;

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

        listen(s,5);
        l = sizeof(client);
        memset(&client, 0, sizeof(client));

        while(1){
                c = accept(s, (struct sockaddr *) &client, &l);
                printf("S-a conectat un client\n");

                char *string1 = (char*)malloc(sizeof(char)*NR);
                char *string2 = (char*)malloc(sizeof(char)*NR);
                int i=0, index=0, vec[NR], carac[NR];

                recv(c, string1, sizeof(char)*NR, MSG_WAITALL);
                recv(c, string2, sizeof(char)*NR, MSG_WAITALL);

                for(int i=0; i<NR; i++){
 			vec[i] = 0;
                        carac[i] = "";
                }

                int ok=0;
                while(i != strlen(string1) && i != strlen(string2)){
                        if (string1[i] == string2[i]){
                                for(int z=0; z<NR; z++){
                                        if (carac[z] == string1[i]){
                                                vec[z]+=1;
                                                ok = 1;
                                                break;
                                        }
                                }
                                if (ok == 0){
                                        carac[index] = string1[i];
                                        vec[index] += 1;
                                        index+=1;
                                }
                                ok=0;
                        }
                        i+=1;
                }

                int max=0;
                char caracter;
                for(int z=0; z<NR; z++){
                        if (vec[z] > max){
                                max = vec[z];
                                caracter = carac[z];
                        }
                }

                send(c, &max, sizeof(int), 0);
                send(c, &caracter, sizeof(char), 0);

                close(c);
        }

        return 0;
}

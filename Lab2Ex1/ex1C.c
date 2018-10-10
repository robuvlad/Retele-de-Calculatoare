#include string.h
#include stdio.h
#include syssocket.h
#include systypes.h
#include netinetin.h
#include netinetip.h

int main(){
        int c;
        struct sockaddr_in server;
        uint16_t suma;

        c = socket(AF_INET, SOCK_STREAM, 0);
        if (c0){
                printf(Eroare la crearea socketului clientn);
                return 1;
        }

        memset(&server, 0, sizeof(server));
        server.sin_port = htons(1234);
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr(127.0.0.1);

        if (connect(c, (struct sockaddr ) &server, sizeof(server)) 0 ){
                printf(Eroare la conectarea la servern);
                return 1;
        }

        uint16_t number=-1;
        while(number){
                printf(nIntroduceti numar );
                scanf(%hu, &number);
                number = htons(number);
                send(c, &number, sizeof(number), 0);
        }

        recv(c, &suma, sizeof(suma), 0);
        suma = ntohs(suma);
        printf(Suma este %hu n, suma);

        close(c);
}

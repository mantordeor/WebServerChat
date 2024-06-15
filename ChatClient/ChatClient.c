#undef UNICODE
#define WIN32_LEAN_AND_MEAN
#pragma warning(disable:4996) 
#pragma comment (lib, "Ws2_32.lib")
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
SOCKET Csocket;
int num = 0;

/*
    add thread
        thread1 : accept user and send server
        thread2 : accept server and show UI

*/



int n1, n2;

char c[9] = { ' ',' ',' ',' ',' ',' ',' ',' ',' ' };

void recvServerAndShow();

void print() {
    printf("[game]\n[begin in 1~9]\n+==================+\n   | %c | % c | %c | \n   | - | - | - | \n   | %c | % c | %c | \n   | - | - | - | \n   | %c | % c | %c | \n+==================+\n",c[0],c[1],c[2],c[3],c[4],c[5],c[6],c[7],c[8]);
}

int judge() {
    if (c[0] == c[1] && c[1] == c[2] && c[2] != ' ') {
        if (c[0] == 'o') n1 = 1;
        else n2 = 1;
        return;
    }
    if (c[3] == c[4] && c[4] == c[5] && c[5] != ' ') {
        if (c[3] == 'o') n1 = 1;
        else n2 = 1;
        return;
    }
    if (c[6] == c[7] && c[7] == c[8] && c[8] != ' ') {
        if (c[6] == 'o') n1 = 1;
        else n2 = 1;
        return;
    }
    if (c[0] == c[3] && c[3] == c[6] && c[6] != ' ') {
        if (c[0] == 'o') n1 = 1;
        else n2 = 1;
        return;
    }
    if (c[1] == c[4] && c[4] == c[7] && c[7] != ' ') {
        if (c[1] == 'o') n1 = 1;
        else n2 = 1;
        return;
    }
    if (c[2] == c[5] && c[5] == c[8] && c[8] != ' ') {
        if (c[2] == 'o') n1 = 1;
        else n2 = 1;
        return;
    }
    if (c[0] == c[4] && c[4] == c[8] && c[8] != ' ') {
        if (c[0] == 'o') n1 = 1;
        else n2 = 1;
        return;
    }
    if (c[2] == c[4] && c[4] == c[6] && c[6] != ' ') {
        if (c[2] == 'o') n1 = 1;
        else n2 = 1;
        return;
    }
}

void game() {
    while (1) {
        n1 = 0, n2 = 0;
        system("cls");
        print();
        int i = 9;
        char sat;
        while (i--) {
            if (i % 2 == 1) {
                printf("Player 2 begin:\n");
                getchar();
                char n;
                (void)scanf("%c", &n);
                if (c[(n - '0') - 1] != ' ' || c[(n - '0') - 1] == 'O' || c[(n - '0') - 1] == 'X' || isalpha(n)) {
                    printf("Wrong!\n");
                    i++;
                    continue;
                }
                else c[(n - '0') - 1] = 'X';
            }
            else {
                printf("Player 1 begin:\n");
                getchar();
                char n;
                (void)scanf("%c", &n);
                if (c[(n - '0') - 1] != ' ' || c[(n - '0') - 1] == 'O' || c[(n - '0') - 1] == 'X' || isalpha(n)) {
                    printf("Wrong!\n");
                    i++;
                    continue;
                }
                c[(n - '0') - 1] = 'O';
            }
            system("cls");
            print();
            judge();
            if (n1 == 1 || n2 == 1) break;
        }
        printf("##Game Over##\n-------------\n");
        if (n1 == 0 && n2 == 0) printf(" | DRAW. | \n") ;
        else if (n1 == 1) printf(" | Player 1 win! | \n");
        else if (n2 == 1) printf(" | Player 2 win! | \n");
        puts("");
        printf("-----------input<1> NewGame------------\n");
        printf("-----------input<2> Back ------------\n");
        puts("");
        pot:
        getchar();
        scanf("%c",&sat);
        if (sat == '1') {
            for (int i = 0; i < 9; i++) {
                c[i] = ' ';
            }
            continue;
        }
        else if(sat == '2') {
            for (int i = 0; i < 9; i++) {
                c[i] = ' ';
            }
            system("cls");
            break;
        }
        else {
            printf("?\n");
            printf("-----------input<1> NewGame------------\n");
            printf("-----------input<2> Back ------------\n");
            goto pot;
        }
    }
    return;
}
int input(char s[]) {
    int idx = 0;
    char c;
    while (scanf("%c", &c) != EOF) {
        if (c == '\n') break;
        s[idx++] = c;
    }
    idx--;
    return idx;
}
int main()
{
    // Initialize Winsock
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        printf("Initialize Winsock Failed: %u\n", GetLastError());
        return -1;
    }
    else printf("Initialize Winsock Success!\n");

    // Create a SOCKET for the server to listen for client connections.
    Csocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (-1 == Csocket) {
        printf("Initialize Winsock Failed: %u\n", GetLastError());
        WSACleanup();
        return -1;
    }
    else printf("Creat socket success!\n");

    // Getaddr
    SOCKADDR_IN sAddr = { 0 };
    sAddr.sin_family = AF_INET;
    sAddr.sin_addr.S_un.S_addr = inet_addr("120.110.114.232");
    sAddr.sin_port = htons(51419);

    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)recvServerAndShow,NULL,NULL,NULL);


    //connecting server
    int r = connect(Csocket, (struct sockaddr*)&sAddr, sizeof(sAddr));
    if (-1 == r) {
        printf("Connecting Server Failed: %u\n", GetLastError());
        WSACleanup();
        return -1;
    }
    else printf("Connecting Server success!\n");

    char buff[1024];
    while (1) {
        memset(buff, 0, 1024);
        printf("Please say >> ");
        input(buff);
        if (buff[0] == 'G' && buff[1] == 'A' && buff[2] == 'M' && buff[3] == 'E') {
            game();
        }
        else {
            send(Csocket, buff, strlen(buff), NULL);
        }
    }

    // cleanup
    closesocket(Csocket);
    WSACleanup();
    return 0;
}

void recvServerAndShow() {
    while (1) {
        char buff[1024];
        int r;
        while (1) {
            r = recv(Csocket, buff, 1023, NULL);
            if (r > 0) {
                printf("%s\n",buff);
                num++;
            }
        }
    }
}
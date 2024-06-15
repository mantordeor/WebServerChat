#undef UNICODE
#define WIN32_LEAN_AND_MEAN
#pragma warning(disable:4996) 
#pragma comment (lib, "Ws2_32.lib")
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

SOCKET Csocket[1024];//1024client
int count = 0;//client->number

void communicate(int idx);


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
    SOCKET Ssocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (-1 == Ssocket) {
        printf("Initialize Winsock Failed: %u\n", GetLastError());
        WSACleanup();
        return -1;
    }
    else printf("Creat socket success!\n");

    // SETADDR
    SOCKADDR_IN sAddr = { 0 };
    sAddr.sin_family = AF_INET;
    sAddr.sin_addr.S_un.S_addr = inet_addr("120.110.114.232");
    sAddr.sin_port = htons(51419);

    //BIND
    int r = bind(Ssocket, (struct sockaddr*)&sAddr, sizeof(sAddr));
    if (-1 == r) {
        printf("Bind Failed: %u\n", GetLastError());
        WSACleanup();
        return -1;
    }
    else printf("Bind success!\n");

    //Listen
    r = listen(Ssocket, 10);
    if (-1 == r) {
        printf("Listen Failed: %u\n", GetLastError());
        WSACleanup();
        return -1;
    }
    else printf("Listen success!\n");
    //accept connect
    SOCKADDR_IN cAddr = { 0 };
    int cAddrlen = sizeof(cAddr);
    for (int i = 0; i < 1024; i++) {
        Csocket[i] = accept(Ssocket, (struct sockaddr*)&cAddr, &cAddrlen);
        if (-1 == Csocket[i]) {
            printf("Creat Csocket Failed: %u\n", GetLastError());
            WSACleanup();
            return -1;
        }
        else printf("Csocket success!%s\n", inet_ntoa(cAddr.sin_addr));

        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)communicate, (LPVOID)i, 0, 0);
    }
    
    
    
    
    // cleanup
    closesocket(Ssocket);
    WSACleanup();
    return 0;
}
//connecting
void communicate(int idx) {
    int r;
    while (1) {
        char buff[1024];
        r = recv(Csocket[idx], buff, 1024, 0);
        if (r > 0) {
            buff[r] = 0;
            printf("%d >> %s\n", idx , buff);
            //broadcast
            for (int i = 0; i < count; i++) {
                send(Csocket[i], buff, r , 0);
            }
        }
    }
}
#undef UNICODE
#define WIN32_LEAN_AND_MEAN
#pragma warning(disable:4996) 
#pragma comment (lib, "Ws2_32.lib")
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>


int main()
{
    // Initialize Winsock
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2),&wsaData);
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        printf("Initialize Winsock Failed: %u\n", GetLastError());
        return -1;
    }
    else printf("Initialize Winsock Success!\n");

    // Create a SOCKET for the server to listen for client connections.
    SOCKET Csocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (-1 == Csocket) {
        printf("Initialize Winsock Failed: %u\n", GetLastError());
        WSACleanup();
        return -1;
    }else printf("Creat socket success!\n");

    // Getaddr
    SOCKADDR_IN sAddr = { 0 };
    sAddr.sin_family = AF_INET;
    char dist_addr[16];
    printf("Input your distination address: ");
    scanf("%s", dist_addr);
    sAddr.sin_addr.S_un.S_addr = inet_addr(dist_addr);
    sAddr.sin_port = htons(8080);
    
    //connecting server
    int r = connect(Csocket,(sockaddr*)&sAddr,sizeof(sAddr));
    if (-1 == r) {
        printf("Connecting Server Failed: %u\n", GetLastError());
        WSACleanup();
        return -1;
    }else printf("Connecting Server success!\n");
    
    char buff[1024];
    while (1) {
        memset(buff, 0, 1024);
        printf("Please say >> ");
        scanf("%s", buff);
        send(Csocket, buff, strlen(buff),NULL);
    }

    // cleanup
    closesocket(Csocket);
    WSACleanup();
    return 0;
}
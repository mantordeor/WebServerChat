#undef UNICODE
#define WIN32_LEAN_AND_MEAN
#pragma warning(disable:4996) 
#pragma comment (lib, "Ws2_32.lib")
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>


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
    sAddr.sin_addr.S_un.S_addr = inet_addr("192.168.0.4");
    sAddr.sin_port = htons(8080);

    //BIND
    int r = bind(Ssocket, (sockaddr*)&sAddr, sizeof(sAddr));
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
    SOCKET Csocket = accept(Ssocket, (sockaddr*)&cAddr, &cAddrlen);
    if (-1 == Csocket) {
        printf("Creat Csocket Failed: %u\n", GetLastError());
        WSACleanup();
        return -1;
    }
    else printf("Csocket success!%s\n", inet_ntoa(cAddr.sin_addr));
    //connecting
    char buff[1024];
    while (1) {
        r = recv(Csocket, buff, 1024, NULL);
        if (r > 0) {
            buff[r] = 0;
            printf(">> %s\n", buff);
        }
    }
    // cleanup
    closesocket(Ssocket);
    WSACleanup();
    return 0;
}
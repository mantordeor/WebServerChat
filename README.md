查看本地端port看占用情況。
```
netstat -ano 
```

server端基本流程
```
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
```
client端接收資訊
```
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
```

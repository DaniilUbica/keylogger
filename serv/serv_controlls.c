#include "serv_controlls.h"

WSADATA wsa_data;
WORD dll_version = MAKEWORD(2, 1);

SOCKADDR_IN addr;
int sizeofaddr = sizeof(addr);

SOCKET connections[MAX_CONNECTIONS];
size_t connections_count = 0;

void set_server_options() {
    if (WSAStartup(dll_version, &wsa_data) != 0) {
        printf("Error, can`t start wsa");
        exit(1);
    }

	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;
}

void client_hadler(size_t index) {
    char msg[512];

    while(1) {
        recv(connections[index], msg, sizeof(msg), NULL);
        printf("%s", msg);
    }
}

void server_listen() {
    SOCKET s_listen = socket(AF_INET, SOCK_STREAM, NULL);

	bind(s_listen, (SOCKADDR*)&addr, sizeof(addr));
	listen(s_listen, SOMAXCONN);

	SOCKET new_connection;
    for (int i = 0; i < MAX_CONNECTIONS; i++) {
        new_connection = accept(s_listen, (SOCKADDR*)&addr, &sizeofaddr);

        if(new_connection == 0) {
            printf("Error #2\n");
        } 
        else {
            connections[i] = new_connection;
            connections_count++;

            CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)client_hadler, (LPVOID)(i), NULL, NULL);
        }
    }
}
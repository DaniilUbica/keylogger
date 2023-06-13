#include <locale.h>

#include "serv_controlls.h"

int main() {
	setlocale(LC_ALL, "Rus");

	set_server_options();

    server_listen();

	system("pause");
	return 0;
}
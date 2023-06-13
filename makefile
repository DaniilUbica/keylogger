CC = gcc
CCFLAGS = -Wall -Wextra
OBJS = main.o functions.o
SRC = main.c ./src/functions.c
SERV_SRC = ./serv/server.c ./serv/serv_controlls.c
LIBS = -lwsock32

all: keylogger server

keylogger: ${SRC}
	$(CC) ${CCFLAGS} -o keylogger ${SRC} ${LIBS}

server: ${SERV_SRC}
	$(CC) ${CCFLAGS} -o server ${SERV_SRC} ${LIBS}

clean: 
	rm *.o main
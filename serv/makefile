CC = gcc
CCFLAGS = -Wall -Wextra
OBJS = main.o functions.o
SRC = server.c serv_controlls.c
LIBS = -lwsock32

# all: ${OBJS}
# 	$(CC) $(CCFLAGS) -o main ${OBJS}

all: ${SRC}
	$(CC) ${CCFLAGS} -o server ${SRC} ${LIBS}

clean: 
	rm *.o main
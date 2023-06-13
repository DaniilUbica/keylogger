CC = gcc
CCFLAGS = -Wall -Wextra
OBJS = main.o functions.o
SRC = main.c ./src/functions.c
LIBS = -lwsock32

# all: ${OBJS}
# 	$(CC) $(CCFLAGS) -o main ${OBJS}

all: ${SRC}
	$(CC) ${CCFLAGS} -o keylogger ${SRC} ${LIBS}

clean: 
	rm *.o main
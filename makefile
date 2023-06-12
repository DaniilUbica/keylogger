CC = gcc
CCFLAGS = -Wall -Wextra -Werror
OBJS = main.o functions.o
SRC = main.c ./src/functions.c

# all: ${OBJS}
# 	$(CC) $(CCFLAGS) -o main ${OBJS}

all: ${SRC}
	$(CC) ${CCFLAGS} -o main ${SRC}

clean: 
	rm *.o main
CC = gcc
CCFLAGS = -Wall -Wextra -Werror
OBJS = main.o
all: ${OBJS}
		$(CC) $(CCFLAGS) -o main ${OBJS}

clean: rm *.o main
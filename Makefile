CC = clang
CFLAGS = -g -Wall
RM = rm -f

main: main.c
	$(CC) $(CFLAGS) -o main main.c

clean:
	$(RM) main
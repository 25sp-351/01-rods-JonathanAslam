CC = clang
CFLAGS = -g -Wall
RM = rm -f

main: main.c rod.c
	$(CC) $(CFLAGS) -o main main.c rod.c

clean:
	$(RM) main
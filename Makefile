CFLAGS = -g
main: main.c
	gcc -o main $(CFLAGS) main.c -lm


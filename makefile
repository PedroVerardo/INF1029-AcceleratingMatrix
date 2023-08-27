all:
	gcc -Wall main.c headerFiles/matrix_lib.c -o main
	./main
	
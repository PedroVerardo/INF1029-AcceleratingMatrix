all:
	clear
	gcc -Wall main2.c headerFiles/matrix_lib.c headerFiles/file_reader.c -o main
	./main
	
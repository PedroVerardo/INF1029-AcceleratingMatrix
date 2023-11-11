all:
	clear
	gcc -mfma -mavx -Wall matrix_lib_test.c headerFiles/matrix_lib.c headerFiles/file_reader.c headerFiles/time.c -o main
	./main 5.0 1024 1024 1024 1024 16 src/A_1024.dat src/B_1024.dat src/result1.dat src/result2.dat
test:
	clear
	gcc -mfma -Wall main2.c headerFiles/matrix_lib.c headerFiles/file_reader.c headerFiles/time.c -o main2
	./main2
nv:
	clear
	@nvcc -o teste matrix_lib_teste.cu headerFiles/time.c matrix_lib.cu matrix_lib.c
	@./teste 5.0 1024 1024 1024 1024 256 4096 7 src/A_1024.dat src/B_1024.dat src/result1.dat src/result2.dat
	@rm teste
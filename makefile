all:
	clear
	gcc -Wall matrix_lib_test.c headerFiles/matrix_lib.c headerFiles/file_reader.c headerFiles/time.c -o main
	./main 5.0 512 512 512 512 src/matrix_A.dat src/matrix_B.dat src/result1.dat src/result2.dat
# test:
# 	clear
# 	gcc -Wall main2.c headerFiles/matrix_lib.c headerFiles/file_reader.c headerFiles/time.c -o main2
# 	./main2
task0.o: task0.c
	gcc -c task0.c
functs.o: mylib/functs.c
	gcc -c mylib/functs.c
finalresult : task0.o mylib/functs.o
	gcc -o finalresult task0.o mylib/functs.o -lm
	rm -rf *.o mylib/*.o
all: finalresult

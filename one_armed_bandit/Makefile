bandit.o: bandit.c
	gcc -c bandit.c
funct.o: myLib/funct.c
	gcc -c myLib/funct.c
result_bandit : bandit.o myLib/funct.o
	gcc -o result_bandit bandit.o myLib/funct.o -lm
	rm -rf *.o myLib/*.o
all: result_bandit

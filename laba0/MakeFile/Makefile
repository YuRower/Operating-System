main1.o: main1.c
	gcc -c main1.c
functs.o: mylib/functs.c
	gcc -c mylib/functs.c
finalresult : main1.o mylib/functs.o
	gcc -o finalresult main1.o mylib/functs.o -lm
	rm -rf *.o mylib/*.o
all: finalresult

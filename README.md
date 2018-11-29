# Operating-System

--------------------------
run SeparateCompilation

gcc -c main1.c

cd mylib

gcc -c functs.c

cd ..

gcc -o result main1.o mylib/functs.o -lm

./result

-------------------------
run MakeFile

make finalresult

./finalresult


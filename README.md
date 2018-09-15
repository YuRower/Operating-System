# Operating-System
Operating System labs
--------------------------
run lab1

gcc -o result/result main1.c functs.c -lm

cd result

./result

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

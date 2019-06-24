#
# CSSE 132
# Rose-Hulman Institute of Technology
# Computer Science and Software Engineering
#
# Makefile - This is used to make the homework.
#


test: test.c unity/unity.o problems.c asm.o
	gcc -g -o test test.c problems.c asm.o unity/unity.o 

unity/unity.o: unity/unity.c
	gcc -c -o unity/unity.o -Iunity unity/unity.c

asm.o: problems.s
	gcc -c -o asm.o problems.s

clean:
	rm test asm.o unity/unity.o

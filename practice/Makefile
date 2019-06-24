#
# CSSE 132
# Rose-Hulman Institute of Technology
# Computer Science and Software Engineering
#
# Makefile - This is used to make the practice problems
#


test: test.c unity/unity.o problems.c
	gcc -g -o test test.c problems.c unity/unity.o 

unity/unity.o: unity/unity.c
	gcc -c -o unity/unity.o -Iunity unity/unity.c

clean:
	rm test unity/unity.o

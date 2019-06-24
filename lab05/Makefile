#
# CSSE 132
# Rose-Hulman Institute of Technology
# Computer Science and Software Engineering
#
# Makefile - This is used to make the lab.  This is not a
# file you need to hand in, unless you modify it.
#


# By default, make "lab5" and "test"
# TODO: add your new rule's name to this list when you've created it
default: lab5 test simple

# TODO: add your new rule here to make "simple".
# Remember, the format for a rule is:
# product: files needed
# 	commands to make product from files needed
#	...

# Produce the app
lab5: data.h data.c lab5.c
	gcc -g -o lab5 lab5.c data.c

test: data.h data.c test.c unity/unity.o
	gcc -g -Wl,-wrap,fprintf -o test test.c data.c unity/unity.o

simple: data.h data.c simple.c
	gcc -g -o simple simple.c data.c

unity/unity.o: unity/unity.c
	gcc -c -o unity/unity.o -Iunity unity/unity.c

# TODO: also add your new rule's name to this list when you've created it
clean:
	rm lab5 test unity/unity.o

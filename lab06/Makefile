#
# CSSE 132
# Rose-Hulman Institute of Technology
# Computer Science and Software Engineering
#
# Makefile - This is used to make the lab.  This is not a 
# 					file you need to hand in, unless you modify it.
#


# By default, make both "local" and "test"
default: local test

# Produce the app
local: data.h data.c local.c
	gcc -g -o local local.c data.c

test: data.h data.c test.c unity/unity.o
	gcc -g -Wl,-wrap,fprintf,-wrap,fgets -o test test.c data.c unity/unity.o 

unity/unity.o: unity/unity.c
	gcc -c -o unity/unity.o -Iunity unity/unity.c

clean:
	rm local test unity/unity.o

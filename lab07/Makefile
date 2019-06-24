#
# CSSE 132
# Rose-Hulman Institute of Technology
# Computer Science and Software Engineering
#
# Makefile - This is used to make the lab.  This is not a 
# 					file you need to hand in, unless you modify it.
#


# By default, make server, client, local and  test
default: server client local test

# Produce the app
local: data.h data.c local.c
	gcc -g -o local local.c data.c

server: data.h data.c server.c
	gcc -g -o server server.c data.c

client: client.c
	gcc -g -o client client.c

test: data.h data.c test.c unity/unity.o
	gcc -g -Wl,-wrap,fprintf,-wrap,fgets -o test test.c data.c unity/unity.o 

unity/unity.o: unity/unity.c
	gcc -c -o unity/unity.o -Iunity unity/unity.c

clean:
	rm server client local test unity/unity.o

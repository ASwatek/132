#
# Makefile for CSSE 132 Final Exam
#

# IMPORTANT: all lines after each rule must start with a tab (not spaces)

test: test.c unity/unity.o part1.c
	gcc -g -o test test.c part1.c unity/unity.o

unity/unity.o: unity/unity.c
	gcc -c -o unity/unity.o -Iunity unity/unity.c

wordsearch: wordsearch.c part1.c
	gcc -g -o wordsearch wordsearch.c

clean:
	rm -f test unity/unity.o wordsearch

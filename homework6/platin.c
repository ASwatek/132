/*
 * CSSE 132
 * Rose-Hulman Institute of Technology
 * Computer Science and Software Engineering
 *
 * platin.c: this file is where you implement the platin program
 *             for the homework assignment.
 *
 * This file contains code for homework in the CSSE 132 class.
 * When you edit this file for class, be sure to put your name here!
 *
 * Edited by
 * NAME:
 * Austin Swatek
 */
#include <stdio.h>

/* This will allow you to use your string functions in problems.c */
#include "problems.c"


/**
 * Here's the main function for our program.  Put all your code in here unless
 * you want to make a helper function.
 *
 * WARNING: there are no tests provided for this program.  You'll have to test
 * it by making and running platin and checking what it does.
 *
 * This program runs in two modes:
 * 1. If there are arguments, convert and print them.
 * 2. If there are no arguments, read input and convert
 *    each line of input.
 *
 * WE RECOMMEND YOU IMPLEMENT THE FIRST MODE, TEST IT, THEN ADD SUPPORT FOR THE
 * SECOND ONE.
 *
 * Mode 1: if there are arguments (that means argc is greater than 1),
 * your program should print the pig-latin version of each argument, one per
 * line.  Mode 1 example:
 *    [foo@pi]$ ./platin awesome sauce
 *    awesomeyay
 *    aucesay
 *    [foo@pi]$
 *
 * Mode 2: If there are no arguments, read lines of input using fgets and pigify
 * each line. Be sure to remove the newline character from each line by converting
 * it to a null character.
 *   ASSUME there is only one word per line.
 *
 * In this example for Mode 2 below, a + means it was typed, and a - means the
 * program printed it. The last line of input is just the enter key):
 *    [foo@pi]$ ./platin
 * +  awesome
 * -  awesomeyay
 * +  sauce
 * -  aucesay
 * +  foo
 * -  oofay
 * +
 *    [foo@pi]$
 *
 *
 * HINT: look at the manual page for fgets(): 'man 3 fgets'.  It will read code
 *       into a buffer.  You can use fgets() with stdin by creating an array of
 *       chars on the stack, then telling fgets to read input from stdin into
 *       that array.
 *
 *       ASSUME the input will never be bigger than 100 characters.
 *
 * HINT: use your functions from problems.c.  The include statement at the top
 *       of this file makes them available (do not copy and paste them into this
 *       file.
 *
 *
 * @param argc - the number of arguments to this program
 *               (including the program name)
 * @param argv - an array of strings representing the arguments, where argv[0] is
 *               the name of the program you're running.
 * @return 0. Just return 0.
 */
int main(int argc, char** argv)
{
  // : Mode 1 -- do this first.
  // If there are arguments (more than just the program name), pigify them and
  // return.
  if(argc > 1){
   for(int i=1; i<argc; i++){
    char* ret = pigify(argv[i]);
    printf("%s\n", ret);
    free(ret);
   }
  return 0;
  }


//FREE AFTER DOING FREE AFTER DOING FREE AFTER DOING FREE AFTER DOING FREE AFTER DOING


  // : Mode 2: since there were no arguments, read words one at a time
  // (using fgets) until an empty word shows up. When you read an empty word,
  // stop reading and return.
  char input[128];
  while(1){
   fgets(input, 100, stdin);
   if(input[0]=='\n') return 0;
//this loop right here is a way to stop my \n from being read in and spit out
//maybe it could be done with regex stuff but this works so it works
   for(int i=0; i<strlen(input); i++){
    if(input[i]=='\n'){
     input[i]='\0';
     break;
    }
   }

   char* ret = pigify(input);
   printf("%s\n", ret);
   free(ret);
  }
  return 0;
}

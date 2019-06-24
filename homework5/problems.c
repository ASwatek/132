/*
 * CSSE 132
 * Rose-Hulman Institute of Technology
 * Computer Science and Software Engineering
 *
 * problems.c: this file is where you implement your solutions
 *             for the homework assignment.
 *
 * This file contains code for homework in the CSSE 132 class.
 * When you edit this file for class, be sure to put your name here!
 *
 * Edited by
 * NAME: Austin Swatek
 *
 */
#include <stdlib.h>
#include <stdio.h>

int length(char* string)
{
 int count = 0;
 int i = 0;
 while(string[i]!='\0'){
  count = count + 1;
  i = i + 1;
 }
 return count;
}


/**
 * This function allocates a new string that contains every other character
 * from the input string.  
 * For example, skipper("AbAbAb") returns "AAA"
 *
 * BE SURE to allocate the right number of bytes, no more and no less.
 * DO NOT de-allocate or free the string after you make it.
 *
 * IMPORTANT: any code using this function MUST de-allocate the string.
 *
 * HINT: you may want to copy your "length" function from HW4 into this file so
 * you can use it.
 *
 * @param input - the string to copy some characters from
 * @return the address of a newly allocated string
 */
char* skipper(char* input)
{
  // your code goes here.  You may also want to change the return
  // statement.
//  int inputLength = 0;
//  printf("hi");
//  inputLength = length(input);
//  printf("zz");
//  int useThis = inputLength/2;
//  char *ret[useThis];
//  char *ret[2];
//  ret = (char *) malloc(15);
//  char *newRet = (char *) malloc(sizeof(char)*useThis);
//  for(int i=0; i<inputLength; i+=2){
//   ret[i/2]=input[i];
//  }
//  return ret;
  int inputLength = length(input);
  char* ret;
  ret = malloc(inputLength * sizeof(char));

  for(int i=0; i<inputLength; i+=2){
    ret[i/2]=input[i];
  }
  return ret;
}

/**
 * This function reads a string representation of a positive integer and
 * returns the value as an int.
 * For example, string2num("10") returns 10.
 *
 * You may assume the input is a properly formed positive integer.  This means
 * you do not have to handle negative integers or non-integer characters.
 * you MUST NOT call other c functions in string2num unless you implement them
 * yourself in this file.
 *
 * HINT: you may want to copy your "length" function from HW4 into this file so
 * you can use it here.
 *
 * @param input - the string to interpret as an integer
 * @return the value as an integer
 */
int string2num(char* input)
{
  // : your code goes here.  You may also want to change the return
  // statement.
  int inputLength = length(input);
  int ret = 0;
  int mult = 1;
for(int i=0; i<inputLength; i++){
//i could add more cases if i knew i had to go higher
   if(inputLength-i==9) mult=100000000;
   if(inputLength-i==8) mult=10000000;
   if(inputLength-i==7) mult=1000000;
   if(inputLength-i==6) mult=100000;
   if(inputLength-i==5) mult=10000;
   if(inputLength-i==4) mult=1000;
   if(inputLength-i==3) mult=100;
   if(inputLength-i==2) mult=10;
   if(inputLength-i==1) mult=1;
   if(input[i]=='1') ret+= mult*1;
   if(input[i]=='2') ret+= mult*2;
   if(input[i]=='3') ret+= mult*3;
   if(input[i]=='4') ret+= mult*4;
   if(input[i]=='5') ret+= mult*5;
   if(input[i]=='6') ret+= mult*6;
   if(input[i]=='7') ret+= mult*7;
   if(input[i]=='8') ret+= mult*8;
   if(input[i]=='9') ret+= mult*9;
}
 return ret;
}

/** DO NOT create a main function in this file or the test executable won't work. **/

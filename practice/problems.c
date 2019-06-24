/*
 * CSSE 132
 * Rose-Hulman Institute of Technology
 * Computer Science and Software Engineering
 *
 * problems.c: this file is where you implement your solutions
 *             for the practice problems assignment.
 *
 * This file contains code for practice in the CSSE 132 class.
 * When you edit this file for class, be sure to put your name here!
 *
 * Edited by
 * NAME:
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/**
 * This function returns the product of a and b
 * WITHOUT USING the multiply (*) operator.
 *
 * Hint: use a loop.
 *
 * You may assume a and b are both non-negative.
 *
 * @params a,b - numbers to multiply
 * @return the product of a and b.
 */
int multiplyNoStar(int a, int b)
{
  //ODO: implement this function
  int ret = 0;
  for(int i=0; i<a; i++){
   ret+=b;
  }
  return ret;
}

/**
 * This function multiplies all the entries in an array.
 *
 * @param array - an array of integers
 * @param len - the number of integers in the array
 * @return the product of all integers in the array.
 */
int arrayprod(int* array, int len)
{
  //ODO: implement this function
  //ODO: this really isnt a good solution because it assumes there are items in here
  if(len<2) return 0;
  int ret = 1;
  for(int i=0; i<len; i++){
   ret*=array[i];
  }
  return ret;
}

/**
 * This function reverses the characters in a string by
 * MODIFYING the input string.
 * If there are an odd number of characters, the middle character
 * doesn't move.
 *
 * You can assume string is not NULL and is properly null-terminated.
 *
 * @param string - a sequence of characters to reverse
 * @return nothing: the input is modified.
 */
void reverseString(char* string)
{
  //ODO: implement this function
  int len = strlen(string);
  char temp;
  for(int i=0; i<len/2; i++){
   temp = string[len-1-i];
   string[len-1-i] = string[i];
   string[i] = temp;
  }
  return;
}

/**
 * Returns the number of vowels (upper and lower case) in a string.
 * A, E, I, O and U are vowels.
 *
 * Hint: you may want to create a helper function that determines
 * if a character is a vowel or not.  Remember, 0 is false and all 
 * other integers are true.
 *
 * You can assume string is non-NULL.
 *
 * @param string - the string to examine
 * @return the number of vowels.
 */
int countVowels(char* string)
{
  //ODO: implement this function
  int ret = 0;
  for(int i=0; i<strlen(string); i++){
   if(string[i]=='A' || string[i]=='E' || string[i]=='I' || string[i]=='O' || string[i]=='U' || string[i]=='a' || string[i]=='e' || string[i]=='i' || string[i]=='o' || string[i]=='u') ret++;
  }
  return ret;
}

/**
 * Creates a copy of the input string without vowels.  This function must
 * malloc() the correct number of bytes for the new string (the one without
 * vowels).  It will NOT free() the string -- the caller will free the string.
 *
 * You may assume string is not NULL.
 *
 * Example: removeVowels("this") returns a string "ths"
 *
 * Hint: use countVowels() to figure out how much space to malloc.  You may
 *       also find your helper function from countVowels handy.
 *
 * @param string - the string to copy.
 * @return a new malloc()'ed string that is the same as the input string
 *         but missing its vowels.
 */
char* removeVowels(char* string)
{
  //TDO: implement this function
  int len = strlen(string);
  int vow = countVowels(string);
  int real = len-vow;
  char* ret = malloc(sizeof(char)*(real+1));//+1 for null term
  int passed = 0;

  for(int i=0; i<len; i++){
   if(string[i]=='A' || string[i]=='E' || string[i]=='I' || string[i]=='O' || string[i]=='U' || string[i]=='a' || string[i]=='e' || string[i]=='i' || string[i]=='o' || string[i]=='u') passed++;
   else ret[i-passed]=string[i];
  }

  ret[real]='\0';
  return ret;
}

/** DO NOT create a main function in this file or the test executable won't work. **/

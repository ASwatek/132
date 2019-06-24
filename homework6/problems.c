/*
 * CSSE 132
 * Rose-Hulman Institute of Technology
 * Computer Science and Software Engineering
 *
 * problems.c: this file is one file where you implement solutions
 *             for the homework assignment.
 *
 * This file contains code for homework in the CSSE 132 class.
 * When you edit this file for class, be sure to put your name here!
 *
 * Edited by
 * NAME:
 * Austin Swatek
 */
#include <stdlib.h>
#include <string.h>

/**
 * This function determines if the string passed in begins with
 * one of the characters in a target string.
 *
 * Examples:
 *   startsWith("foo", "f") => 1
 *   startsWith("foo", "") => 0
 *   startsWith("foo", "X") => 0
 *   startsWith("foo", "Xfg") => 1
 *   startsWith("ate", "aeiou") => 1
 *
 * @param input - the string to examine
 * @return 1 if it begins with a character in the target string,
 *         0 otherwise.
 */
int startsWith(char* input, char* targets)
{
  // : implement this function here
  int i=0;
  while(targets[i]!='\0'){
   if(input[0]==targets[i]) return 1;
   i++;
  }
  return 0;
}


/**
 * This function determines if the string passed in begins with
 * a vowel (either upper case or lower case).
 *
 * HINT: call startsWith() above (once you've finished it) with
 *   a string containing all the vowels a, e, i, o, u (in both
 *   upper and lower case).
 *
 * @param input - the string to examine
 * @return 1 if it begins with a vowel
 *         0 otherwise.
 */
int startsWithVowel(char* input)
{
  // : implement this function here
  char stuff[10] = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
  return startsWith(input, stuff);
}

/**
 * This function allocates a new string (on the heap) and fills it
 * with a basic pig-latin version of the input word.
 *
 * DO NOT de-allocate the string in this function (the caller will do that).
 *
 *
 * Basic pig-latin rules are as follow:
 *
 * 0. If the input string is empty (just a '\0'), return a copy of
 *     the empty string (a string with only the null char in it).
 * 1. If a word starts with a vowel, add "yay" to the end of the word.
 *     Example: "ate" => "ateyay"
 * 2. If a word starts with a consanant, move the first letter to the
 *    end of the string, and then append "ay".
 *     Example: "code" => "odecay"
 *
 * HINTS:
 *  - use strlen() from string.h to measure the length of a string.
 *  - use strncpy() from string.h to copy a string from one array
 *     to another.  (See 'man 3 strncpy' for details.)
 */
char* pigify(char* input)
{
  // : implement this function here
  // IMPORTANT: DO NOT free any malloc (the caller will do that)
  int length = strlen(input);
  if(length==0) return input;
//  char* ret = malloc(strlen(input)*sizeof(char)+1
  if(startsWithVowel(input)==1){//if vowel: add "yay"
   char* ret = malloc((length+4)*sizeof(char));	//+3 for "yay", +1 for nullTerminator
   strncpy(ret, input, length);
   ret[length]='y';
   ret[length+1]='a';
   ret[length+2]='y';
   ret[length+3]='\0';
   return ret;
  }//if not vowel: move [0] to original end, then "ay"
  char* ret =  malloc((length+3)*sizeof(char));//+2 for "ay", +1 for nullTerminator
  for(int i=1; i<length; i++){//shift letters
   ret[i-1]=input[i];
  }
  ret[length-1]=input[0];
  ret[length]='a';
  ret[length+1]='y';
  ret[length+2]='\0';
/*
  strncpy(ret, input, length);
  char temp = input[length-1];
  ret[length-1] = input[0];
  ret[0] = temp;
  ret[length]='a';
  ret[length+1]='y';
  ret[length+2]='\0';
*/
  return ret;
}

/** DO NOT create a main function in this file or the test executable won't work. **/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
 * wordsearch.c
 * Austin Swatek
*/


  /**
   * sevenUp()
    *
     * Creates a copy of an array with values 7 greater than the original.
      *
       * Given an array and its length, this function creates a copy of the array on
* the heap, adds seven to each element and then returns a pointer to the new
 * array.
  *
   * For example, given an array {1, 2, 3}, this creates and returns
    * a new array {8, 9, 10}.
     *
      * Use malloc() in this function.
       * DO NOT free() anything you return (the code that calls sevenUp will
*   do this).
 *
  * YOU MAY NOT CALL OTHER FUNCTIONS FROM sevenUp() EXCEPT malloc() and free()
   * UNLESS YOU FIRST IMPLEMENT THEM IN THIS FILE.
    *
     * ASSUME: array lengths are always a positive integer > 0
      *
       * @param arr - the input array to copy
* @param length - the length of arr
 * @returns - a pointer to the new array
  */
  int* sevenUp(int* arr, int length) {
    // ODO: implement this function
      int* ret = malloc(sizeof(int)*length);
      
for(int i=0; i<length; i++){
   ret[i]=arr[i]+7;
     }
     
       return ret;
       }
       
       
       /**
* isAlphaNumeric()
 *
  * Checks if the given character is an alphanumeric character.
   * Alphanumeric (sometimes seen as alphameric) is a term encompassing
    * all the letters as well as the numerals.
     * For example:
      *  isAlphaNumeric('b') returns one
       *  isAlphaNumeric('L') returns one
*  isAlphaNumeric('0') returns one
 *  isAlphaNumeric('9') returns one
  *  isAlphaNumeric(';') returns zero
   *  isAlphaNumeric('.') returns zero
    *  isAlphaNumeric(' ') returns zero
     *
      * YOU MAY NOT CALL OTHER FUNCTIONS FROM isAlphaNumeric UNLESS YOU FIRST
       * IMPLEMENT THEM IN THIS FILE.
*
 * @param c - The input character.
  * @returns - One if the given character is alphanumeric,
   *            otherwise returns zero.
    */
    int isAlphaNumeric(char c)
    {
      // ODO: implement this function
if((c>47 && c<58) || (c>64 && c<91) || (c>96 && c<123)) return 1;
  return 0;
  }
  
  
  /**
   * findNextWord()
    *
     * Given a string, returns a pointer to the next word in an input
      * string. If the input string doesn't start with a word, findNextWord
       * returns a pointer to the first word found in the string.
* If there are no more words in the string, this function returns NULL.
 *
  * For example, findNextWord("one two") would return a pointer to the
   * character 't' in the original input string.  More specifically:
    *
     *     char* x = "one two";
      *     char* y = findNextWord(x);
       *
* After this, x and y point to parts of the same string:
 *
  *   "one two"
   *    ^   ^
    *    |   |
     *    x   y
      *
       * If the input string does not begin with a word, findNextWord() returns
* a pointer to the first word:
 *
  *     char* a = "---- two";
   *     char* b = findNextWord(x);
    *
     *   "---- two"
      *    ^    ^
       *    |    |
*    a    b
 *
  * If there are no more words, this function returns NULL:
   *
    *    findNextWord("one")      --> NULL
     *    findNextWord(".#*@& \n") --> NULL
      *    findNextWord("")         --> NULL
       *    findNextWord(NULL)       --> NULL
*
 * For more examples see the tests in test.c
  *
   * YOU MAY NOT CALL OTHER FUNCTIONS FROM findNextWord UNLESS YOU FIRST
    * IMPLEMENT THEM IN THIS FILE.
     *
      * @param text - the input string
       * @returns - a pointer to the next word if the string starts with a word,
*          - a poitner to the first word if the string starts with a
 *             non-word character (not alphanumeric)
  *          - NULL if there are no more words
   *
    */
    char* findNextWord(char* text)
    {
      // ODO: implement this function
if(text==NULL) return NULL;
  int length=0;
    while(text[length]!='\0') length++;
      if(length<2) return NULL;
      
int index=0;
  while(text[index]!=' ' && index<length){
     index++;
       }
 int test=index;
   for(int i=index; i<length; i++){
      if(text[i]==' ' || isAlphaNumeric(text[i])!=1){
  test++;
     }else{
 break;
    }
      }
      
if(test==length) return NULL;
  return text+test;
  }
  
  
  /**
   * startsWithWord()
    *
     * Checks if a string begins with a given word.
      *
       * NOTE: this is not a substring check.  For example, the string "oranges rock"
* does not begin with the word "orange"!  These are different words, but they
 * start with the same characters.
  *
   * Some examples (not exhaustive):
    *   startsWithWord("orange rocks", "orange") --> 1 (or other nonzero number)
     *   startsWithWord("oranges rock", "orange") --> 0
      *   startsWithWord("", "orange")             --> 0
       *   startsWithWord("one two three", "one")   --> 1
*   startsWithWord("  one two thr", "one")   --> 0
 *
  * See test.c for more examples.
   *
    * YOU MAY NOT CALL OTHER FUNCTIONS FROM startsWithWord UNLESS YOU FIRST
     * IMPLEMENT THEM IN THIS FILE.
      *
       * @param text - the string to search
* @param word - the word that "text" must begin with
 * @returns - a non-zero number if a given string begins with a word.  If it doesn't, return 0.
  */
  int startsWithWord(char* text, char* word)
  {
    // ODO: implement this function
      if(text==NULL || word==NULL) return 0;
int wordLen=0;
  while(word[wordLen]!='\0') wordLen++;
    int textLen=0;
      while(text[textLen]!='\0') textLen++;
      
int broken=0;
  for(int i=0; i<wordLen; i++){
     if(word[i]!=text[i]) return 0;
       }
       
 if(textLen>wordLen){
    if(text[wordLen]!=' ') return 0;
      }
return 1;
}


/**
 * countMatchingWords()
  *
   * Counts the number of words in a string that match a given word.
    *
     * HINT: use the other functions you wrote in this file.
      *
       * Some examples (not exhaustive):
*   countMatchingWords("one", "one")             --> 1
 *   countMatchingWords("ne", "one")              --> 0
  *   countMatchingWords("one one one", "one")     --> 3
   *   countMatchingWords("   one ones one", "one") --> 2
    *
     * See test.c for more examples.
      *
       * YOU MAY NOT CALL OTHER FUNCTIONS FROM countMatchingWords UNLESS YOU FIRST
* IMPLEMENT THEM IN THIS FILE.
 *
  * @param text - the string to search
   * @param word - the word to count
    * @returns - the number of times word appears in text.
     */
int countMatchingWords(char* text, char* word)
{
  // ODO: implement this function
  if(text==NULL || word==NULL) return 0;
  int wordLen=0;
  while(word[wordLen]!='\0') wordLen++;
  int textLen=0;
  while(text[textLen]!='\0') textLen++;
  int count=0;

/*
  if(startsWithWord(text, word)) count++;
  char* ret = findNextWord(text);

  while(ret!=NULL){
   if(startsWithWord(ret, word)) count++;
   ret = findNextWord(ret);
  }*/
  
  for(int i=0; i<textLen-wordLen+1; i++){
   for(int j=0; j<wordLen; j++){
    if(text[i+j]!=word[j]) break;
    if(j==wordLen-1){
     if(text[i+j]==word[j] && isAlphaNumeric(text[i+j+1])==0) count++;
    }
   }
  }

 return count;
}
 // DO NOT create a main function in this file or the tests will not compile.



int main(int argc, char** argv){
  if(argc<3){
   printf("Usage: ./wordsearch <file> <word> [<word> ...]\n");
   return -1;
  }
  char* fileName = argv[1];
  int len = strlen(fileName);
  if(len<5 || ((fileName[len-1]!='t' && fileName[len-2]!='x' && fileName[len-3]!='t' && fileName[len-4]!='.')  )  ){
   printf("Usage: ./wordsearch <file> <word> [<word> ...]\n");
   return -1;
  }
  char buf[512];

  for(int i=2; i<argc; i++){
   FILE* input = fopen(fileName, "r");
   int count=0;

   while(feof(input)==0){
    fgets(buf, 255, input);
    count+=countMatchingWords(buf, argv[i]);
   }
   printf("Occurrences of [%s]: %d\n", argv[i], count);
   fclose(input);
  }
  return 1;
}

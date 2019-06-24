#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int isUpper(char c)
{
  return c >= 'A' && c <= 'Z';
  }
  
  /**
   * Returns 1 if the given character is a lower case letter, 0 otherwise.
    */
    int isLower(char c)
    {
      return c >= 'a' && c <= 'z';
      }
      
      /**
       * Transposes an upper-case input character "num" spots forward in the
* alphabet, wrapping around to the beginning.
 * 
  * For example:
   *    transposeUpper('A', 1) returns 'B'.
    *    transposeUpper('Z', 1) returns 'A'.
     *    transposeUpper('D', 3) returns 'G'.
      *
       * Assume:
*  num will always be positive
 *  c is an UPPERCASE letter (no numbers or special characters).
  *
   *  @param c: the character to transpose
    *  @param num: the number of positions to transpose it
     *  @return the transposed character.
      */
char transposeUpper(char c, unsigned int num)
{
// ODO: implement this
  if(c+num>90){
  /*
   int test = 90-c;
   while(c+test>90){//while for if the number is outrageous such as 1000. probably works, not sure
    test-=num;
   }
   c = 64+test+num;*/
   return c+num-26;
  }
//  c+=num;
  return c+num;
}

   /**
    * Same as transposeUpper, but for lower-case characters.
     */
char transposeLower(char c, unsigned int num)
{
       // ODO: implement this
  if(c+num>122){
 /*  int test = 122-c;
   
   while(c+test>122){
    test-=num;
   }
   c = 96+test+num;*/
   
   return c+num-26;
  }
  //c+=num;
  return c+num;
}


  /**
   * Transposes all the letters in the string, but leaves the non-letter characters alone.
    * This function also allocates space and COPIES the input string into the new
     * space.  Return a pointer to the new string.
      *
       * For example, after this line:
*   char* result = transposeString("A big Fox.", 2);
 * result points to "C dki Hqz." and needs to be free()'ed.
  *
   * HINT: use isUpper and isLower!
    * HINT: You will also need to use malloc.
     *
      * It is ok to assume:
       *  - the inputString is well-formed (null-terminated)
*  - num is positive
 *
  * @param inputString: a C string to read and transpose
   * @param num: the number of positions to transpose each letter
    */
char* transposeString(const char* inputString, unsigned int num)
{
      // ODO: implement this
  int retLen = strlen(inputString);
  char* ret = malloc(sizeof(char)*retLen);
  for(int i=0; i<retLen; i++){
   if(isUpper(inputString[i])) ret[i]=transposeUpper(inputString[i], num);
   else if(isLower(inputString[i]))  ret[i]=transposeLower(inputString[i], num);
   else ret[i]=inputString[i];	//for numbers and spaces and nonletters
  }
  return ret;
}

int main(int argc, char** argv){
  char* fileName = argv[1];
  int num = atoi(argv[2]);
//  int length = strlen(fileName);
 // char* outputName = malloc((length+4)*sizeof(char));//+4 .txt +1 \0
 // memcpy(outputName, fileName, length-4);
 // strcat(outputName, ".txt\0");
  FILE* input = fopen(fileName, "r");
 // FILE* output = fopen(outputName, "w");
//  int index;
  char toEdit[256];
//  char* transposed;
  while(feof(input)==0){//used for multiple lines
//   index = 0;
   if(fgets(toEdit, 255, input)!=NULL){
    char* transposed = transposeString(toEdit, num);
    transposed[strlen(toEdit)-1]='\0';
    printf("%s\n", transposed);
    free(transposed);
   }//if(fgets)
  }//while(feof)
//  fgets(toEdit, 255, input);
//  char* transposed = transposeString(toEdit, num);
//  transposed[strlen(toEdit)-1]='\0';
//  printf("%s", transposed);
  fclose(input);
//  free(transposed);
  return 0;
}//main

//Austin Swatek

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv){
  if(argc!=3){
   printf("%s\n", "Usage: ./shuffle string1 string2");
   return 0;
  }
  char* str1=argv[1];
  char* str2=argv[2];
  int length1=0;
  int length2=0;
  while(str1[length1]!='\0'){
   length1++;
  }
  while(str2[length2]!='\0'){
   length2++;
  }
  if(length1!=length2){
   printf("%s\n", "ERROR: The input strings must be the same length.");
   return 0;
  }
  char* orig1 = malloc(length1*sizeof(char));
  char* orig2 = malloc(length2*sizeof(char));
  for(int i=0; i<length1; i++){
   orig1[i] = str1[i];
   orig2[i] = str2[i];
  }
//  char* orig = argv[1];
//  char* orig2 = argv[2];
  shuffle(str1, str2);
//OLD:  printf("argv[1] @ argv[2] -> %s @ %s\n", str1, str2 );
  printf("%s @ %s -> %s @ %s\n", orig1, orig2, str1, str2); //NEW: now it actually prints the original strings
  free(orig1);
  free(orig2);
  return 0;
}

void shuffle(char* str1, char* str2){
  int length=0;
  while(str1[length]!='\0'){
   length++;
  }

  char* tempBig = malloc(2*length*sizeof(char));
  int k=0;
  for(int j=0; j<length; j++){
   tempBig[j*2] = str1[j];
   tempBig[j*2+1] = str2[j];
  }
  int half=length/2;

  for(int i=0; i<length; i++){
  str1[i]=tempBig[i];
  str2[i]=tempBig[i+length];
 }
  free(tempBig);
}

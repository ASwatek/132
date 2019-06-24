#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Austin Swatek

int isWordChar(char x)
{
  if((x<='z' && x>='a') || (x<='Z' && x>='A')) return 1;
  return 0;
}

int wordlen(char* str)
{
  if(isWordChar(str[0])==0) return 0;
  int length = strlen(str);
  int i=0;
  while(i<length && isWordChar(str[i])==1){
   i++;
  }
  return i;
}

//assumes given "fileName.txt"
int main(int argc, char** argv){
  char* fileName = argv[1];
  int length = strlen(fileName);
  char* outputName = malloc((length+10)*sizeof(char));//+9 .censored +1 \0
  memcpy(outputName, fileName, length-4);
  strcat(outputName, ".censored\0");
  FILE* input = fopen(fileName, "r");
  FILE* output = fopen(outputName, "w");
  char toEdit[256];//i assume no line of text has more than toEdit's size of characters
  int index;
 while(feof(input)==0){//used for multiple lines
  index = 0;
  if(fgets(toEdit, 255, input)!=NULL){
   while(index<strlen(toEdit)){
    if(isWordChar(toEdit[index])){
     int count = wordlen(index + toEdit);
     if(count==4){
      toEdit[index+1]='*';
      toEdit[index+2]='*';
     }//if(count)
     index+=count;
    }//if(isWordChar)
    index++;
   }//while(index)
/** substring
   for(int i=0; i<strlen(toEdit); i++){
    char substr[256];
    if(isWordChar(toEdit[i])){
     strncpy(substr, toEdit+i, strlen(toEdit)-i);//substring of remaining to check/edit
//   printf("%s", substr);
     int count = wordlen(substr);
//   printf("%d", count);
     if(count==4){
      toEdit[i+1]='*';
      toEdit[i+2]='*';
     }
      i+=count-1;//so doesnt repeat indices check
    }
   }substring**/
/*   if(isWordChar(toEdit[i])){
    for(int j=i; j<strlen(toEdit); j++){
     substr[j-i]=toEdit[j];
    }
    if(wordlen(substr)==4){
     toEdit[i+1]='*';
     toEdit[i+2]='*';
    }
   }else{
    //increase to next index without doing anything
   }*/

   toEdit[index]='\0';
   fwrite(toEdit, 1, strlen(toEdit) , output);//up to strlen(toEdit) to prevent terrible random weird things
  }//if(fgets)
 }//while(feof)
 fclose(input);
 fclose(output);
 free(outputName);
 return 0;
}//main

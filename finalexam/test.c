/*
 * CSSE 132
 * Rose-Hulman Institute of Technology
 * Computer Science and Software Engineering
 *
 * test.c - Source file with tests for the homework.
 *          This is a file you need to hand in!
 *
 *          This file contains the tests you run to verify
 *          the code for the final exam.
 *
 * This file contains code used by the final exam in the CSSE 132 class.
 * If you edit this file for class, be sure to put your name(s) here!
 *
 * Edited by
 * NAME:
 *
 */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unity/unity.h"

// functions tested by this test harness
int*  sevenUp(int* arr, int length);
int   isAlphaNumeric(char c);
char* findNextWord(char* text);
int   startsWithWord(char* text, char* word);
int   countMatchingWords(char* text, char* word);


void setUp(void) { }
void tearDown(void) { }

// use this to put -1s in malloc space
void scrubHeap(int s, int v) {
  void* ptr = malloc(s);
  memset(ptr, -1, s);
  if(v > 0) { scrubHeap(s,--v); }
  free(ptr);
}


void
test_sevenUp(void)
{

  // two copies of the array (one for control in case the array is mutated by
  // sevenUp).
  const int arr0[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  int       arr1[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  int* rv;
  int i;

  scrubHeap(16, 8192);

  // TEST 1:
  // check that a one-element array works (value of 1 => 8)
  rv = sevenUp(arr1, 1);
  TEST_ASSERT_NOT_NULL_MESSAGE(rv, "sevenUp should not return NULL.");
  TEST_ASSERT_EQUAL_INT(arr0[0], arr1[0]);   // old array
  TEST_ASSERT_EQUAL_INT(8,       rv[0]);     // new array
  if (rv)  free(rv);
  scrubHeap(16, 8192);

  // TEST 2:
  // check that a 9 element array works
  rv = sevenUp(arr1, 9);
  TEST_ASSERT_NOT_NULL_MESSAGE(rv, "sevenUp should not return NULL.");
  for(i=0; i<9; i++) {
    TEST_ASSERT_EQUAL_INT(arr0[i],     arr1[i]); // old array
    TEST_ASSERT_EQUAL_INT(arr0[i] + 7, rv[i]);   // new array
  }
  if (rv)  free(rv);
  scrubHeap(16, 8192);

  // TEST 3:
  // fill the array with random numbers and check that it still works
  for(i=0; i<10; i++) {
    arr1[i] = rand();
  }
  rv = sevenUp(arr1, 10);
  TEST_ASSERT_NOT_NULL_MESSAGE(rv, "sevenUp should not return NULL.");
  for(i=0; i<10; i++) {
    TEST_ASSERT_EQUAL_INT(arr1[i] + 7, rv[i]);   // new array
  }
  if (rv)  free(rv);
  scrubHeap(16, 8192);

}

void
test_isAlphaNumeric(void)
{
  int rv;

  TEST_ASSERT_EQUAL(1, isAlphaNumeric('a'));
  TEST_ASSERT_EQUAL(1, isAlphaNumeric('W'));
  TEST_ASSERT_EQUAL(1, isAlphaNumeric('A'));
  TEST_ASSERT_EQUAL(1, isAlphaNumeric('k'));
  TEST_ASSERT_EQUAL(1, isAlphaNumeric('3'));
  TEST_ASSERT_EQUAL(1, isAlphaNumeric('N'));
  TEST_ASSERT_EQUAL(1, isAlphaNumeric('z'));
  TEST_ASSERT_EQUAL(1, isAlphaNumeric('Z'));
  TEST_ASSERT_EQUAL(1, isAlphaNumeric('9'));
  TEST_ASSERT_EQUAL(1, isAlphaNumeric('0'));
  TEST_ASSERT_EQUAL(0, isAlphaNumeric(' '));
  TEST_ASSERT_EQUAL(0, isAlphaNumeric('\n'));
  TEST_ASSERT_EQUAL(0, isAlphaNumeric('.'));
  TEST_ASSERT_EQUAL(0, isAlphaNumeric('*'));
  TEST_ASSERT_EQUAL(0, isAlphaNumeric('_'));
  TEST_ASSERT_EQUAL(0, isAlphaNumeric('\t'));
  TEST_ASSERT_EQUAL(0, isAlphaNumeric('\0'));
}

void
test_findNextWord()
{
  int i = 0;
  //char* findNextWord(char* text);
  char* myStr = "This is  a long,\t long string; with punctuation -- in weird\n spots!";

  // the next word in the input string should be "is"
  TEST_ASSERT_EQUAL_STRING_LEN("is", findNextWord("This is"), 2);

  // the next word in the input string should be "apple"
  TEST_ASSERT_EQUAL_STRING_LEN("apple", findNextWord(",#(*\t apple"), 5);

  // check for null return values
  TEST_ASSERT_NULL(findNextWord("This"));
  TEST_ASSERT_NULL(findNextWord(NULL));

  // this finds the fourth word ("long")
  TEST_ASSERT_EQUAL_STRING_LEN("long",   findNextWord(findNextWord(findNextWord(myStr))), 4);

  // this test "advances" through the big long string to find "string" (6th word)
  TEST_ASSERT_EQUAL_STRING_LEN("string", findNextWord( /*long*/
                                         findNextWord( /*long*/
                                         findNextWord( /*a*/
                                         findNextWord( /*is*/
                                         findNextWord(myStr))))), 4);
  char* x = myStr;
  // get the 11th word ("spots"), which is the last word (so 12th is null)
  for(i = 0; i < 10; i++) { x = findNextWord(x); TEST_ASSERT_NOT_NULL(x); }
  TEST_ASSERT_EQUAL_STRING_LEN("spots", x, 5);
  TEST_ASSERT_NULL(findNextWord(x));
}


void
test_startsWithWord()
{
  // int   startsWithWord(char* text, char* word);
  TEST_ASSERT_TRUE (startsWithWord("orange", "orange"));
  TEST_ASSERT_TRUE (startsWithWord("orange things rock", "orange"));
  TEST_ASSERT_FALSE(startsWithWord("orange things rock", "oranges"));
  TEST_ASSERT_FALSE(startsWithWord("orange things rock", "or"));
  TEST_ASSERT_FALSE(startsWithWord("", "or"));
  TEST_ASSERT_FALSE(startsWithWord(NULL, "or"));
  TEST_ASSERT_FALSE(startsWithWord("Some things", NULL));
}


void test_countMatchingWords()
{
 //(char* text, char* word);
 TEST_ASSERT_EQUAL_INT(0, countMatchingWords("", "orange"));
 TEST_ASSERT_EQUAL_INT(1, countMatchingWords("orange", "orange"));
 TEST_ASSERT_EQUAL_INT(0, countMatchingWords("oranges", "orange"));
 TEST_ASSERT_EQUAL_INT(2, countMatchingWords("orange orange", "orange"));
 TEST_ASSERT_EQUAL_INT(2, countMatchingWords(" pie orange.pie  ", "pie"));
 TEST_ASSERT_EQUAL_INT(1, countMatchingWords("pie\0pie orange.pie  ", "pie"));
 TEST_ASSERT_EQUAL_INT(0, countMatchingWords("salkdjflaksdnf lwnelkr nqwlkenjf lkasjfd lqhw;lajsdfjlk q;nj", "foo"));
 TEST_ASSERT_EQUAL_INT(3, countMatchingWords("The orange said oranges are orange in orange light.", "orange"));

 //some null checks
 TEST_ASSERT_EQUAL_INT(0, countMatchingWords(NULL, "foo"));
 TEST_ASSERT_EQUAL_INT(0, countMatchingWords("foo", NULL));
 TEST_ASSERT_EQUAL_INT(0, countMatchingWords(NULL, NULL));
}

void
main(int argc, char** argv)
{

  printf(">>>         Running tests for CSSE 132 Final Exam.   <<<\n");
  printf(" * NOTE: these tests are not complete, you may want to write more tests\n");
  printf(" * DEBUGGING HINT: use gdb on this test program if things crash!\n");
  printf(" * If tests fail, the output will tell you which line of test.c to examine\n\n");

  UnityBegin("test.c");

  RUN_TEST(test_sevenUp);
  RUN_TEST(test_isAlphaNumeric);
  RUN_TEST(test_findNextWord);
  RUN_TEST(test_startsWithWord);
  RUN_TEST(test_countMatchingWords);

  UnityEnd();
}

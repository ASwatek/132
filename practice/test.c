/*
 * CSSE 132
 * Rose-Hulman Institute of Technology
 * Computer Science and Software Engineering
 *
 * test.c - Source file with tests for the practice problems.
 *          This is a file you need to hand in!
 *          
 *          This file contains the tests you run to verify
 *          the code for practice problems.
 *
 * If you edit this file for class, be sure to put your name(s) here!
 *
 * Edited by
 * NAMES:
 *
 */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unity/unity.h"

// functions tested by this test harness
int multiplyNoStar(int a, int b);
int arrayprod(int* array, int len);
void reverseString(char* string);
int countVowels(char* string);
char* removeVowels(char* string);

void setUp(void) { }
void tearDown(void) { }

void
test_multiplyNoStar(void)
{
  TEST_ASSERT_EQUAL_INT(0, multiplyNoStar(0, 0));
  TEST_ASSERT_EQUAL_INT(0, multiplyNoStar(12, 0));
  TEST_ASSERT_EQUAL_INT(0, multiplyNoStar(0, 3));
  TEST_ASSERT_EQUAL_INT(12*15, multiplyNoStar(12, 15));
  TEST_ASSERT_EQUAL_INT(12*15, multiplyNoStar(12, 15));
}

void
test_arrayprod(void)
{
  int zero[2] = {1, 0};
  int zero_p = 0;

  int one[3] = {1, 2, 3};
  int one_p = 1 * 2 * 3;

  int two[5] = {6, 10, 10};
  int two_p = 6 * 10 * 10;

  TEST_ASSERT_EQUAL_INT(zero_p, arrayprod(zero, 2));
  TEST_ASSERT_EQUAL_INT(one_p, arrayprod(one, 3));
  TEST_ASSERT_EQUAL_INT(two_p, arrayprod(two, 3));
}

void
test_reverseString(void)
{
  char one[] = "";
  char two[] = "dcba";
  char three[] = "cba";
  char four[] = "emit eno";

  reverseString(one);
  TEST_ASSERT_EQUAL_STRING("", one); 

  reverseString(two);
  TEST_ASSERT_EQUAL_STRING("abcd", two);

  reverseString(three);
  TEST_ASSERT_EQUAL_STRING("abc", three);

  reverseString(four);
  TEST_ASSERT_EQUAL_STRING("one time", four);
}

void
test_countVowels(void)
{
  TEST_ASSERT_EQUAL_INT(0, countVowels(""));
  TEST_ASSERT_EQUAL_INT(0, countVowels("xbg"));
  TEST_ASSERT_EQUAL_INT(5, countVowels("aeiou"));
  TEST_ASSERT_EQUAL_INT(5, countVowels("the quick brown fox"));
}

void
test_removeVowels(void)
{
  // does a malloc for us.
  //char* removeVowels(char* string);
  char* output;

  TEST_ASSERT_EQUAL_STRING("", output=removeVowels(""));
  free(output);
  
  TEST_ASSERT_EQUAL_STRING("", output=removeVowels("aeiou"));
  free(output);

  TEST_ASSERT_EQUAL_STRING("txb", output=removeVowels("txb"));
  free(output);

  TEST_ASSERT_EQUAL_STRING("th qck brwn fx", output=removeVowels("the quick brown fox"));
  free(output);
}


int
main(int argc, char** argv)
{
  UnityBegin("Practice test.c");

  RUN_TEST(test_multiplyNoStar);
  RUN_TEST(test_arrayprod);
  RUN_TEST(test_reverseString);
  RUN_TEST(test_countVowels);
  RUN_TEST(test_removeVowels);

  UnityEnd();
}

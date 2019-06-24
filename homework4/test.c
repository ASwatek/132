/*
 * CSSE 132
 * Rose-Hulman Institute of Technology
 * Computer Science and Software Engineering
 *
 * test.c - Source file with tests for the homework.
 *          This is a file you need to hand in!
 *
 *          This file contains the tests you run to verify
 *          the code for homework 4.
 *
 * This file contains code used by labs in the CSSE 132 class.
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
int length(char* string);
int lengthNoArrays(char* string);
int bitDropper(int input);
int upcaseVowels(char* tochange);


void setUp(void) { }
void tearDown(void) { }

void
test_length(void)
{
  TEST_ASSERT_EQUAL_INT(0, length(""));
  TEST_ASSERT_EQUAL_INT(1, length("a"));
  TEST_ASSERT_EQUAL_INT(26, length("abcdefghijklmnopqrstuvwxyz"));
  TEST_ASSERT_EQUAL_INT(10, length("Whee! fun!"));
}

void
test_lengthNoArrays(void)
{
  TEST_ASSERT_EQUAL_INT(0, lengthNoArrays(""));
  TEST_ASSERT_EQUAL_INT(1, lengthNoArrays("a"));
  TEST_ASSERT_EQUAL_INT(26, lengthNoArrays("abcdefghijklmnopqrstuvwxyz"));
  TEST_ASSERT_EQUAL_INT(10, lengthNoArrays("Whee! fun!"));
}

void
test_bitDropper(void)
{
  TEST_ASSERT_EQUAL_INT(0x8, bitDropper(0x9));
  TEST_ASSERT_EQUAL_INT(0xAAAAAAA, bitDropper(0xFFFFFFF));
  TEST_ASSERT_EQUAL_INT(0x0000000, bitDropper(0x5555555));
  TEST_ASSERT_EQUAL_INT(0x0A0A0A0, bitDropper(0x5F5F5F5));

  // to test the most significant bit, we're going to be messing with
  // the sign bit (due to twos' complement).  This means we need to
  // explicitly tell C that we want this to be signed.
  TEST_ASSERT_EQUAL_INT((int)0xA0A0A0A0, bitDropper((int)0xF5F5F5F5));
}

void
test_upcaseVowels(void)
{
  char str0[] = "e";
  char str0_exp[] = "E";

  printf(" ... testing \"%s\" ... \n", str0);
  TEST_ASSERT_EQUAL_INT(1, upcaseVowels(str0));
  TEST_ASSERT_EQUAL_STRING(str0_exp, str0);

  char str1[] = "aeiou";
  char str1_exp[] = "AEIOU";

  printf(" ... testing \"%s\" ... \n", str1);
  TEST_ASSERT_EQUAL_INT(5, upcaseVowels(str1));
  TEST_ASSERT_EQUAL_STRING(str1_exp, str1);

  char str2[] = "Thr n vwls hr.";

  printf(" ... testing \"%s\" ... \n", str2);
  TEST_ASSERT_EQUAL_INT(0, upcaseVowels(str2));
  TEST_ASSERT_EQUAL_STRING(str2, str2);

  char str3[] = "Hi there you silly.";
  char str3_exp[] = "HI thErE yOU sIlly.";

  printf(" ... testing \"%s\" ... \n", str3);
  TEST_ASSERT_EQUAL_INT(6, upcaseVowels(str3));
  TEST_ASSERT_EQUAL_STRING(str3_exp, str3);
}


int
main(int argc, char** argv)
{
  UnityBegin("HW4 test.c");

  RUN_TEST(test_length);
  RUN_TEST(test_lengthNoArrays);
  RUN_TEST(test_bitDropper);
  RUN_TEST(test_upcaseVowels);

  UnityEnd();
}

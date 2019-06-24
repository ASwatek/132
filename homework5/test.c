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
char* skipper(char* input);
int string2num(char* input);

// functions in asm files
int add(int a, int b);
int sumArray(int* arr, int size);
int greater(int x, int y);


void setUp(void) { }
void tearDown(void) { }

void
test_skipper(void)
{
  char* rv;

  rv = skipper("AbAbAb");
  TEST_ASSERT_NOT_NULL(rv);
  if (rv != NULL) {
    TEST_ASSERT_EQUAL_STRING_LEN("AAA", rv, 3);
    TEST_ASSERT_EQUAL_MESSAGE('\0', rv[3], "Output must be null-terminated.");
    //todo test that rv is the right allocation size
    free(rv);
  }

  rv = skipper("AbAbA");
  TEST_ASSERT_NOT_NULL(rv);
  if (rv != NULL) {
    TEST_ASSERT_EQUAL_STRING_LEN("AAA", rv, 3);
    TEST_ASSERT_EQUAL_MESSAGE('\0', rv[3], "Output must be null-terminated.");
    //todo test that rv is the right allocation size
    free(rv);
  }

  rv = skipper("TxhWi4se bi s) Qf u n#zxi*ewso!p");
  TEST_ASSERT_NOT_NULL(rv);
  if (rv != NULL) {
    TEST_ASSERT_EQUAL_STRING_LEN("This is funzies!", rv, 16);
    TEST_ASSERT_EQUAL_MESSAGE('\0', rv[16], "Output must be null-terminated.");
    //todo test that rv is the right allocation size
    free(rv);
  }

}

void
test_string2num(void)
{
  TEST_ASSERT_EQUAL(10, string2num("10"));
  TEST_ASSERT_EQUAL(65535, string2num("65535"));
  TEST_ASSERT_EQUAL(0, string2num("0"));

}

void
test_add(void)
{
  TEST_ASSERT_EQUAL(2, add(1,1));
  TEST_ASSERT_EQUAL(0, add(-1,1));
}

void
test_greater(void)
{
  TEST_ASSERT_EQUAL(2, greater(2, 0));
  TEST_ASSERT_EQUAL(2, greater(0, 2));
  TEST_ASSERT_EQUAL(-3, greater(-3, -4));
  TEST_ASSERT_EQUAL(1, greater(1, 1));
}

void
test_sumArray(void)
{
  int a1[4];
  a1[0] = 1;
  a1[1] = 20;
  a1[2] = 343;
  a1[3] = 47;

  TEST_ASSERT_EQUAL( 1, sumArray(a1, 1));
  TEST_ASSERT_EQUAL(411, sumArray(a1, 4));
}


void
main(int argc, char** argv)
{
  UnityBegin("HW5 test.c");

  RUN_TEST(test_skipper);
  RUN_TEST(test_string2num);

  RUN_TEST(test_add);
  RUN_TEST(test_greater);
  RUN_TEST(test_sumArray);

  UnityEnd();
}

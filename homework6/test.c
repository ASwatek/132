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
int startsWith(char* input, char* targets);
int startsWithVowel(char* input);
char* pigify(char* input);

void setUp(void) { }
void tearDown(void) { }

void
test_startsWith(void)
{
  TEST_ASSERT_EQUAL(0, startsWith("foo", "x"));
  TEST_ASSERT_EQUAL(0, startsWith("foo", ""));
  TEST_ASSERT_EQUAL(1, startsWith("foo", "f"));
  TEST_ASSERT_EQUAL(1, startsWith("foo", "xf"));
  TEST_ASSERT_EQUAL(0, startsWith("foo", "dogs"));
  TEST_ASSERT_EQUAL(1, startsWith("foo", "frogs"));
}

void
test_startsWithVowel(void)
{
  TEST_ASSERT_EQUAL(0, startsWithVowel("foo"));
  TEST_ASSERT_EQUAL(1, startsWithVowel("ate"));
  TEST_ASSERT_EQUAL(0, startsWithVowel(""));
  TEST_ASSERT_EQUAL(0, startsWithVowel("bars"));
  TEST_ASSERT_EQUAL(0, startsWithVowel("coffee"));
  TEST_ASSERT_EQUAL(0, startsWithVowel("you"));
  TEST_ASSERT_EQUAL(1, startsWithVowel("EXCITED!"));
}

void
test_pigify(void)
{
  char* rv;

  rv = pigify("pig");
  TEST_ASSERT_NOT_NULL(rv);
  if (rv != NULL) {
    TEST_ASSERT_EQUAL_STRING_LEN("igpay", rv, 5);
    TEST_ASSERT_EQUAL_MESSAGE('\0', rv[6], "Output must be null-terminated.");
    //todo test that rv is the right allocation size
    free(rv);
  }

  rv = pigify("is");
  TEST_ASSERT_NOT_NULL(rv);
  if (rv != NULL) {
    TEST_ASSERT_EQUAL_STRING_LEN("isyay", rv, 5);
    TEST_ASSERT_EQUAL_MESSAGE('\0', rv[6], "Output must be null-terminated.");
    //todo test that rv is the right allocation size
    free(rv);
  }

  rv = pigify("sausage");
  TEST_ASSERT_NOT_NULL(rv);
  if (rv != NULL) {
    TEST_ASSERT_EQUAL_STRING_LEN("ausagesay", rv, 9);
    TEST_ASSERT_EQUAL_MESSAGE('\0', rv[10], "Output must be null-terminated.");
    //todo test that rv is the right allocation size
    free(rv);
  }

}


void
main(int argc, char** argv)
{
  UnityBegin("HW6 test.c");

  RUN_TEST(test_startsWith);
  RUN_TEST(test_startsWithVowel);
  RUN_TEST(test_pigify);

  UnityEnd();
}

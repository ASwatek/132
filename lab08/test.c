/*
 * CSSE 132
 * Rose-Hulman Institute of Technology
 * Computer Science and Software Engineering
 *
 * test.c - Source file with tests for the lab.
 *          This is a file you need to hand in!
 *          
 *          This file contains the tests you run to verify
 *          the code for lab 6.
 *
 * This file contains code used by labs in the CSSE 132 class.
 * When you edit this file for class, be sure to put your name(s) here!
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
#include "data.h"

// change this to zero if you want to allow fgets to work when the
// G_FGETS_INPUT buffer is empty.
#define FAIL_ON_EMPTY_FGETS_BUFFER 1

char* G_PRINTF_OUTPUT;
char* G_FGETS_INPUT;

// for forwarding non-wrapped i/o calls.
extern char* __real_fgets  (char* s, int size, FILE* stream);
extern int   __real_printf (const char* fmt, ...);
extern int   __real_fprintf (FILE* stream, const char* fmt, ...);

/**
 * Free and nullify any fgets buffer to start over.  This is used for the
 * intercepted calls to fgets.
 */
void
resetFgetsBuffer()
{
  if (G_FGETS_INPUT) free(G_FGETS_INPUT);
  G_FGETS_INPUT = NULL;
}

/**
 * Free and nullify any printf buffer to start over.  This is used for the
 * intercepted calls to printf.
 */
void
resetPrintfBuffer()
{
  //__real_printf("Freeing %x\n", G_PRINTF_OUTPUT);
  if (G_PRINTF_OUTPUT) free(G_PRINTF_OUTPUT);
  G_PRINTF_OUTPUT = NULL;
}


/**
 * wrapper for capturing output from fprintf.
 */
int
__wrap_fprintf(FILE* stream, const char* fmt, ...)
{
  int rv;
  va_list args;
  va_start(args, fmt);

  if (stream != stdout) {
    return vfprintf(stream, fmt, args); 
  }

  // allocate some space.
  char buf[1024];
  char* tmp = NULL;
  int prevLen = 0;
  int newLen = prevLen;
  memset(buf, 0, 1024 * sizeof(char));
  rv = vsprintf(buf, fmt, args);

  // make sure the global buffer has space
  prevLen = G_PRINTF_OUTPUT ? strlen(G_PRINTF_OUTPUT) : 0;
  newLen = prevLen + strlen(buf);

  // the +1 is for a null terminator
  tmp = realloc(G_PRINTF_OUTPUT, (prevLen + newLen + 1) * sizeof(char));
  if (tmp == NULL)
    return 0;
  G_PRINTF_OUTPUT = tmp;

  // append the new string
  memcpy(G_PRINTF_OUTPUT + prevLen, buf, newLen + 1);

  va_end(args);
  return rv;
}

/**
 * Queue up a line to feed fgets.  Only accepts one line at a time.
 */
void
preloadFgets(const char* line)
{
  int len;
  len = strlen(line); 

  resetFgetsBuffer();

  // Allocate extra chars for '\n' and null termination
  G_FGETS_INPUT = malloc(len * sizeof(char) + 2);
  memcpy(G_FGETS_INPUT, line, len);
  G_FGETS_INPUT[len] = '\n';
  G_FGETS_INPUT[len+1] = '\0';
}

/**
 * wrapper for simulating input to fgets.
 */
char*
__wrap_fgets(char* s, int size, FILE* stream)
{
  int len = 0;

  if (!G_FGETS_INPUT) {
    if (FAIL_ON_EMPTY_FGETS_BUFFER) {
      TEST_FAIL_MESSAGE("WARNING: empty input provided for fgets. You should "
                        "use preloadFgets() before calling fgets");
      return 0;
    }
    return  __real_fgets(s, size, stream);
  }

  len = strlen(G_FGETS_INPUT);
  if (len < 1) {
    return NULL;
  }

  // make sure there's still room for the null terminator.
  // We'll copy a subset of the string if "size" is too small.
  // len is now the maximum string length (max is size - 1)
  len  = (size - 1 < len) ? size - 1 : len;

  memcpy(s, G_FGETS_INPUT, len);
  s[len] = '\0';

  return s;
}



void setUp(void) { }
void tearDown(void) { }

void
test_do_list_database(void)
{
  int i;
  // set up a database
  struct db_entry** db = malloc(DB_MAX_SIZE * sizeof(struct db_entry*));
  memset(db, 0, DB_MAX_SIZE * sizeof(struct db_entry*));
  TEST_ASSERT_EQUAL_INT(0, db_count_entries(db));

  resetPrintfBuffer();
  do_list_database(db);
  // should be nothing
  TEST_ASSERT_NULL(G_PRINTF_OUTPUT);

  // (A, B, C)
  do_add_entry(db, "A", "A1");
  do_add_entry(db, "B", "B1");
  do_add_entry(db, "C", "C1");

  resetPrintfBuffer();
  do_list_database(db);
  // Expected:
  // A => A1\n
  // B => B1\n
  // C => C1\n
  TEST_ASSERT_EQUAL_STRING_LEN("A => A1\n", G_PRINTF_OUTPUT, 8);
  TEST_ASSERT_EQUAL_STRING_LEN("B => B1\n", G_PRINTF_OUTPUT + 8, 8);
  TEST_ASSERT_EQUAL_STRING_LEN("C => C1\n", G_PRINTF_OUTPUT + 16, 8);

  db_remove(db, 1);

  resetPrintfBuffer();
  do_list_database(db);
  // Expected:
  // A => A1\n
  // C => C1\n
  TEST_ASSERT_EQUAL_STRING_LEN("A => A1\n", G_PRINTF_OUTPUT, 8);
  TEST_ASSERT_EQUAL_STRING_LEN("C => C1\n", G_PRINTF_OUTPUT + 8, 8);

  do_add_entry(db, "D", "D1");

  resetPrintfBuffer();
  do_list_database(db);
  // Expected:
  // A => A1\n
  // C => C1\n
  // D => D1\n
  TEST_ASSERT_EQUAL_STRING_LEN("A => A1\n", G_PRINTF_OUTPUT, 8);
  TEST_ASSERT_EQUAL_STRING_LEN("C => C1\n", G_PRINTF_OUTPUT + 8, 8);
  TEST_ASSERT_EQUAL_STRING_LEN("D => D1\n", G_PRINTF_OUTPUT + 16, 8);

  // clean up the database
  for(i = 3; i > 0; i--) { db_remove(db, 0); }
  free(db);
}

void
test_do_find_all_matches(void)
{
  int i;
  // set up a database
  struct db_entry** db = malloc(DB_MAX_SIZE * sizeof(struct db_entry*));
  memset(db, 0, DB_MAX_SIZE * sizeof(struct db_entry*));

  do_add_entry(db, "Alice", "A1");
  do_add_entry(db, "Bob", "B1");
  do_add_entry(db, "Cindy", "C1");
  do_add_entry(db, "Bonnie", "D1");

  resetPrintfBuffer();

  do_find_all_matches(db, "B");
  TEST_ASSERT_EQUAL_STRING_LEN("Bob => B1\n", G_PRINTF_OUTPUT, 10);
  TEST_ASSERT_EQUAL_STRING_LEN("Bonnie => D1\n", G_PRINTF_OUTPUT + 10, 12);

  // clean up the database
  while(db_count_entries(db) > 0) { db_remove(db, 0); }
  free(db);
}

void
test_getALine(void)
{
  int rv = 0;
  char buf[512];

  const char* S_TEST1 = "this is a line";
  preloadFgets(S_TEST1);
  rv = getALine(buf, 512, stdin);
  TEST_ASSERT_EQUAL(strlen(S_TEST1), rv);
  TEST_ASSERT_EQUAL_STRING(S_TEST1, buf);

  const char* S_TEST2 = "this is a line, too";
  preloadFgets(S_TEST2);
  rv = getALine(buf, 512, stdin);
  TEST_ASSERT_NOT_EQUAL(0, rv);
  TEST_ASSERT_EQUAL_STRING(S_TEST2, buf);

  const char* S_TEST3= "oh look, it works!";
  preloadFgets(S_TEST3);
  rv = getALine(buf, 512, stdin);
  TEST_ASSERT_NOT_EQUAL(0, rv);
  TEST_ASSERT_EQUAL_STRING(S_TEST3, buf);
}

void
main(int argc, char** argv)
{
  UnityBegin("test.c");

  RUN_TEST(test_do_list_database);
  RUN_TEST(test_getALine);
  RUN_TEST(test_do_find_all_matches);

  resetFgetsBuffer();
  resetPrintfBuffer();
  UnityEnd();
}

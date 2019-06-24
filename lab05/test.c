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

void test_dbe_allocAndFree(void)
{
  struct db_entry* dbe;

  dbe = dbe_alloc("foo", "this is a long value string");

  TEST_ASSERT_NOT_NULL_MESSAGE(dbe,
    "dbe_alloc should not return null");

  TEST_ASSERT_NOT_NULL_MESSAGE(dbe->name,
    "db_entry.name should not be null after allocation");
    
  TEST_ASSERT_NOT_NULL_MESSAGE(dbe->value,
    "db_entry.value should not be null after allocation");

  TEST_ASSERT_EQUAL_STRING_MESSAGE(dbe->name, "foo",
    "db_entry.name has wrong value after allocation");

  TEST_ASSERT_EQUAL_STRING_MESSAGE(dbe->value, "this is a long value string",
    "db_entry.value has wrong value after allocation");

  dbe_free(dbe);
  TEST_ASSERT_NOT_NULL_MESSAGE(dbe,
    "dbe_free should not change the pointer");
}


void
test_do_add_entry(void)
{
  int i;
  struct db_entry** db = malloc(DB_MAX_SIZE * sizeof(struct db_entry*));
  //TEST_ASSERT_NOT_NULL_MESSAGE(db, "malloc failed to make us a database");

  memset(db, 0, DB_MAX_SIZE * sizeof(struct db_entry*));
  // for (i=0; i<DB_MAX_SIZE; i++) {
  //  TEST_ASSERT_NULL_MESSAGE(db[i], "memset should zero out the database");
  // }
  
  do_add_entry(db, "a", "b");
  TEST_ASSERT_NOT_NULL_MESSAGE(db[0],
    "do_add_entry should write at the beginning of the array");
  TEST_ASSERT_EQUAL_STRING_MESSAGE(db[0]->name, "a",
    "the database entry has wrong name after do_add_entry");
  TEST_ASSERT_EQUAL_STRING_MESSAGE(db[0]->value, "b",
    "the database entry has wrong value after do_add_entry");
  TEST_ASSERT_NULL_MESSAGE(db[1],
    "do_add_entry should not write a second entry");

  do_add_entry(db, "c", "d");
  TEST_ASSERT_EQUAL_STRING_MESSAGE(db[0]->name, "a",
    "should not modify the previous entry's name");
  TEST_ASSERT_EQUAL_STRING_MESSAGE(db[0]->value, "b",
    "should not modify the previous entry's value");
  TEST_ASSERT_NOT_NULL_MESSAGE(db[1],
    "do_add_entry should write at the first available slot of the array");
  TEST_ASSERT_EQUAL_STRING_MESSAGE(db[1]->name, "c",
    "the database entry has wrong name after do_add_entry");
  TEST_ASSERT_EQUAL_STRING_MESSAGE(db[1]->value, "d",
    "the database entry has wrong value after do_add_entry");
  TEST_ASSERT_NULL_MESSAGE(db[2],
    "do_add_entry should not write a second entry");

  dbe_free(db[1]);
  dbe_free(db[0]);
  free(db);
}


// DEPENDS ON: dbe_free, do_add_entry
void
test_db_count_entries(void)
{
  int i = 0;

  // set up a database
  struct db_entry** db = malloc(DB_MAX_SIZE * sizeof(struct db_entry*));
  memset(db, 0, DB_MAX_SIZE * sizeof(struct db_entry*));
  TEST_ASSERT_EQUAL_INT(0, db_count_entries(db));

  // Add three entries (appends them to the end)
  // (A, B, C)
  do_add_entry(db, "A", "A1");
  TEST_ASSERT_NOT_NULL(db[0]);
  do_add_entry(db, "B", "B1");
  TEST_ASSERT_NOT_NULL(db[1]);
  do_add_entry(db, "C", "C1");
  TEST_ASSERT_NOT_NULL(db[2]);
  TEST_ASSERT_EQUAL_INT(3, db_count_entries(db));

  // clean up the database
  for(i = 3; i > 0; i--) {
    TEST_ASSERT_EQUAL_INT(i, db_count_entries(db));
    //db_remove(db, 0);
    dbe_free(db[i-1]);
    db[i-1] = NULL;
  }
  free(db);
}


// DEPENDS ON: do_add_entry, db_count_entries
void
test_db_remove(void)
{
  int i;

  // set up a database
  struct db_entry** db = malloc(DB_MAX_SIZE * sizeof(struct db_entry*));
  memset(db, 0, DB_MAX_SIZE * sizeof(struct db_entry*));
  TEST_ASSERT_EQUAL_INT(0, db_count_entries(db));

  // this should do nothing, not crash or anything.
  db_remove(db,3);
  TEST_ASSERT_NULL_MESSAGE(db[3], "db_remove shouldn't do anything to a null entry");
  
  // Add three entries (appends them to the end)
  // (A, B, C)
  do_add_entry(db, "A", "A1");
  TEST_ASSERT_NOT_NULL(db[0]);
  do_add_entry(db, "B", "B1");
  TEST_ASSERT_NOT_NULL(db[1]);
  do_add_entry(db, "C", "C1");
  TEST_ASSERT_NOT_NULL(db[2]);
  TEST_ASSERT_EQUAL_INT(3, db_count_entries(db));

  // remove the one in the middle (A, B, C) => (A, C)
  db_remove(db, 1);
  TEST_ASSERT_EQUAL_INT_MESSAGE(2, db_count_entries(db),
    "After removing one db_entry, the database count should be 2");
  TEST_ASSERT_NOT_NULL_MESSAGE(db[1],
    "db_remove should shift the third item up after removing the second one");
  TEST_ASSERT_NULL_MESSAGE(db[2],
    "db_remove should shift the third item up after removing the second one");
  TEST_ASSERT_EQUAL_STRING("A", db[0]->name);
  TEST_ASSERT_EQUAL_STRING("C", db[1]->name);

  // this removes the next-to-last entry (A, C) => (C)
  db_remove(db, 0);
  TEST_ASSERT_NOT_NULL(db[0]);
  TEST_ASSERT_NULL(db[1]);
  TEST_ASSERT_EQUAL_STRING("C", db[0]->name);

  // this removes the last entry (C) => ()
  db_remove(db, 0);
  TEST_ASSERT_NULL(db[0]);

  // clean up the database
  free(db);
}


// DEPENDS ON: dbe_free, do_add_entry, db_count_entries, db_remove
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

// DEPENDS ON: db_count_entries, do_add_entry, db_remove
void
test_db_find_one(void)
{
  // set up a database
  struct db_entry** db = malloc(DB_MAX_SIZE * sizeof(struct db_entry*));
  memset(db, 0, DB_MAX_SIZE * sizeof(struct db_entry*));
  TEST_ASSERT_EQUAL_INT(0, db_count_entries(db));

  // Add three entries (appends them to the end)
  do_add_entry(db, "Ant", "A1");
  do_add_entry(db, "Bird", "B1");
  do_add_entry(db, "Cat", "C1");
  TEST_ASSERT_EQUAL_INT(3, db_count_entries(db));

  TEST_ASSERT_EQUAL_INT_MESSAGE(0, db_find_one(db, "Ant", 0),
    "Should find Ant at index 0");
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, db_find_one(db, "Bird", 0),
    "Should find Bird at index 1");
  TEST_ASSERT_EQUAL_INT_MESSAGE(2, db_find_one(db, "Cat", 0),
    "Should find Cat at index 2");
  TEST_ASSERT_EQUAL_INT_MESSAGE(-1, db_find_one(db, "Dog", 0),
    "Should not find Dog");
  TEST_ASSERT_EQUAL_INT_MESSAGE(-1, db_find_one(db, "Ant", 1),
    "Should not find Ant after index 1");
  TEST_ASSERT_EQUAL_INT_MESSAGE(-1, db_find_one(db, "Ant", 3),
    "Should not find Ant after index 3");

  // clean up the database
  while(db_count_entries(db) > 0) { db_remove(db, 0); }
  free(db);
}


// DEPENDS ON: db_count_entries, do_add_entry, db_remove
void
test_do_remove_first_match_exact(void)
{
  int i = -1;
  // set up a database
  struct db_entry** db = malloc(DB_MAX_SIZE * sizeof(struct db_entry*));
  memset(db, 0, DB_MAX_SIZE * sizeof(struct db_entry*));
  TEST_ASSERT_EQUAL_INT(0, db_count_entries(db));

  // Add three entries (appends them to the end)
  do_add_entry(db, "Ant", "A1");
  do_add_entry(db, "Bird", "B1");
  do_add_entry(db, "Cat", "C1");
  do_add_entry(db, "Dog", "D1");
  TEST_ASSERT_EQUAL_INT(4, db_count_entries(db));

  // testing an exact match
  i = do_remove_first_match(db, "Cat");
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, i,
    "do_remove_first_match should find Cat in the database and return 1");
  TEST_ASSERT_EQUAL_STRING("Ant", db[0]->name);
  TEST_ASSERT_NOT_NULL(db[1]);  //third element moves down to second
  TEST_ASSERT_EQUAL_STRING("Bird", db[1]->name);
  TEST_ASSERT_NOT_NULL(db[2]);  //fourth element moves down to third 
  TEST_ASSERT_EQUAL_STRING("Dog", db[2]->name);
  TEST_ASSERT_NULL(db[3]);      //fourth element should be empty now

  // clean up the database
  while(db_count_entries(db) > 0) { db_remove(db, 0); }
  free(db);
}

// DEPENDS ON: db_count_entries, do_add_entry, db_remove
void
test_do_remove_first_match_partial(void)
{
  int i = -1;
  // set up a database
  struct db_entry** db = malloc(DB_MAX_SIZE * sizeof(struct db_entry*));
  memset(db, 0, DB_MAX_SIZE * sizeof(struct db_entry*));
  TEST_ASSERT_EQUAL_INT(0, db_count_entries(db));

  // Add three entries (appends them to the end)
  do_add_entry(db, "Ant", "A1");
  do_add_entry(db, "Bird", "B1");
  do_add_entry(db, "Cat", "C1");
  TEST_ASSERT_EQUAL_INT(3, db_count_entries(db));

  i = do_remove_first_match(db, "Bi");
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, i,
    "do_remove_first_match should find the substring Bi in Bird");
  TEST_ASSERT_EQUAL_STRING("Ant", db[0]->name);
  TEST_ASSERT_NOT_NULL(db[1]);  //third element moves down to second
  TEST_ASSERT_EQUAL_STRING("Cat", db[1]->name);
  TEST_ASSERT_NULL(db[2]);      //third element should be empty now

  // clean up the database
  while(db_count_entries(db) > 0) { db_remove(db, 0); }
  free(db);
}


void
main(int argc, char** argv)
{
  UnityBegin("test.c");

  RUN_TEST(test_dbe_allocAndFree);
  RUN_TEST(test_do_add_entry);
  RUN_TEST(test_db_count_entries);
  RUN_TEST(test_db_remove);
  RUN_TEST(test_do_list_database);
  RUN_TEST(test_db_find_one);
  RUN_TEST(test_do_remove_first_match_exact);
  RUN_TEST(test_do_remove_first_match_partial);

  resetFgetsBuffer();
  resetPrintfBuffer();
  UnityEnd();
}

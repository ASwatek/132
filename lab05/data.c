/*
 * CSSE 132
 * Rose-Hulman Institute of Technology
 * Computer Science and Software Engineering
 *
 * data.c - Source file with your solutions to the lab.  The
 *          main functionality for this lab should be implemented
 *          here.  This file is used for running the lab's program
 *          and also for running the unit tests.
 *
 *          This is a file you need to hand in!
 *
 * This file contains code used by labs in the CSSE 132 class.
 * When you edit this file for class, be sure to put your name(s) here!
 *
 * Edited by
 * NAMES: Austin Swatek and Steven Jung
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"

// This is the size of our "database" array: it has this many slots and can't
// grow any larger.
const unsigned int DB_MAX_SIZE = 128;


/**
 * This formats and prints out a db_entry nicely.
 * We're providing this for you so the output is uniform.  You'll modify this
 * in the next lab!
 *
 * @param entry: the db_entry struct to print
 */
void
dbe_print(struct db_entry* entry)
{
  fprintf(stdout, "%s => %s\n", entry->name, entry->value);
}


/**
 * Allocates space for a db_entry's members and copies the strings into the
 * newly allocated memory.  If you need space for a string, this is where you
 * allocate it.  This function "constructs" the structure and fills it up.
 *
 * dbe_alloc("me", "val") must allocate contiguous space for two string
 * pointers.  Once that's allocated, it needs to create the space for each
 * string and point the structure's values to the strings.  This example
 * creates a structure in memory that looks like this:
 *
 * db_entry* -> {
 *                char* name: -------> ['m', 'e', '\0']
 *                char* value: ------> ['v', 'a', 'l', '\0']
 *              }
 * The structure itself only needs space for the two pointers, but to figure
 * out how to initialize the pointers, you need to make space for the strings
 * first.
 *
 * @return: a pointer to where the allocated
 */
struct db_entry*
dbe_alloc(const char* name, const char* value)
{
  // 
  // Allocate space for the structure.
  // Allocate space for the two strings and copy them from the arguments.
  // Check the man page for memcpy to figure out how to copy one array to
  // another.
  // Don't forget to:
  //   - null-terminate the strings
  //   - connect the structure to the newly allocated strings!
  struct db_entry* ret;
// ret = malloc(sizeof(struct db_entry) + sizeof(name) + sizeof(value));
  ret = malloc(sizeof(struct db_entry));
//  char* nameP = malloc(sizeof(name)+1);
//  char* valueP = malloc(sizeof(value)+1);
//  char* nameP = malloc(strlen(name)+1);
//  char* valueP = malloc(strlen(value)+1);

//  ret->name=nameP;
  ret->name=malloc(strlen(name)+1);
  memcpy(ret->name, name, strlen(name)+1);
//  ret->value=valueP;
  ret->value=malloc(strlen(value)+1);
  memcpy(ret->value, value, strlen(value)+1);
  return ret;
}


/**
 * Releases the memory held by the a db_entry struct.
 * Anything that needed to be malloc()'ed when the structure was created must
 * be free()'ed here.
 *
 * @param entry: a pointer to the structure to free.
 */
void
dbe_free(struct db_entry* entry)
{
  //
  // free space allocated for the structure's members and for the structure
  // itself.
  if(entry!=0){
   free(entry->name);
   free(entry->value);
   free(entry);
  }
}


/**
 * This allocates some memory for a new entry and adds a pointer to it to the
 * end of the database.
 *
 * The database "db" is the address of a series of pointers to db_entry
 * structs that you will create with dbe_alloc().  (It is an array of pointers).
 *
 * After the last entry in the database, there is a null pointer (zero).
 *
 * db -> [
 *          -----> db_entry struct [ name, value ]
 *          -----> db_entry struct [ name, value ]
 *          -----> db_entry struct [ name, value ]
 *          -----> db_entry struct [ name, value ]
 *          0
 *       ]
 *
 * db_entry -> {
 *               char* name: -------> ['m', 'e', '\0']
 *               char* value: ------> ['v', 'a', 'l', '\0']
 *             }
 *
 * @param db: a pointer to the database (array)
 * @param name: a string for the name of the entry
 * @param value: a string for the entry's contents */
void
do_add_entry(struct db_entry** db, const char* name, const char* value)
{
  // :
  // Use your dbe_alloc function to make a new db_entry instance to put in the
  // database.  Add it to the end of the database.
  // You can assume there are no empty spots between entries.
  //
  // For example, a database that has three items:
  //   [ X, Y, Z, 0, 0, 0, 0 ... 0 ]
  // After adding A, it will look like this:
  //   [ X, Y, Z, A, 0, 0, 0 ... 0 ]

//  int i=0;
//  while(db[i]!="0"){
//   i++;
//  }

//  struct db_entry myGuy;
//  myGuy* = &dbe_alloc(name, value);
//  db[i]=myGuy;
//  free(*myGuy);

//loop to empty, create myGuy, put myGuy in database, free myGuy

  //loops to empty position
  int i=0;
  while(db[i]!=0){
   printf("s");
   i++;
  }

  //creates myGuy entry
  struct db_entry* myGuy;
  myGuy=dbe_alloc(name, value);

  //make myGuy
  db[i]=myGuy;
  //dbe_free(myGuy);
}


/**
 * Returns the number of non-null entries in the database.
 * For example, given this database:
 *   db = [("A" => "aval"), ("C" => "cval"), 0, 0]
 * db_count_entries(db) returns 2.
 *
 * @param database: a pointer to the database structure
 * @return: the entry count
 */
int
db_count_entries(struct db_entry** database)
{
  // :
  // count the number of non-NULL entries in the database.
  // You can assume there won't be NULL entries betwee non-NULL entries.
  // Hint: the database will never be bigger than the constant value DB_MAX_SIZE
  //       (this is a global constant at the top of this file).
  int count=0;
  int i=0;
  while(database[i]!=0){
   count++;
   i++;
 }

  return count;
}


/**
 * Removes the entry at index "index" and shifts the trailing items down.
 * For example, if a database looks like this:
 *   db = [("A" => "aval"), ("B" => "bval"), ("C" => "cval"), 0]
 * when db_remove(db, 1) completes, db will look like this:
 *   db = [("A" => "aval"), ("C" => "cval"), 0, 0]
 *
 * @param database: a pointer to the database structure
 * @param index: the index of the item to remove.
 */
void
db_remove(struct db_entry** database, int index)
{
  // :
  // remove the item at the given index.
  // Don't forget to "free" it, and set the appropriate index to NULL.
  // Once it's destroyed, shift all the remaining items down.
  // For example, given this database:
  //   [ X, Y, Z, 0 ... 0 ]
  // After removing Y, it will look like this:
  //   [ X, Z, 0, 0 ... 0 ]
//iterate up to index, remove index, check to see if next exists: if{replace with next}, else{replace with 0}


  dbe_free(database[index]);
/**
  int i=index;
  while(database[i+1]!=0){
   database[i]=database[i+1];
   i++;
  }
*/
for(index;database[index]!=0;index++){
  database[index]=database[index+1];
}

}


/**
 * Prints out all the entries in the database using dbe_print().
 *
 * @param db: a pointer to the database structure
 */
void
do_list_database(struct db_entry** db)
{
  // :
  // List all the entries in the database.  You'll need a loop and use the
  // dbe_print() function.
  // Don't list the null entries (entries that haven't been added yet).
  int i=0;
  while(db[i]!=0){
   dbe_print(db[i]);
   i++;
  }
}


/**
 * This looks for "target" in the database and returns the index if found.
 *
 * For example, db_find_one(db, "bob", 0) will search db for any entries with
 * the name starting with "bob", beginning with the first (0th) index.
 *
 * @param database: a pointer to the database structure
 * @param target: a string to look for in the database's names
 * @param initialIndex: a starting index in case you want to search part
 *           of the database
 * @returns the index of the first matching entry or -1 if it wasn't found.
 */
int
db_find_one(struct db_entry** database,
            const char* target,
            int initialIndex)
{
  // TODO:
  // Search through all the entries in the database and return the index of
  // the first item that matches.  If nothing is found, return -1.
  //
  // In order to check for a match, you'll use strncmp to compare the first
  // "N" characters in target to stringToSearch:
  //
  //     strncmp(target, stringToSearch, count)
  //
  // Note: to figure out the count, you can use a function to determine the
  // length of "target".  See the section 3 manpage for "string" for some
  // possibilities.

  int targetLength=0;
  int i=0;
  while(target[i]!='\0'){
   targetLength++;
   i++;
  }
  i=initialIndex;
  while(database[i]!=0){
   if(strncmp(target, database[i]->name, targetLength)==0){
    return i;
   }
   i++;
  }
  return -1;
}


/**
 * Complete this function:
 * When do_remove_first_match is called, remove the first entry in the database
 * with a name that starts with the value of target.  If no entries start with
 * the string contained in the target parameter, nothing is removed.
 *
 * @param db: a pointer to the database structure
 * @param target: a name of an entry to remove
 * @return: 1 if something was removed, 0 if not.
 */
int
do_remove_first_match(struct db_entry** db, const char* target)
{
  // :
  // Find the first thing that matches target, and remove it.
  // Be sure to return 0 if nothing is found!
  int targetLength=0;
  int i=0;
  int happened=0; //i didnt know how to make a boolean, so i used this integer
  while(target[i]!='\0'){
   targetLength++;
   i++;
  }
  i=0;
  while(db[i]!=0){
   if(strncmp(target, db[i]->name, targetLength)==0){
    happened=1;  //once it has been found, return the data
    break;
   }else{
    i++;
   }
  }

  if(happened==1){
   db_remove(db, i);
   return 1;
  }
  return 0;
}


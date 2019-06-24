/*
 * CSSE 132
 * Rose-Hulman Institute of Technology
 * Computer Science and Software Engineering
 *
 * lab5.c - Source file with your solutions to the lab.
 *          This is a file you need to hand in!
 *
 *          This file represents the "program" you run to execute
 *          the code for lab 5.
 *
 * This file contains code used by labs in the CSSE 132 class.
 * When you edit this file for class, be sure to put your name(s) here!
 *
 * Edited by
 * NAMES:
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"

int
main(int argc, char** argv)
{
  /*
    This database is an array of pointers to structs.
    Visually, the format looks like this:
    database =
    [
      {name: "name1", value:"value1" },
      {name: "name2", value:"value2" },
      ...
    ]

    In reality, the array is a bunch of addresses, and the addresses are the
    location where instances of the struct are stored.
   */

  // make a big, empty database in the heap
  // this is a _pointer_ to an _array_ of db_entry structs.
  struct db_entry** db = malloc(DB_MAX_SIZE * sizeof(struct db_entry*));

  // zero out the memory, just in case.
  memset(db, 0, DB_MAX_SIZE * sizeof(struct db_entry*));

  // The following code adds some data and plays with it.
  // TODO: Uncomment this when you're ready to see if it works.
  /*
  do_add_entry(db, "Adele", "A1 Data");
  do_add_entry(db, "Bubba", "B1 Datum");
  do_add_entry(db, "Chuck", "C1 Datas");

  // [ ("Adele" => "A1 Data"),
  //   ("Bubba" => "B1 Datum"),
  //   ("Chuck" => "C1 Datas") ]

  do_list_database(db);
  printf("\n");

  do_remove_first_match(db, "Bubba");

  // [ ("Adele" => "A1 Data"),
  //   ("Chuck" => "C1 Datas") ]

  do_list_database(db);
  printf("\n");

  do_add_entry(db, "Bubba's brother", "B1 Datum");

  // [ ("Adele" => "A1 Data"),
  //   ("Chuck" => "C1 Datas"),
  //   ("Bubba's Brother" => "B1 Datum") ]

  do_list_database(db);
  printf("\n");

  do_remove_first_match(db, "Chu");

  // [ ("Adele" => "A1 Data"),
  //   ("Bubba's Brother" => "B1 Datum") ]

  do_list_database(db);
  printf("\n");

  // remove the last two
  db_remove(db, 0);
  db_remove(db, 0);

  // [ ]

  */

  // return the used memory
  free(db);

  return 0;
}

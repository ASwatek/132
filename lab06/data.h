#ifndef __data_h__
#define __data_h__

/*
 * data.h
 *
 * CSSE 132
 * Rose-Hulman Institute of Technology
 * Computer Science and Software Engineering
 *
 * This file contains declarations for functions and constants used by this
 * project.  For implementations, please see data.c
 */

// maximum entries for the DB
extern const unsigned int DB_MAX_SIZE;// = 128;

// The type of thing we're storing in the database
struct db_entry {
  char* name;
  char* value;
};

// Some function declarations from Lab 5
//void   dbe_print(struct db_entry* entry);
void dbe_print(struct db_entry* entry, FILE* file);
struct db_entry* dbe_alloc(const char* name, const char* value);
void   dbe_free(struct db_entry* entry);
int    db_count_entries(struct db_entry** database);
void   db_remove(struct db_entry** database, int index);
int    db_find_one(struct db_entry** database, const char* target, int initialIndex);
void   do_add_entry(struct db_entry** db, const char* name, const char* value);
void   do_list_database(struct db_entry** db);
int    do_remove_first_match(struct db_entry** db, const char* target);

// added for Lab 6
int    getALine(char* dest, int maxlen, FILE* fd);
void   do_find_all_matches(struct db_entry** db, const char* target);
int    do_import_db(struct db_entry** db, const char* filename);
void   do_export_db(struct db_entry** db, const char* filename);

#endif /*def __data_h__*/

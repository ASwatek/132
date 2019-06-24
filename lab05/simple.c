// CSSE 132 Lab 5: simple.c
// Names: Austin Swatek

#include "data.h"
#include <stdlib.h>

void main()
{
  struct db_entry stack;
  stack.name="jeff";
  stack.value="true";
  dbe_print(&stack);

  //
  struct db_entry* heap;
  heap = malloc(sizeof(struct db_entry));
  //(*heap).name="he";
  heap->name="he";
  heap->value="ap";
  dbe_print(heap);
  free(heap);

  struct db_entry* data = dbe_alloc("My Name", "My Value");
  dbe_print(data);
  dbe_free(data);
}

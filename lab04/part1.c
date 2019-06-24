/*
 * CSSE 132
 * Rose-Hulman Institute of Technology
 * Computer Science and Software Engineering
 *
 * part1.c - Source file that you'll examine for the lab.
 *
 *          This is not a file you need to hand in.
 *
 * If you edit this file for class, be sure to put your name(s) here!
 *
 * Edited by
 * NAMES:
 *
 */

#include <stdlib.h>
#include <stdio.h>


void
main(void)
{
  int array[8];
  
  /* Fill the array */
  array[0] = 19;
  array[1] = 17;
  array[2] = 13;
  array[3] = 11;
  array[4] = 7;
  array[5] = 5;
  array[6] = 3;
  array[7] = 2;
  
  /* increment them! */
  array[0] = array[0] + 2;
  array[1] = array[1] + 2;
  array[2] = array[2] + 2;
  array[3] = array[3] + 2;
  array[4] = array[4] + 2;
  array[5] = array[5] + 2;
  array[6] = array[6] + 2;
  array[7] = array[7] + 2;
}

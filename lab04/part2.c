/*
 * CSSE 132
 * Rose-Hulman Institute of Technology
 * Computer Science and Software Engineering
 *
 * part2.c - Source file that you'll break and then fix in the lab.
 *
 *          This is a file you need to hand in!  Be sure it gets checked into
 *          your repository when you've finished the lab.
 *
 * This file contains code used by labs in the CSSE 132 class.
 * When you edit this file for class, be sure to put your name(s) here!
 *
 * Edited by
 * NAMES:Austin Swatek, Steven Jung
 *
 */

#include <stdlib.h>
#include <stdio.h>

void
copyIntoBuffer(char* src, char* dest, int bufferSize)
{
  int i=0;
  while(src[i] != '\0' && i<bufferSize){
    dest[i] = src[i];
    i++;
  }
}

void
holyGrail()
{
  printf("  YAY! You DID IT!\n");
  exit(7);
}

void
doIt(char* input)
{
  char buffer[13];
  int bufferSize = 13;
  copyIntoBuffer(input, buffer, 13);
}

int
main(int argc, char** argv)
{
  if (argc < 2) return 0;

  /* Don't worry about understanding these next few lines. */
  union BA { char x[4]; void* p; } hg;
  hg.p = &holyGrail;
  printf("alternate = $'%sBBB\\x%02x\\x%02x\\x%02x'\n",
         argv[1], hg.x[0], hg.x[1], hg.x[2]);

  /* This is the part of main() that really matters: */
  doIt(argv[1]);

  /* exit normally */
  return 0;
}

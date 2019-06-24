/**
 * CSSE 132
 * Rose-Hulman Institute of Technology
 * Computer Science and Software Engineering
 *
 * problems.s: this file is where you implement your solutions
 *             for the homework assignment in ARM assembly.
 *
 * NOTE: the .global and .type lines expose the functions to your 
 * C programs (including the tests).
 *
 * This file contains code for homework in the CSSE 132 class.
 * When you edit this file for class, be sure to put your name here!
 *
 * Edited by
 * NAME: Austin Swatek
 */


/**
 * This function adds two arguments and returns the result.
 * Remember that the return value is placed in r0 before returning.
 *
 * @param r0: first arg, x
 * @param r1: second arg, y
 * @returns the sum of the two
 */
.global add
.type add, %function
add:
  /* finish this procedure here. */
  add r0, r0, r1
  /* return from this procedure (jump to lr) */
  bx lr

/**
 * This function returns the greater of two arguments.
 * 
 * You will need to do a comparison for this.  Remember that 
 * cmp sets all the CSPR registers (EQ, ZERO, etc) and the next
 * instruction can use them. (BEQ, BLE, etc).
 * HINT: to copy the value of a register into another, use the "mov"
 * instruction:
 *   mov r0, r1 ; copies value of r1 into r0
 * 
 * @param r0: first arg, x
 * @param r1: second arg, y
 * @returns the greater value of x or y
 */
.global greater
.type greater, %function
greater:
  /* finish this procedure here */
//  sub sp, sp, #12
//  str r0, [sp, #0]
//  str r1, [sp, #1]
/*  .BEGINIF:
   cmp r0, r1
   ble .ELSE
   str r0, [r0]
   b .ENDIF
  .ELSE:
   str r1, [r0]
  .ENDIF:
*/
//  str r0, [r0]
//  str r1, [r1]
//  cmp r0, r1

  sub sp, sp, #12
  str r0, [sp, #0]
  str r1, [sp, #4]
  ldr r0, [sp, #0]
  ldr r1, [sp, #4]
//  cmp r0, r1
  .BEGINIF:
   cmp r0, r1
   ble .ELSE
   mov r0, r0
   b .ENDIF
  .ELSE:
   mov r0, r1
  .ENDIF:
 /* return from this procedure (jump to lr) */
  bx lr


/**
 * This function sums an array.
 *
 * You'll need a loop for this, and will probably want to
 * use a few registers as temporary storage.
 *
 * Some hints:
 *  * to multiply the value in a register by 2, shift it left one bit.
 *    This instruction shifts a r4's value left one bit and stores the
 *    result in r3:
 *     lsl r3, r4, #1
 *
 *  * in ARM, things in [ ] are treated as a memory address. For
 *    example, the following instruction loads the value in memory at
 *    the address contained in r4 plus 2 (r3 = Mem[r4+2]):
 *     ldr r3, [r4, #2]
 *
 *  * There are many ways to do this (hard) problem.  If you want to
 *    try and use fewer instructions, look up ARMv7 addressing modes
 *    or ask your instructor for tips.
 * 
 * @param r0: the base address of the array (pointer)
 * @param r1: the number of elements in the array
 * @returns the sum of the elements in the array
 */
.global sumArray
.type sumArray, %function
sumArray:
  /* TODO: finish this procedure here */
  sub sp, sp, #60  //make extra room
  str r0, [sp, #0] //store base address
  str r1, [sp, #4] //store max address increase
  mov r3, #0  //"i" var used in loop
  mov r4, #0  //sum var
  add r4, r4, r0
  .LOOP:
   cmp r3, r1 //if i==end num, break
   beq .ENDLOOP
   ldr r5, [r0, r3] //get value of array + position
   add r4, r4, r5   //add above value to sum var
//   add r4, r4, [r0, r3]
   add r3, r3, #1   //increment "i" var
  .ENDLOOP:
  /* return from this procedure (jump to lr) */
//  mov r0, r4
  bx lr


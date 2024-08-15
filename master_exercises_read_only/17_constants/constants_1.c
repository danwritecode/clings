/*
 * A constant in programming is a value that remains unchanged throughout the
 * execution of a program.
 *
 * This exercise focuses on defining constants correctly. The provided file will
 * not compile until the user correctly defines all constants.
 * (You can only delete/edit lines with // <-- Fix this line)
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>

// ❌ I AM NOT DONE

int main() {
  // Correctly Define the Constants

  // Define a constant integer with the value 100
  int_const = ; // <-- Fix this line

  // Define a constant float with the value 3.14
  float_const = ; // <-- Fix this line

  // Define a constant character with the value 'A'
  char_const = ; // <-- Fix this line

  // Define a constant string with the value "Hello, World!"
  str_const = ; // <-- Fix this line

  // DO NOT CHANGE
  assert(int_const == 100);
  assert(float_const == 3.14f);
  assert(char_const == 'A');
  assert(strcmp(str_const, "Hello, World!") == 0);

  printf("All constants are correctly defined!\n");

  return 0;
}

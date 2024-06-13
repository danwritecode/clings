
/*
 * This exercise focuses on using constants correctly in calculations and
 * logical operations. The provided file will not compile or run correctly until
 * the user fixes the mistakes.
 * (You can only delete/edit lines with // <-- Fix this line)
 */

#include <assert.h>
#include <stdio.h>

// ❌ I AM NOT DONE

/*
 * The first name in an `enum` has value 0, the next 1, and so on, unless
 * explicit values are specified
 */
enum boolean { NO, YES };

int main() {
  // Correctly Use the Constants
  const int MAX_VALUE = 100;
  const float PI = 3.14f;

  MAX_VALUE = 90; // <-- Fix this line

  int result = +50; // <-- Fix this line: Should be 150 (use MAX_VALUE)
  float area = PI * 10 * 10;

  // Logical operation
  const char FLAG_TRUE = 'T';
  const char FLAG_FALSE = 'F';

  char flag = 'T';
  int isTrue = (flag ==) ? YES : NO; // <-- Fix this line

  // DO NOT CHANGE
  assert(result == 100);
  assert(area == 314.0f);
  assert(isTrue == 1);

  printf("Constants used correctly in calculations and logical operations!\n");

  return 0;
}

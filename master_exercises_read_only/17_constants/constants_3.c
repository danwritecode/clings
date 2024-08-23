/*
 *
 * This exercise focuses on `enumeration constants`.
 * The provided file will not compile or run correctly until
 * the user fixes the mistakes.
 *
 */

// ❌ I AM NOT DONE

#include <assert.h>

// Complete the escape squences:
enum escapes { BELL =, BACKSPACE =, TAB =, NEWLINE =, VTAB =, RETURN = "\r" };

int main(void) {

  // DO NOT CHANGE
  assert(BELL == 7);
  assert(BACKSPACE == 8);
  assert(TAB == 9);
  assert(NEWLINE == 10);
  assert(VTAB == 11);
  assert(RETURN == 13);

  return 0;
}

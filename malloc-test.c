#include "core.h"
#include <stdlib.h>
#include <string.h>

void main() {
  char* s1, s2, s3;
  rb_set_window(redbus);
  rb_map_device(default_con_id);
  rb_enable();

  con = redbus;

  con->cursor_mode = 0;
  con->line = 1;
  print("Allocating memory...");
  s1 = malloc(sizeof(char[2]));
  strcpy(s1, "A");
  s2 = malloc(sizeof(char[4]));
  strcpy(s2, "BCD");
  s3 = malloc(sizeof(char[6]));
  strcpy(s3, "EFGHI");

  print(s1);
  print(s2);
  print(s3);
  print("The above should be A\\nBCD\\nEFGHI.");
  print("Freeing...");
  free(s1);
  free(s2);
  free(s3);
  print("Test complete.");
}

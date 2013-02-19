#include "core.h"
#include <stdlib.h>
#include <string.h>

void main() {
  char* s1, *s2, *s3;
  char buf[10];
  // Basic setup
  initialize_dynamic_memory();

  rb_set_window(redbus);
  rb_map_device(default_con_id);
  rb_enable();

  con = redbus;

  con->cursor_mode = 0;
  con->line = 1;
  strcpy(buf, "0x");

  print("Allocating memory...");
  s1 = malloc(2);
  itoa(s1, buf+2, 16);
  print(buf);
  strcpy(s1, "A");
  s2 = malloc(4);
  itoa(s2, buf+2, 16);
  print(buf);
  strcpy(s2, "BCD");
  s3 = malloc(6);
  itoa(s3, buf+2, 16);
  print(buf);
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

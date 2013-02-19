#include "core.h"
#include <stdlib.h>
#include <string.h>

typedef struct buddyblock {
  uint8_t free;
  uint8_t size;
  struct buddyblock* next;
  struct buddyblock* prev;
} bblock_t;

extern bblock_t* freelists[];

char buf[30];

void checknum(int);

void main() {
  char* s1, *s2, *s3;
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
  print("Testing freelists.");
  checknum(12);
  print("Test complete.");
}

void checknum(int i) {
  if (i == 0) return;
  memset(buf, '_', 29);
  buf[29] = 0;
  itoa(i, buf, 10);
  buf[strlen(buf)]= '_';
  itoa(freelists[i], buf+3, 16);
  buf[strlen(buf)]= '_';
  itoa(freelists[i]->size, buf+8, 10);
  buf[strlen(buf)]= '_';
  print(buf);
  print("-=-=-");
  checknum(i-1);
}

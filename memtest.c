#include "core.h"
#include <string.h>

void test(unsigned int* loc)
{
  *loc = 0xAB;
  if (*loc == 0xAB) { print("PASS"); }
  else { print("FAIL"); }
}

void main() {
  rb_set_window(redbus);
  rb_map_device(default_con_id);
  rb_enable();

  con = redbus;

  con->cursor_mode = 2;
  print("Memory test.");
  print("TESTING 0x0000");
  test((uint16_t*)0x0000);
  print("TESTING 0x2000");
  test((uint16_t*)0x2000);
  print("TESTING 0x4000");
  test((uint16_t*)0x4000);
  print("TESTING 0x6000");
  test((uint16_t*)0x6000);
  print("TESTING 0x8000");
  test((uint16_t*)0x8000);
  print("TESTING 0xA000");
  test((uint16_t*)0xA000);
  print("TESTING 0xC000");
  test((uint16_t*)0xC000);
  print("TESTING 0xE000");
  test((uint16_t*)0xE000);
  
}

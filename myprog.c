#include "core.h"

#define LPROMPT 49

void test(unsigned int* loc)
{
  *loc = 0xAB;
  if (*loc == 0xAB) { print("PASS"); }
  else { print("FAIL"); }
}

void main() {
  char buf[80];

  rb_set_window(redbus);
  rb_map_device(default_con_id);
  rb_enable();

  con = redbus;

  con->cursor_mode = 2;
  con->line = 1;
  print("WAITING FOR INPUT...");

  con->line = LPROMPT;
  getline(buf, 80);
  fill(0x20,0,LPROMPT,SCREEN_W,1);
  con->cursor_x = 0;
  con->line = 1;
  print(buf);
  print("PROGRAM DONE!");
}

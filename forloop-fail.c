#include "core.h"

void pass()
{
  int i;
  char buf[10];

  for (i=0;i!=6;++i) {
    // Code here
    itoa(i, buf+3, 10);
    if (i < 3) buf[0] = '<';
    else buf[0] = ' ';
    if (i == 3) buf[1] = '=';
    else buf[1] = ' ';
    if (i > 3) buf[2] = '>';
    else buf[2] = ' ';
    print(buf);
  }
}

void infinite()
{
  int i;
  for (i=0; i < 3; ++i) {
    print("-");
  }
  for (i=0; i > 3; ++i) {
    print("+");
  }
}

void main()
{
  rb_set_window(redbus);
  rb_map_device(default_con_id);
  rb_enable();

  con = redbus;

  con->cursor_mode = 0;
  con->line = 1;

  print("Begin!");
  print("pass"); pass();
  print("infinite"); infinite();
  print("End!");
}

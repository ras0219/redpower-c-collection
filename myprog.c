#include "core.h"

void main() {
  int i;
  int len;
  char buf[20];
  i = 0;
  rb_set_window(redbus);
  rb_map_device(default_con_id);
  rb_enable();

  con = redbus;

  con->cursor_mode = 0;
  con->line = 1;

  print("Begin!");
  i = 0;
  while(1) {
    itoa(i, buf, 10);
    len = strlen(buf);
    buf[len] = ' ';
    itoa((i!=3), buf+len+1, 10);
    print(buf);
    if (i==3) break;
    ++i;
  }
  print("End!");
}

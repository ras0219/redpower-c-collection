#include "core.h"

void pass()
{
  int i;

  i = 0;
  while(1) {
    if (i == 3) break;
    // Code here
    print("+");
    ++i;
  }
}

void maybe()
{
  int i;

  i = 0;
  while(i != 3) {
    // Code here
    print("+");
    ++i;
  }
}

void failmaybe()
{
  int i;

  i = 0;
  for(;i != 3;) {
    // Code here
    print("+");
    ++i;
  }
}

void fail()
{
  int i;

  for(i = 0;i != 3;++i) {
    // Code here
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
  print("maybe"); maybe();
  print("failmaybe"); failmaybe();
  print("fail"); fail();
  print("End!");
}

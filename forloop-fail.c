#include "core.h"


//int = 16bit return value.
//0000 0000 = success
//bits set to 1 indicate failure
//up to 16 tests per function

//both unsigned and signed
//b0 >
//b1 <
//b2 & | 
//b3 ^
//b4 - +
//b5 * 
//b6 / %

int int8_test()
{
  return 0;
}
int int16_test()
{
  return 0;
}
int int32_test()
{
  return 0;
}


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

int gt(int a, int b) {
  return (b-a) & (1 << 15);
}

int lt(int a, int b) {
  return (a-b) & (1 << 15);
}

void workaround()
{
  int i;
  char buf[10];

  for (i=0;i!=6;++i) {
    // Code here
    itoa(i, buf+3, 10);
    if (lt(i, 3)) buf[0] = '<';
    else buf[0] = ' ';
    if (i == 3) buf[1] = '=';
    else buf[1] = ' ';
    if (gt(i, 3)) buf[2] = '>';
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
  print("workaround"); workaround();
  print("infinite"); infinite();
  print("End!");
}

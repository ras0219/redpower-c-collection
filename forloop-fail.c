#include "core.h"
#include "stdint.h"


//make sure:  a,b,c,d are enabled
#define TEST(var1, operation, var2) \
    do{\
  a = var1 ;\
  b = var2 ;\
  c = (a operation b);\
  d = (var1 operation var2);\
  if(c != d) \
    print("failed! "  #var1  #operation  #var2 );\
    }\
  while(0);\


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
  int8_t a,b,c,d = 0;
  
  TEST(0, - ,0);
  TEST(5, - ,0);

  TEST(0, - ,5);
  TEST(6, - ,3);
  
  TEST(-10, - ,1);
  
  TEST(125, > , 126);

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

#define weak_assert(cond)	      \
  if (!(cond))			      \
    print("Assertion failed: " #cond);

void main()
{
  rb_set_window(redbus);
  rb_map_device(default_con_id);
  rb_enable();

  con = redbus;

  con->cursor_mode = 0;
  con->line = 1;

  print("Begin");
  //int8_test();
  //while(1);

  /*print("Begin!");
  print("pass"); pass();
  print("workaround"); workaround();
  print("infinite"); infinite();
  */
  {
    uint8_t u8_0 = 0,
      u8_1 = 1,
      u8_127 = 127,
      u8_128 = 128,
      u8_129 = 129,
      u8_255 = 255;

    weak_assert(u8_1 > u8_0);
    weak_assert(u8_127 > u8_0);
    weak_assert(u8_128 > u8_0);
    weak_assert(u8_129 > u8_0);
    weak_assert(u8_255 > u8_0);

    weak_assert(u8_0 < u8_1);
    weak_assert(u8_0 < u8_127);
    weak_assert(u8_0 < u8_128);
    weak_assert(u8_0 < u8_129);
    weak_assert(u8_0 < u8_255);

    weak_assert(u8_127 > u8_1);
    weak_assert(u8_128 > u8_1);
    weak_assert(u8_129 > u8_1);
    weak_assert(u8_255 > u8_1);

    weak_assert(u8_1 < u8_127);
    weak_assert(u8_1 < u8_128);
    weak_assert(u8_1 < u8_129);
    weak_assert(u8_1 < u8_255);

    weak_assert(u8_128 > u8_127);
    weak_assert(u8_129 > u8_127);
    weak_assert(u8_255 > u8_127);

    weak_assert(u8_127 < u8_128);
    weak_assert(u8_127 < u8_129);
    weak_assert(u8_127 < u8_255);

    weak_assert(u8_129 > u8_128);
    weak_assert(u8_255 > u8_128);

    weak_assert(u8_128 < u8_129);
    weak_assert(u8_128 < u8_255);

    weak_assert(u8_255 > u8_129);

    weak_assert(u8_129 < u8_255);
  }
  print("End!");
}

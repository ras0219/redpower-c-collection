#include <redbus.h>
#include <console.h>
#include <string.h>
#include <stdint.h>

#define redbus (Console*)0x0300
#define default_console_id 0x01

#define malloc_start (void*)0x2000
#define heap_space (size_t)0x2000

void* malloc(size_t sz)
{
  return NULL;
}

char * text = "Hello, C World!";
unsigned int * base = NULL;
Console* console;

void print(char * text)
{
  int len;
  len = strlen(text);
  memcpy(console->display, text, len);
  console->line += 1;
}

void test(unsigned int* loc)
{
  *loc = 0xAB;
  if (*loc == 0xAB) { print("PASS"); }
  else { print("FAIL"); }
}

void main() {
  rb_set_window(redbus);
  rb_map_device(default_console_id);
  rb_enable();

  console = redbus;

  console->cursor_mode = 2;
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

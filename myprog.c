#include <redbus.h>
#include <console.h>
#include <string.h>
#include <stdint.h>

#define redbus (Console*)0x0300
#define default_con_id 0x01

#define malloc_start (void*)0x2000
#define heap_space (size_t)0x4000

#define LF 13

#define SCREEN_W 80
#define SCREEN_H 50

#define LPROMPT 49

char * text = "Hello, C World!";
unsigned int * base = NULL;
Console* con;

void blit(char command, char x, char y, char xo, char yo, char w, char h) {
	con->blit_start_x = x;
	con->blit_start_y = y;
	con->blit_offset_x = xo;
	con->blit_offset_y = yo;
	con->blit_width = w;
	con->blit_height = h;
	con->blit_mode = command;
	while(con->blit_mode != 0) ; //WAI
}

void* malloc(size_t sz)
{
  static uint8_t* ptr = malloc_start;
  void* retptr = ptr;
  ptr += sz;
  return retptr;
}

void free(void*)
{
  // BEST FREE EVER
}

void print(char * text)
{
  int len;
  len = strlen(text);
  memcpy(con->display, text, len);
  con->line += 1;
}

void test(unsigned int* loc)
{
  *loc = 0xAB;
  if (*loc == 0xAB) { print("PASS"); }
  else { print("FAIL"); }
}

void getline(char* buf, size_t len)
{
  while (1) {
    con->line = LPROMPT;
    while (con->kb_pos != con->kb_start) {
      if (con->kb_key == LF) {
	buf[con->cursor_x] = '\0';
	fill(0x20,0,LPROMPT,SCREEN_W,1);
	con->cursor_x = 0;
	++con->kb_start;
	return;
      }
      buf[con->cursor_x] = con->kb_key;
      con->display[con->cursor_x] = con->kb_key;
      ++con->cursor_x;
      ++con->kb_start;
    }
  }
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

  getline(buf, 80);
  con->line = 1;
  print(buf);
  print("PROGRAM DONE!");
}

#include "core.h"

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

size_t getline(char* buf, size_t len) {
  size_t l = 0;
  while (1) {
    while (con->kb_pos != con->kb_start) {
      if (con->kb_key == LF) {
	buf[con->cursor_x] = '\0';
	++con->kb_start;
	return l;
      }
      if (con->kb_key == BK) {
	if (l == 0) continue;
	++con->kb_start;
	if (con->cursor_x == 0) {
	  con->cursor_x = SCREEN_W - 1;
	  --con->line;
	  con->cursor_y -= 1;
	} else {
	  --con->cursor_x;
	}
	buf[con->cursor_x] = '\0';
	con->display[con->cursor_x] = 0x20;
	--l;
	continue;
      }
      if (l < len - 1) {
	buf[con->cursor_x] = con->kb_key;
	con->display[con->cursor_x] = con->kb_key;
	if (con->cursor_x == SCREEN_W - 1) {
	  con->cursor_x = 0;
	  ++con->cursor_y;
	  ++con->line;
	} else {
	  ++con->cursor_x;
	}
	++con->kb_start;
	++l;
      }
    }
  }
}

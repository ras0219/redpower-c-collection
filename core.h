#ifndef _CORE_H_
#define _CORE_H_

#include <redbus.h>
#include <console.h>
#include <string.h>
#include <stdint.h>
#include "buddy.h"

#define redbus (Console*)0x0300
#define default_con_id 0x01

#define malloc_start (void*)0x2000
#define heap_space (size_t)0x4000

#define LF 13
#define BK 8

#define SCREEN_W 80
#define SCREEN_H 50

extern Console* con;

void blit(char command, char x, char y, char xo, char yo, char w, char h);

size_t getline(char* buf, size_t len);

// Print one line at con->line
// text - zero terminated string
// (side effect: con->line++)
void print(char* text);

#endif

#ifndef _CORE_H_
#define _CORE_H_

#include <redbus.h>
#include <iox.h>
#include <stdint.h>

#define redbus (Iox*)0x0300
#define default_con_id 0x03

extern Iox* con;

void elevator_up();
void elevator_down();
void elevator_reset();

#endif

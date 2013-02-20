#ifndef _ELEVATOR_H_
#define _ELEVATOR_H_

#include <redbus.h>
#include "core.h"
#include <iox.h>
#include <stdint.h>
#include <cpu.h>

#define IOX_redbus (Iox*)0x0300
#define CON_redbus (Console*)0x0300
#define IOX_con_id 0x03
#define CON_con_id 0x01

#define ELEV_CLEAN WHITE 
#define ELEV_UP    BLACK
#define ELEV_DOWN  RED

#define ELEVATOR_RESET_COUNT 32

#define ELEV_DELAY \
    do { \
        for(del=0;del<20000;del++);\
    } while (0)


void elevator_up();
void elevator_down();
void elevator_reset();

#endif

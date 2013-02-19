#ifndef _CORE_H_
#define _CORE_H_

#include <redbus.h>
#include <iox.h>
#include <stdint.h>
#include <cpu.h>

#define redbus (Iox*)0x0300
#define IOX_con_id 0x03

#define ELEV_CLEAN WHITE 
#define ELEV_UP    BLACK
#define ELEV_DOWN  RED

#define ELEVATOR_RESET_COUNT 32

#define ELEV_DELAY \
    do { \
        wait();\
        wait();\
    } while (0)


void elevator_up();
void elevator_down();
void elevator_reset();

#endif

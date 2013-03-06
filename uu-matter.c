#include "core.h"
#include "stdint.h"
#include <iox.h>
#include <cpu.h>

#define IOX_redbus (Iox*)0x0300

#define UU_GENER_ON WHITE
#define IT_IS_SHINING BLACK
#define ENERGY_EMPTY RED

void main()
{
  int i=0;
  int can_run = 0;
  Iox* our_expand = IOX_redbus;

  rb_set_window(IOX_redbus);
  rb_map_device(3);
  rb_enable();


  for(;;) //best OS NA
  {
   can_run = 1;
   
   if((our_expand->in & ENERGY_EMPTY) == (ENERGY_EMPTY))
    can_run=0;
   if((our_expand->in & IT_IS_SHINING) != (IT_IS_SHINING))
    can_run=0;
   
   if(can_run==0) //damn reversed logic
      our_expand->out|= UU_GENER_ON; 
   else
      our_expand->out = 0;

    wait();
    wait();
    wait();
    wait();
    wait();


    wait();
    wait();
    wait();
    wait();
    wait();
 
    wait();
    wait();
    wait();
    wait();
    wait();
  
    wait();
    wait();
    wait();
    wait();
    wait();
  }

  
}

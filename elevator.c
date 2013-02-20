#include "elevator.h"

Iox* our_expand;

int del = 0;

void main() {
  //char buf[80];
  int i =0;
  our_expand = IOX_redbus;
  con = CON_redbus;
  
  rb_set_window(CON_redbus);
  rb_map_device(CON_con_id);
  rb_enable();
  print("Starting");
  if(1)
    print("True");
  else
    print("False");
meow_goto:
  print("a");
  i++; 
  if(i!=10)
      goto meow_goto;
  rb_disable();

  rb_set_window(IOX_redbus);
  rb_map_device(IOX_con_id);
  rb_enable();

  elevator_reset();
  rb_disable();

  rb_set_window(CON_redbus);
  rb_map_device(CON_con_id);
  rb_enable();
  print("Reset!");
  rb_disable();

  rb_set_window(IOX_redbus);
  rb_map_device(IOX_con_id);
  rb_enable();
  
  for(;;)
  {
    for(i=0;i<20;i++)
    {
      elevator_up();
    }
    for(i=0;i<20;i++)
    {
      elevator_down();
    }
  }
}

void elevator_up()
{
  our_expand->out |= ELEV_UP;
  ELEV_DELAY;
  our_expand->out &= ~ELEV_UP;

  our_expand->out |= ELEV_CLEAN;
  ELEV_DELAY;
  our_expand->out &= ~ELEV_CLEAN;
}

void elevator_down()
{
  our_expand->out |= ELEV_DOWN;
  ELEV_DELAY;
  our_expand->out &= ~ELEV_DOWN;

  our_expand->out |= ELEV_CLEAN;
  ELEV_DELAY;
  our_expand->out &= ~ELEV_CLEAN;
}

void elevator_reset()
{
  int reset_cycle=0;
  for(reset_cycle=0;reset_cycle<ELEVATOR_RESET_COUNT;reset_cycle++)
  {
    elevator_down();
  }
}

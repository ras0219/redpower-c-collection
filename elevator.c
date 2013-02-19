#include "elevator.h"

Iox* our_expand;
void main() {
  //char buf[80];
  int i =0;
  our_expand = redbus;

  rb_set_window(redbus);
  rb_map_device(IOX_con_id);
  rb_enable();

  elevator_reset();
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

  our_expand->out &= ELEV_UP;

  our_expand->out |= ELEV_CLEAN;
  ELEV_DELAY;
  our_expand->out &= ELEV_CLEAN;
}

void elevator_down()
{
  our_expand->out |= ELEV_DOWN;
  ELEV_DELAY;
  our_expand->out &= ELEV_DOWN;

  our_expand->out |= ELEV_CLEAN;
  ELEV_DELAY;
  our_expand->out &= ELEV_CLEAN;
}

void elevator_reset()
{
  int reset_cycle=0;
  for(reset_cycle=0;reset_cycle<ELEVATOR_RESET_COUNT;reset_cycle++)
  {
    elevator_down();
  }
}

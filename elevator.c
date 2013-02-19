#include "elevator.h"


void main() {
  //char buf[80];
  Iox* our_expand = redbus;

  rb_set_window(redbus);
  rb_map_device(default_con_id);
  rb_enable();

  our_expand->out = ~0;
}

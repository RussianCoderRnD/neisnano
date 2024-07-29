#ifndef LOL_H
#define LOL_H

#include <avr/wdt.h>

void lol(int val) {
    if(val >=100){wdt_enable(WDTO_15MS);  
      while (1) {}
  }
}

#endif 
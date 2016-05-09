#include <unistd.h>
#include <iostream>
#include "pierogi.h"

int main() {
  SharedQueue kolejka(FARSZ_Q);
  SharedQueue debug(DEBUG_Q);

  for(;;) {
    kolejka.push(GRZYB);
    debug.push(GRZYB);
    usleep(GRZYB_T);
  }

  return 0;
}

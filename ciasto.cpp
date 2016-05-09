#include <unistd.h>
#include <iostream>
#include "pierogi.h"

int main() {
  SharedQueue kolejka(CIASTO_Q);
  SharedQueue debug(DEBUG_Q);

  for(;;) {
    kolejka.push(CIASTO);
    debug.push(CIASTO);
    usleep(CIASTO_T);
  }

  return 0;
}

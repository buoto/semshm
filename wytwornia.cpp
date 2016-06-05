#include <unistd.h>
#include <iostream>
#include <cstdio>
#include "pierogi.h"

int main() {
  SharedQueue farsz(FARSZ_Q);
  SharedQueue ciasto(CIASTO_Q);
  SharedQueue pierogi(PIEROGI_Q);
  SharedQueue debug(DEBUG_Q);

  for(;;) {
    char f = farsz.pop()+4;
    ciasto.pop();
    pierogi.push(f);
    debug.push(f);
    usleep(PIEROG_T);
  }

  return 0;
}

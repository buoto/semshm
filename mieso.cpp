#include <unistd.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "pierogi.h"

int main() {
  SharedQueue kolejka(FARSZ_Q);
  SharedQueue debug(DEBUG_Q);

  srand (time(NULL));
  for(;;) {
    kolejka.push_priority(MIESO);
    debug.push(MIESO);
    float r = rand() % 1000000;
    usleep(MIESO_T);
  }

  return 0;
}

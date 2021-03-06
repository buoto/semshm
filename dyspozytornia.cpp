#include <unistd.h>
#include <iostream>
#include <cstdio>
#include "pierogi.h"

int main() {
  SharedQueue pierogi(PIEROGI_Q);
  SharedQueue debug(DEBUG_Q);

  for(;;) {
    char f = pierogi.pop();
    switch (f) {
      case MIESNE:
        std::cout << "miesne" << std::endl;
        break;
      case GRZYBOWE:
        std::cout << "grzybowe" << std::endl;
        break;
      case SEROWE:
        std::cout << "serowe" << std::endl;
        break;
    }
    usleep(DYSPOZY_T);
  }

  return 0;
}

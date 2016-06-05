#include <unistd.h>
#include <iostream>
#include "pierogi.h"

int count[8];

int main() {
  SharedQueue kolejka(DEBUG_Q);

  for(;;) {
    char c = kolejka.pop();
    count[c+1] ++;
    switch (c) {
      case MIESO:
        std::cout << "mieso" << std::endl;
        break;
      case SER:
        std::cout << "ser" << std::endl;
        break;
      case GRZYB:
        std::cout << "grzyb" << std::endl;
        break;
      case CIASTO:
        std::cout << "ciasto" << std::endl;
        break;
      case MIESNE:
        std::cout << "miesne" << std::endl;
        break;
      case GRZYBOWE:
        std::cout << "grzybowe" << std::endl;
        break;
      case SEROWE:
        std::cout << "serowe" << std::endl;
        break;
      default:
        std::cout << c << std::endl;
    }
    std::cout << "g: " << count[GRZYB + 1] << " m: " << count[MIESO + 1] <<
     " s: " << count[SER + 1] <<
     " c: " << count[CIASTO + 1] << " G:" << count[GRZYBOWE + 1] <<
     " M: " << count[MIESNE + 1] <<
     " S: " << count[SEROWE + 1] << std::endl;
  }

  return 0;
}

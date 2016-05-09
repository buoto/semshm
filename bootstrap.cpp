#include <iostream>
#include "pierogi.h"

int main() {
  std::cout << "Inicjalizacja kolejek..." << std::endl;
  SharedQueue farsz(FARSZ_Q, true),
              ciasto(CIASTO_Q, true),
              pierogi(PIEROGI_Q , true),
              debug(DEBUG_Q , true);
  std::cout << "Aby zakończyć wcisnij Ctrl+D" << std::endl;
  char c;
  while(std::cin >> c);
  return 0;
}

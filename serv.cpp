#include <iostream>

#include "shared_queue.h"


int main() {
  char c;
  try {
    SharedQueue q(2778, true);
    std::cin >> c;
  } catch (shmerror e) {
    perror("shm");
  }
  return 0;
}

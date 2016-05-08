#include <iostream>

#include "shared_queue.h"


int main() {
  try {
    SharedQueue q(2778, false);
    q.push('x');
      q.print_contents();
      q.pop();
    for(char i = 0; i < 4; i ++){
      q.push('a' + i);
      q.print_contents();
    }
    q.push_priority('P');
      q.print_contents();
    q.push_priority('P');
      q.print_contents();
      q.pop();
      q.pop();
      q.pop();
      q.print_contents();
      q.pop();
      q.print_contents();
      q.pop();
      q.print_contents();
      q.pop();
      q.print_contents();
      q.pop();
      q.print_contents();
  } catch (shmerror e) {
    perror("shm");
  }

  return 0;
}

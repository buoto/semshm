#ifndef PIEROGI_H
#define PIEROGI_H

#include "shared_queue.h"

extern const int FARSZ_Q = 2786;
extern const int CIASTO_Q = 2779;
extern const int PIEROGI_Q = 2789;
extern const int DEBUG_Q = 666666;

enum produkt {
  MIESO,
  GRZYB,
  CIASTO,
  MIESNE,
  GRZYBOWE
};

extern const int MIESO_T = 1500000;
extern const int GRZYB_T = 1000000/5;
extern const int CIASTO_T = 1000000/7;
extern const int PIEROG_T = 1000000/4;

#endif

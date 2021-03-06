#ifndef PIEROGI_H
#define PIEROGI_H

#include "lib/shared_queue.h"

extern const int FARSZ_Q = 2786;
extern const int CIASTO_Q = 2779;
extern const int PIEROGI_Q = 2789;
extern const int DEBUG_Q = 666666;

enum produkt {
  MIESO,
  GRZYB,
  SER,
  CIASTO,
  MIESNE,
  GRZYBOWE,
  SEROWE
};

extern const int MIESO_T = 1000000/3;
extern const int GRZYB_T = 1000000/5;
extern const int SER_T = 1000000/3;
extern const int CIASTO_T = 1000000/8;
extern const int PIEROG_T = 1000000/5;
extern const int DYSPOZY_T = 1000000/3;

#endif

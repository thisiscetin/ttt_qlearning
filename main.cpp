#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>

#include "trainer.hpp"

int main() {
  strategy* s = new strategy {0.5, 0.2, 1};
  agent* a = new agent(marker::x, s);
  dummy_agent* d = new dummy_agent();

  trainer* t = new trainer(a, d);
  t->play();

  return 0;
}


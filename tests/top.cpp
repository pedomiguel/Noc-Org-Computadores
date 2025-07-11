#include "../include/top.hpp"
#include "sysc/kernel/sc_simcontext.h"

#include <systemc.h>

int sc_main(int argc, char **argv) {
  Top rede("rede_teste", 3);
  rede.nodes[0][0]->send(1, 1, "teste");
  
  sc_core::sc_start(10, sc_core::SC_NS);
  return 0;
}

#ifndef TOP_HPP
#define TOP_HPP

#include "router.hpp"

#include "sysc/kernel/sc_module.h"
#include <systemc.h>

SC_MODULE(Top) {
  int n; // Square dimention
  Router** nodes;

  SC_CTOR(Top) = delete;
  Top(sc_core::sc_module_name name, int size);
  ~Top();
};

#endif // !TOP_HPP

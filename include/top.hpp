#ifndef TOP_HPP
#define TOP_HPP

#include "router.hpp"

#include "sysc/kernel/sc_module.h"
#include <systemc.h>

SC_MODULE(Top) {
  int n; // Square dimention
  Router** nodes;
  // Add enlaces

};

#endif // !TOP_HPP

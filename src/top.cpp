#include "../include/top.hpp"
#include "sysc/kernel/sc_module.h"

#include <string>
#include <systemc.h>

Top::Top(sc_core::sc_module_name name, int size)
  : sc_module(name), n(size) {
  nodes = new Router*[n * n];

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int idx = i * n + j;

      std::string node_name = "Node_" + std::to_string(j) + std::to_string(i);
      Algorithm algorithm = XY; // Define dynamically

      nodes[idx] = new Router(node_name.c_str(), algorithm);
      nodes[idx]->x = i;
      nodes[idx]->y = j;
    }
  }
}

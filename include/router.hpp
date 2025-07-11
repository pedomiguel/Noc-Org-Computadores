#include "package.hpp"

#include <systemc.h>

#ifndef ROUTER_HPP
#define ROUTER_HPP

enum Direction {SOUTH = 0, NORTH, EAST, WEST, LOCAL};
enum Algorithm {XY, WEST_FIRST};

extern const int WIDTH;
extern const int HEIGHT;

SC_MODULE(Router) {
  sc_core::sc_fifo_in<Package> in_ports[5];
  sc_core::sc_fifo_out<Package> out_ports[5];
  sc_core::sc_fifo<Package> buffers[5];
  int x, y;
  Algorithm algorithm;

  void input_process();
  void routing_process();
  void route_xy(Package& package);
  void route_west_first(Package& package);

  SC_CTOR(Router);
  Router(sc_core::sc_module_name name, Algorithm algorithm, int x, int y);
  Router();
};

#endif

#include <systemc.h>
#include "package.hpp"

#ifndef NODE_HPP
#define NODE_HPP

SC_MODULE(Node) {
  sc_core::sc_fifo_in<Package> in_port;
  sc_core::sc_fifo_out<Package> out_port;
  int x, y;

  void read();
  void send(int to_x, int to_y, std::string data);

  SC_CTOR(Node);
  Node(sc_core::sc_module_name name, int x, int y);
  Node();
};

#endif

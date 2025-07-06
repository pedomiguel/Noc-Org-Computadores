#include <systemc.h>
#include "package.hpp"

#ifndef LINK_HPP
#define LINK_HPP

SC_MODULE(Link) {
  sc_in<bool> val_in[2], ack_in[2];
  sc_in<Package> data_in[2];

  sc_out<bool> val_out[2], ack_out[2];
  sc_out<Package> data_out[2];

  void process();

  SC_CTOR(Link);
};

#endif

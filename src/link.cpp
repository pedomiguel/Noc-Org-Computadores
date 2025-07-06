#include "../include/link.hpp"

void Link::process() {
    for(int i=0; i<2; i++) {
        val_out[i].write(val_in[i]);
        ack_out[i].write(ack_in[i]);
        data_out[i].write(data_in[i]);
    }
}

Link::Link(sc_module_name name) : sc_module(name) {
    SC_METHOD(process);
    sensitive << val_in << ack_in << data_in;
  }
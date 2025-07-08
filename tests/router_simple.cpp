#include "../include/router.hpp"
#include "../include/package.hpp"

#include "sysc/kernel/sc_simcontext.h"
#include <iostream>

int sc_main(int argc, char **argv) { // TEM QUE SER (int argc, char **argv)
  Router r("Router_test", XY);
  r.x = 0, r.y = 0;

  sc_core::sc_fifo<Package> local_in_fifo(4);
  sc_core::sc_fifo<Package> east_out_fifo(4);

  sc_core::sc_fifo<Package> dummy_in_east(1);
  sc_core::sc_fifo<Package> dummy_in_north(1);
  sc_core::sc_fifo<Package> dummy_in_south(1);
  sc_core::sc_fifo<Package> dummy_in_west(1);

  sc_core::sc_fifo<Package> dummy_out_local(1);
  sc_core::sc_fifo<Package> dummy_out_west(1);
  sc_core::sc_fifo<Package> dummy_out_north(1);
  sc_core::sc_fifo<Package> dummy_out_south(1);

  r.in_ports[LOCAL](local_in_fifo);
  r.out_ports[EAST](east_out_fifo);

  r.in_ports[EAST](dummy_in_east);
  r.in_ports[NORTH](dummy_in_north);
  r.in_ports[SOUTH](dummy_in_south);
  r.in_ports[WEST](dummy_in_west);

  r.out_ports[LOCAL](dummy_out_local);
  r.out_ports[WEST](dummy_out_west);
  r.out_ports[NORTH](dummy_out_north);
  r.out_ports[SOUTH](dummy_out_south);

  Package pkg;
  pkg.src_x = 0, pkg.src_y = 0;
  pkg.dest_x = 2, pkg.dest_y = 0;
  pkg.data = "Data Test";

  local_in_fifo.write(pkg);

  sc_core::sc_start(10, sc_core::SC_NS);

  if (east_out_fifo.num_available() > 0) {
    Package out_pkg = east_out_fifo.read();
    std::cout << "Package routed to (" << out_pkg.dest_x << ", " << out_pkg.dest_y << ") | With data: " << out_pkg.data << std::endl;
  } else {
    std::cout << "No Package found" << std::endl;
  }

  return 0;
}

#include "../include/router.hpp"
#include "sysc/kernel/sc_simcontext.h"

#include <systemc.h>

int sc_main(int argc, char **argv) {
  Router src_r("src", XY);
  Router inter_r("inter", XY);
  Router dest_r("dest", XY);
  src_r.x = 0, src_r.y = 0;
  inter_r.x = 1, inter_r.y = 0;
  dest_r.x = 1, dest_r.y = 1;

  //    |
  // -> ^

  sc_core::sc_fifo<Package> dummy[100];
  sc_core::sc_fifo<Package> link[2];

  sc_core::sc_fifo<Package> src_pkg(4);
  sc_core::sc_fifo<Package> dest_pkg(4);

  src_r.in_ports[NORTH](dummy[0]);
  src_r.in_ports[SOUTH](dummy[1]);
  src_r.in_ports[WEST](dummy[2]);
  src_r.in_ports[EAST](dummy[3]);
  src_r.out_ports[NORTH](dummy[4]);
  src_r.out_ports[SOUTH](dummy[5]);
  src_r.out_ports[WEST](dummy[6]);
  src_r.out_ports[LOCAL](dummy[7]);

  inter_r.in_ports[LOCAL](dummy[8]);
  inter_r.in_ports[EAST](dummy[9]);
  inter_r.in_ports[SOUTH](dummy[10]);
  inter_r.in_ports[NORTH](dummy[11]);
  inter_r.out_ports[LOCAL](dummy[12]);
  inter_r.out_ports[NORTH](dummy[13]);
  inter_r.out_ports[EAST](dummy[14]);
  inter_r.out_ports[WEST](dummy[15]);

  dest_r.in_ports[SOUTH](dummy[16]);
  dest_r.in_ports[WEST](dummy[17]);
  dest_r.in_ports[LOCAL](dummy[18]);
  dest_r.in_ports[EAST](dummy[19]);
  dest_r.out_ports[NORTH](dummy[20]);
  dest_r.out_ports[SOUTH](dummy[21]);
  dest_r.out_ports[WEST](dummy[22]);
  dest_r.out_ports[EAST](dummy[23]);

  src_r.in_ports[LOCAL](src_pkg);
  dest_r.out_ports[LOCAL](dest_pkg);

  src_r.out_ports[EAST](link[0]);
  inter_r.in_ports[WEST](link[0]);
  inter_r.out_ports[SOUTH](link[1]);
  dest_r.in_ports[NORTH](link[1]);

  Package pkg;
  pkg.src_x = 0, pkg.src_y = 0;
  pkg.dest_x = 1, pkg.dest_y = 1;
  pkg.data = "Router to Router test";

  src_pkg.write(pkg);

  sc_core::sc_start(10, sc_core::SC_NS);

  if (dest_pkg.num_available() > 0) {
    Package incoming_pkg = dest_pkg.read();
    std::cout << "Package came: " << incoming_pkg.data << std::endl;
  } else {
    std::cout << "Package did not came" << std::endl;
  }

  return 0;
}

#include "../include/router.hpp"
#include "../include/node.hpp"
#include "sysc/kernel/sc_simcontext.h"

#include <systemc.h>

int sc_main(int argc, char **argv) {
  Node src_node("src_node", 0, 0);
  Node tgt_node("tgt_node", 1, 0);

  Router src_node_router("src_node_router", XY);
  Router tgt_node_router("tgt_node_router", XY);
  src_node_router.x = 0, src_node_router.y = 0;
  tgt_node_router.x = 1, tgt_node_router.y = 0;

  sc_core::sc_fifo<Package> dummy[12];
  sc_core::sc_fifo<Package> link_routers_1(4), link_routers_2;
  sc_core::sc_fifo<Package> link_src_1(4), link_tgt_1(4), link_src_2(4), link_tgt_2(4);

  src_node_router.out_ports[NORTH](dummy[0]);
  src_node_router.out_ports[SOUTH](dummy[1]);
  src_node_router.out_ports[WEST](dummy[2]);
  src_node_router.in_ports[NORTH](dummy[3]);
  src_node_router.in_ports[SOUTH](dummy[4]);
  src_node_router.in_ports[WEST](dummy[5]);
  tgt_node_router.out_ports[NORTH](dummy[6]);
  tgt_node_router.out_ports[SOUTH](dummy[7]);
  tgt_node_router.out_ports[EAST](dummy[8]);
  tgt_node_router.in_ports[NORTH](dummy[9]);
  tgt_node_router.in_ports[SOUTH](dummy[10]);
  tgt_node_router.in_ports[EAST](dummy[11]);

  src_node_router.out_ports[EAST](link_routers_1);
  tgt_node_router.in_ports[WEST](link_routers_1);
  src_node_router.in_ports[EAST](link_routers_2);
  tgt_node_router.out_ports[WEST](link_routers_2);

  src_node.out_port(link_src_1);
  src_node_router.in_ports[LOCAL](link_src_1);
  src_node_router.out_ports[LOCAL](link_src_2);
  src_node.in_port(link_src_2);

  tgt_node.out_port(link_tgt_1);
  tgt_node_router.in_ports[LOCAL](link_tgt_1);
  tgt_node_router.out_ports[LOCAL](link_tgt_2);
  tgt_node.in_port(link_tgt_2);

  src_node.send(1, 0, "teste");
  tgt_node.send(0, 0, "teste 2");

  sc_core::sc_start(10, sc_core::SC_NS);
  
  
  return 0;
}

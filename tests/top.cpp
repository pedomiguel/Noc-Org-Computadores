#include "../include/top.hpp"
#include "sysc/kernel/sc_simcontext.h"
#include <systemc.h>
#include <time.h>
#include <random>


std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());

std::pair<int, int> random_pair(int n) {
  std::uniform_int_distribution<int> uid(0, n-1);
  return std::make_pair(uid(rng), uid(rng));
}

int sc_main(int argc, char **argv) {
  int noc_size = std::stoi(argv[1]);
  Algorithm algorithm = (Algorithm) std::stoi(argv[2]);
  int pkg_cnt=std::stoi(argv[3]);

  Top noc("rede_teste", noc_size, algorithm);

  for(int i=0; i<pkg_cnt; i++) {
    int src_x, src_y;
    int tgt_x, tgt_y;

    do {
      std::tie(src_x, src_y) = random_pair(noc_size);
      std::tie(tgt_x, tgt_y) = random_pair(noc_size);
    } while(src_x == tgt_x and src_y == tgt_y);
    
    noc.nodes[src_x][src_y]->send(tgt_x, tgt_y, std::to_string(i));
  }
  
  sc_core::sc_start(100, sc_core::SC_NS);
  return 0;
}

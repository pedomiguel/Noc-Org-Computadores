#include "../include/top.hpp"
#include "sysc/kernel/sc_module.h"

#include <string>
#include <systemc.h>

Top::Top(sc_core::sc_module_name name, int size, Algorithm algorithm)
  : sc_module(name), n(size) {
  routers = new Router**[n];
  nodes = new Node**[n];
  links = new sc_core::sc_fifo<Package>[2*n*n + n*n*4 + 4*n];

  for(int i=0; i<n; ++i) {
    routers[i] = new Router*[n];
    nodes[i] = new Node*[n];

    for(int j=0; j<n; j++) {
        std::string router_name = "router_" + std::to_string(i) + std::to_string(j);
        routers[i][j] = new Router(router_name.c_str(), algorithm, i, j);

        std::string node_name = "node_" + std::to_string(i) + std::to_string(j);
        nodes[i][j] = new Node(node_name.c_str(), i, j);
    }
  }

  
  // connect router to node
  int global_link_cnt = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      nodes[i][j]->in_port(links[global_link_cnt]);
      routers[i][j]->out_ports[LOCAL](links[global_link_cnt]);
      global_link_cnt++;

      nodes[i][j]->out_port(links[global_link_cnt]);
      routers[i][j]->in_ports[LOCAL](links[global_link_cnt]);
      global_link_cnt++;
    }
  }

  // connect router to router
  for (int i = 0; i < n; ++i) {
    for(int j = 0; j < n; ++j) {
      routers[i][j]->in_ports[NORTH](links[global_link_cnt]);
      if(i > 0) routers[i-1][j]->out_ports[SOUTH](links[global_link_cnt]);
      global_link_cnt++;

      routers[i][j]->in_ports[EAST](links[global_link_cnt]);
      if(j < n-1) routers[i][j+1]->out_ports[WEST](links[global_link_cnt]);
      global_link_cnt++;
      
      routers[i][j]->in_ports[SOUTH](links[global_link_cnt]);
      if(i < n-1) routers[i+1][j]->out_ports[NORTH](links[global_link_cnt]);
      global_link_cnt++;

      routers[i][j]->in_ports[WEST](links[global_link_cnt]);
      if(j > 0) routers[i][j-1]->out_ports[EAST](links[global_link_cnt]);
      global_link_cnt++;
    }
  }

  for(int j=0; j<n; j++) {
    routers[0][j]->out_ports[NORTH](links[global_link_cnt]);
    global_link_cnt++;

    routers[n-1][j]->out_ports[SOUTH](links[global_link_cnt]);
    global_link_cnt++;

    routers[j][0]->out_ports[WEST](links[global_link_cnt]);
    global_link_cnt++;

    routers[j][n-1]->out_ports[EAST](links[global_link_cnt]);
    global_link_cnt++;
  }
}

Top::~Top() {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      delete routers[i][j];
      delete nodes[i][j];
    }
    delete [] routers[i];
    delete [] nodes[i];
  }
  delete [] nodes;
  delete [] routers;
  delete [] links;
}

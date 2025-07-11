#include "../include/router.hpp"

#include <systemc.h>


const char* number_to_port_name(int i) {
  std::string resp;
  switch(i){
    case EAST:
      resp = "EAST";
      break;
    case WEST:
      resp = "WEST";
      break;
    case NORTH:
      resp = "NORTH";
      break;
    case SOUTH:
      resp = "SOUTH";
      break;
    case LOCAL:
      resp = "LOCAL";
      break;
  }
  return resp.c_str();
}
Router::Router(sc_core::sc_module_name name, Algorithm algorithm, int _x, int _y)
: sc_module(name), algorithm(algorithm), x(_x), y(_y) {
  SC_THREAD(input_process);
  SC_THREAD(routing_process);
}

void Router::input_process() {
  while (true) {
    for (int i = 0; i < 5; ++i) {
      if (in_ports[i].num_available() > 0) {
        Package pkg = in_ports[i].read();
        buffers[i].write(pkg);
        printf("Router(%d, %d): Received package from port %s with data: %s\n", x, y, number_to_port_name(i), pkg.data.c_str());
      }
    }
    wait(1, sc_core::SC_NS);
  }
}

void Router::routing_process() {
  while (true) {
    for (int i = 0; i < 5; ++i) {
      if (buffers[i].num_available() > 0) {
        Package pkg = buffers[i].read();
        if (algorithm == Algorithm::XY) {
          route_xy(pkg);
        } else {
          route_west_first(pkg);
        }
      }
    }
    wait(1, sc_core::SC_NS);
  }
}


void Router::route_xy(Package& pkg) {
  if (pkg.dest_x > x && out_ports[SOUTH].num_free() > 0) {
    out_ports[SOUTH].write(pkg);
  } else if (pkg.dest_x < x && out_ports[NORTH].num_free() > 0) {
    out_ports[NORTH].write(pkg);
  } else if (pkg.dest_y > y && out_ports[EAST].num_free() > 0) {
    out_ports[EAST].write(pkg);
  } else if (pkg.dest_y < y && out_ports[WEST].num_free() > 0) {
    out_ports[WEST].write(pkg);
  } else if (pkg.dest_x == x && pkg.dest_y == y && out_ports[LOCAL].num_free() > 0) {
    out_ports[LOCAL].write(pkg);
  } else {
    buffers[LOCAL].write(pkg);
  }
}



void Router::route_west_first(Package& pkg) {
  if (pkg.dest_y < y && out_ports[WEST].num_free() > 0) {
    out_ports[WEST].write(pkg);
  } else {
    if (pkg.dest_x < x && out_ports[NORTH].num_free() > 0) {
      out_ports[NORTH].write(pkg);
    } else if (pkg.dest_x > x && out_ports[SOUTH].num_free() > 0) {
      out_ports[SOUTH].write(pkg);
    } else if (pkg.dest_y > y && out_ports[EAST].num_free() > 0) {
      out_ports[EAST].write(pkg);
    } else if (pkg.dest_x == x && pkg.dest_y == y && out_ports[LOCAL].num_free() > 0) {
      out_ports[LOCAL].write(pkg);
    } else {
      buffers[LOCAL].write(pkg);
    }
  }
}


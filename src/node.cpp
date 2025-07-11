#include "../include/node.hpp"

Node::Node(sc_core::sc_module_name name, int _x, int _y): sc_module(name), x(_x), y(_y) {
    SC_THREAD(read);
}

void Node::read() {
    while(true) {
        wait(1, SC_NS);
        Package p = in_port.read();
        printf("Node(%d, %d): Received package from (%d, %d) with data: %s\n", x, y, p.src_x, p.src_y, p.data.c_str());
    }
}

void Node::send(int to_x, int to_y, std::string data) {
    Package p(x, y, to_x, to_y, data);
    out_port.write(p);
    printf("Node(%d, %d): Sending package to (%d, %d) with data: %s\n", x, y, to_x, to_y, p.data.c_str());
}
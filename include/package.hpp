#include <ostream>
#include <string>

#ifndef PACKAGE_HPP
#define PACKAGE_HPP

struct Package {
  int src_x, src_y;
  int dest_x, dest_y;
  std::string data;

  Package(int _src_x, int _src_y, int _dest_x, int _dest_y, std::string _data):
    src_x(_src_x),
    src_y(_src_y),
    dest_x(_dest_x),
    dest_y(_dest_y),
    data(_data) {};

  Package() {}
};

inline std::ostream& operator<<(std::ostream& os, const Package& p) {
    os << "[src=(" << p.src_x << "," << p.src_y
      << ") dest=(" << p.dest_x << "," << p.dest_y
      << ") data=" << p.data << "]";
    return os;
  }

#endif

#include <ostream>
#include <string>

#ifndef PACKAGE_HPP
#define PACKAGE_HPP

struct Package {
  int src_x, src_y;
  int dest_x, dest_y;
  std::string data;
};

inline std::ostream& operator<<(std::ostream& os, const Package& p) {
    os << "[src=(" << p.src_x << "," << p.src_y
      << ") dest=(" << p.dest_x << "," << p.dest_y
      << ") data=" << p.data << "]";
    return os;
  }

#endif

#include "reader.hpp"

#include <cmath>

num_t safe_read(std::istream &in, num_t exp) {
  double tmp = HUGE_VAL;
  in >> tmp;
  if(tmp == HUGE_VAL) {
    throw true;
  }
  return tmp * std::pow(10, exp);
}

void read_pset(pset &set, std::istream &in, num_t exp) {
  point p;
  while(!in.eof()) {
    try {
      p.x = safe_read(in, exp);
      p.y = safe_read(in, exp);
      set.push_back(p);
    } catch(...) {
      break;
    }
  }
}


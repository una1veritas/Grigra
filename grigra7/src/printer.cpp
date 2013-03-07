#include "printer.hpp"

#include <cmath>

const char *pset_raw_delimiter = " ";
const char *pset_col_delimiter = "";

void print_num(std::ostream &out, num_t a, num_t exp) {
  if(!exp) {
    out << a / (double)std::pow(10, exp);
  } else {
    out << a;
  }
}

void print_pset(pset &set, std::ostream &out, num_t exp) {
  for(pset::iterator i = set.begin(); i != set.end(); ++i) {
    print_num(out, i->x, exp);
    out << pset_raw_delimiter;
    print_num(out, i->y, exp);
    out << pset_col_delimiter << std::endl;
  }
}

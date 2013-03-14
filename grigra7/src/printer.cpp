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


bool check_overlap(pset &set, std::ostream &err) {
  bool check = false;
  for(pset::iterator i = set.begin(); i != set.end(); ++i) {
    for(pset::iterator j = i+1; j != set.end(); ++j) {
      if(*i == *j) {
        err << "Overlap! : " << i->x << " " << i->y << std::endl;
        check = true;
      }
    }
  }
  return check;
}

bool check_gridded(pset &set, num_t g, std::ostream &err) {
  bool check = false;
  for(pset::iterator i = set.begin(); i != set.end(); ++i) {
    if(i->x % g != 0 && i->y % g != 0) {
      err << "Not on Grid! : " << i->x << " " << i->y << std::endl;
      check = true;
    }
  }
  return check;
}

void check_gridlayout_successed(pset &set, num_t g, std::ostream &err) {
  check_overlap(set, err);
  check_gridded(set, g, err);
}


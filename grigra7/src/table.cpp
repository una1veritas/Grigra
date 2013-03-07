#include "table.hpp"

#include <algorithm>

void init_ilist(ilist &ilst, pset &set) {
  ilst.clear();
  ilst.resize(set.size());
  for(size_t i=0; i<set.size(); ++i) {
    ilst[i] = i;
  }
}

class compare_xy {
  pset &set;
public:
  compare_xy(pset &set) : set(set) {}
  bool operator () (const size_t &a, const size_t &b) {
    return set[a].lt_xy(set[b]);
  }
};

class compare_yx {
  pset &set;
public:
  compare_yx(pset &set) : set(set) {}
  bool operator () (const size_t &a, const size_t &b) {
    return set[a].lt_yx(set[b]);
  }
};

void sort_xy(ilist &ilist, pset &set) {
  std::sort(ilist.begin(), ilist.end(), compare_xy(set));
}

void sort_yx(ilist &ilist, pset &set) {
  std::sort(ilist.begin(), ilist.end(), compare_yx(set));
}


ttable::ttable(size_t size) : length(size), dat(NULL) {
  dat = new point[size * size];
  fill(point());
}

ttable::~ttable() {
  if(dat) delete[] dat;
}

size_t ttable::size() {
  return length;
}

void ttable::fill(point p) {
  for(size_t i=0; i<length; ++i) {
    for(size_t j=0; j<length; ++j) {
      ref(i,j) = p;
    }
  }
}

point &ttable::ref(size_t i, size_t j) {
  if(length <= i) throw true;
  if(length <= j) throw true;
  return dat[i + j * length];
}


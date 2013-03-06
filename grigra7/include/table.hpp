#ifndef TABLE_HPP
#define TABLE_HPP

#include "point.h"

// Index List
struct ilist {
  size_t *dat, length;

  ilist(pset &set);
  ~ilist();

  void sort_xy();
  void sort_yx();

  size_t ref(size_t i);
};

// Translation Table
struct ttable {
  point *dat;
  size_t length;

  ttable(size_t size);
  ~ttable();

  void fill(point p);
  point &ref(size_t i, size_t j);
};

#endif

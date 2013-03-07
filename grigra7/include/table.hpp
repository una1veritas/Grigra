#ifndef TABLE_HPP
#define TABLE_HPP

#include "point.hpp"

// 添え字配列
typedef std::vector<size_t> ilist;
void init_ilist(ilist &ilst, pset &set);
void sort_xy(ilist &ilst, pset &set);
void sort_yx(ilist &ilst, pset &set);

// 添え字外を示す定数
const size_t OUT_OF_INDEX = (size_t)-1;
inline bool is_right_index(size_t i) { return i != OUT_OF_INDEX; }

// Translation Table
class ttable {
  size_t length;
  point *dat;
public:
  ttable(size_t size);
  ~ttable();

  size_t size();

  void fill(point p);
  point &ref(size_t i, size_t j);
};

#endif

#ifndef POINT_HPP
#define POINT_HPP

// C++0x未満の標準仕様では intXX_t は存在しない(cstdintがない)
// 可搬性高く記述しようとすると、boostライブラリを使用する必要があるが、
// 今回は面倒なので却下
// 代用案としてC99標準規格の stdint.h を利用する
// よってこのコンパイル環境にはC99以上を要求する
#include <stdint.h>

#include <cmath>
#include <set>

typedef int32_t elem_t;

struct point {
  elem_t x, y;

  point();
  point(elem_t x, elem_t y);
  point(const point &p);
  ~point();

  point right_top(point p);
  elem_t length() const;

  bool operator == (point &p);
  point &operator = (point &p);
  point operator + (point p);
  point operator - (point p);
  point &operator += (point p);
  point &operator -= (point p);
};

typedef std::set<point> pset;

#endif


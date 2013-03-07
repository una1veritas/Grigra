#ifndef POINT_HPP
#define POINT_HPP

// C++0x未満の標準仕様では intXX_t は存在しない(cstdintがない)
// 可搬性高く記述しようとすると、boostライブラリを使用する必要があるが、
// 今回は面倒なので却下
// 代用案としてC99標準規格の stdint.h を利用する
// よってこのコンパイル環境にはC99以上を要求する
#include <stdint.h>

#include <cmath>
#include <vector>
#include <cstdlib>

// 点の成分の型
typedef int32_t num_t;

// 点クラス
struct point {
  num_t x, y;

  point();
  point(num_t x, num_t y);
  point(const point &p);
  ~point();

  point right_top(point p);
  num_t length() const;

  // xy, yx方向の比較演算(<)
  bool lt_xy(point &q);
  bool lt_yx(point &q);

  bool operator == (point &p);
  bool operator != (point &p);

  point &operator = (point &p);
  point operator + (point p);
  point operator - (point p);
  point &operator += (point p);
  point &operator -= (point p);
};

// 点集合クラス
typedef std::vector<point> pset;

#endif


#ifndef GRID_LAYOUT_TABLE_H
#define GRID_LAYOUT_TABLE_H

/* <encode : utf-8>

  点ソート列のデータ構造PointSequenceと、
  テーブル用データ構造Gridの定義。

*/

#include "pointset.h"
using namespace gridlayout;

template<typename TYPE>
class compare_XY {
  PointSet<TYPE> &set;
public:
  compare_XY(PointSet<TYPE> &set) : set(set) {}
  bool operator ()(const TYPE &a, const TYPE &b) const {
    return set[a].getX() == set[b].getX()
             ? set[a].getY() < set[b].getY()
             : set[a].getX() < set[b].getX();
  }
};

template<typename TYPE>
class compare_YX {
  PointSet<TYPE> &set;
public:
  compare_YX(PointSet<TYPE> &set) : set(set) {}
  bool operator ()(const TYPE &a, const TYPE &b) const {
    return set[a].getY() == set[b].getY()
             ? set[a].getX() < set[b].getX()
             : set[a].getY() < set[b].getY();
  }
};

template<typename TYPE>
class PointSequence : public std::vector<size_t> {

  // Internal Type
  typedef std::vector<size_t> super;
  typedef typename super::iterator iterator;

  // Field
  PointSet<TYPE> &set;

public:
  ~PointSequence() {}
  
  PointSequence(PointSet<TYPE> &set, bool sortx) : super(set.size()), set(set) {
    size_t j=0;
    for(iterator i = super::begin(); i != super::end(); ++i) {
      *i = j++;
    }

    if(sortx) {
      std::sort(super::begin(), super::end(), compare_XY<TYPE>(set));
    } else {
      std::sort(super::begin(), super::end(), compare_YX<TYPE>(set));
    }
  }
  
  Point<TYPE> &ref(size_t i) {
    return set.at(at(i));
  }
  
  void print(std::ostream &out) {
    for(iterator i = super::begin(); i != super::end(); ++i) {
      out << *i << " : " << set[*i] << std::endl;
    }
  }

};

template<typename TYPE>
std::ostream &operator <<(std::ostream &out, PointSequence<TYPE> &p) {
  p.print(out);
  return out;
}

template <typename TYPE>
class grid : public std::vector<TYPE> {
  
  // Internal Type
  typedef std::vector<TYPE> super;
  typedef typename super::iterator iterator;
  
  // Field
  size_t width;

public:
  ~grid() {}

  grid() : super(), width(0) {}
  
  grid(size_t size) : super(size * size), width(size) {}
  
  TYPE &ref(size_t x, size_t y) {
    return super::at(x + y * width);
  }
  
  void print(std::ostream &out) {
    size_t j=0;
    for(iterator i = super::begin(); i != super::end(); i++) {
      out << " " << *i << "|";
      if(++j % width == 0) out << std::endl;
    }
  }

};

template<typename TYPE>
std::ostream &operator <<(std::ostream &out, grid<TYPE> &p) {
  p.print(out);
  return out;
}

#endif

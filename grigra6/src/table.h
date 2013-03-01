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
    if(set[a].getX() == set[b].getX()) {
      return set[a].getY() < set[b].getY();
    }
    return set[a].getX() < set[b].getX();
  }
};

template<typename TYPE>
class compare_YX {
  PointSet<TYPE> &set;
public:
  compare_YX(PointSet<TYPE> &set) : set(set) {}
    
  bool operator ()(const TYPE &a, const TYPE &b) const {
    if(set[a].getY() == set[b].getY()) {
      return set[a].getX() < set[b].getX();
    }
    return set[a].getY() < set[b].getY();
  }
};

template<typename TYPE>
class PointSequence : public std::vector<int> {
  typedef typename std::vector<int>::iterator iterator;
  PointSet<TYPE> &set;
public:
  ~PointSequence() {}
  
  PointSequence(PointSet<TYPE> &set, bool sortx)
  : std::vector<int>(set.size()), set(set) {
    int j=0;
    for(iterator i=std::vector<int>::begin(); i!=std::vector<int>::end(); ++i) {
      *i = j++;
    }
    
    if(sortx) {
      std::sort(std::vector<int>::begin(),
                std::vector<int>::end(),
                compare_XY<TYPE>(set));
    } else {
      std::sort(std::vector<int>::begin(),
                std::vector<int>::end(),
                compare_YX<TYPE>(set));
    }
  }
  
  Point<TYPE> &ref(int i) {
    return set.at(at(i));
  }
  
  void print(std::ostream &out) {
    for(iterator i=std::vector<int>::begin(); i!=std::vector<int>::end(); ++i) {
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
  typedef typename std::vector<TYPE>::iterator iterator;
  
  int grid_size;
public:
  grid() : std::vector<TYPE>(), grid_size(0) {}
  
  grid(int size) : std::vector<TYPE>(size*size), grid_size(size) {}
  
  TYPE &ref(int x, int y) {
    return std::vector<TYPE>::at(x + y * grid_size);
  }
  
  void print(std::ostream &out) {
    int j=0;
    for(iterator i=std::vector<TYPE>::begin(); i!=std::vector<TYPE>::end(); i++) {
      out << " " << *i << "|";
      if(++j % grid_size == 0) {
        out << std::endl;
      }
    }
  }
};

template<typename TYPE>
std::ostream &operator <<(std::ostream &out, grid<TYPE> &p) {
  p.print(out);
  return out;
}

#endif

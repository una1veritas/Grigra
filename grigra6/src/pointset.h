#ifndef GRID_LAYOUT_POINT_SET_H
#define GRID_LAYOUT_POINT_SET_H

/* <encode : utf-8>

  PointSetテンプレートクラスの定義。

*/

#include "point.h"

namespace gridlayout {
  template<typename TYPE>
  class PointSet : public std::vector<Point<TYPE> > {
    typedef Point<TYPE> POINT_T;
    typedef typename std::vector<POINT_T>::iterator iterator;
  public:
    PointSet() : std::vector<POINT_T>() {}
    ~PointSet() {}
    
    PointSet(std::istream &in) : std::vector<POINT_T>() {
      TYPE x, y;
      in >> x;
      in >> y;
      while(!in.eof()) {
        std::vector<POINT_T>::push_back(POINT_T(x,y));
        in >> x;
        in >> y;
      }
    }

    PointSet(PointSet &set) : std::vector<POINT_T>(set.size()) {
      for(int i=0; i<set.size(); ++i) {
        std::vector<POINT_T>::at(i) = set[i];
      }
    }
    
    PointSet(int size) : std::vector<POINT_T>(size) {}
    void print(std::ostream &out) {
      for(iterator i = std::vector<POINT_T>::begin();
          i != std::vector<POINT_T>::end();
          i++)
      {
        i->print(out);
        out << std::endl;
      }
    }
    
    PointSet(const TYPE *array, const size_t maxlen) : std::vector<POINT_T>(maxlen) {
      for(size_t i=0; i<maxlen; i+=2)
      {
        std::vector<POINT_T>::at(i).setX(array[i]);
        std::vector<POINT_T>::at(i+1).setY(array[i+1]);
      }
    }
    
    bool checkIndependent() {
      bool check = true;
      for(int i = 0; i < std::vector<POINT_T>::size(); i++) {
        for(int j = i; j < std::vector<POINT_T>::size(); j++) {
          if(!(i==j) && (std::vector<POINT_T>::at(i) == std::vector<POINT_T>::at(j))) {
            std::cerr << "ERROR : GRID-LAYOUT FAILED." << std::endl;
            std::cerr << i << " : " << std::vector<POINT_T>::at(i) << " | "
                      << j << " : " << std::vector<POINT_T>::at(j) << std::endl;
            check = false;
          }
        }
      }
      return check;
    }
    
    PointSet &operator=(PointSet &set) {
      for(int i=0; i<std::vector<POINT_T>::size(); ++i) {
        std::vector<POINT_T>::at(i) = set[i];
      }
      return *this;
    }
  };

  template<typename TYPE>
  std::ostream &operator <<(std::ostream &out, PointSet<TYPE> &p) {
    p.print(out);
    return out;
  }
}

#endif

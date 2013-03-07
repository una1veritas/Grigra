#ifndef GRID_LAYOUT_POINT_SET_H
#define GRID_LAYOUT_POINT_SET_H

/* <encode : utf-8>

  PointSetテンプレートクラスの定義。

*/

#include "point.h"

namespace gridlayout {
  template<typename TYPE>
  class PointSet : public std::vector<Point<TYPE> > {

    // Internal Type
    typedef std::vector<Point<TYPE> > super;
    typedef Point<TYPE> POINT_T;
    typedef typename super::iterator iterator;

  public:
    PointSet() : super() {}
    ~PointSet() {}
    
    PointSet(std::istream &in) : super() {
      TYPE x, y;
      in >> x;
      in >> y;
      while(!in.eof()) {
        super::push_back(POINT_T(x,y));
        in >> x;
        in >> y;
      }
    }

    PointSet(PointSet &set) : super(set.size()) {
      for(size_t i=0; i<set.size(); ++i) {
        super::at(i) = set[i];
      }
    }
    
    PointSet(size_t size) : super(size) {}
    void print(std::ostream &out) {
      for(iterator i = super::begin(); i != super::end(); i++) {
        i->print(out);
        out << std::endl;
      }
    }
    
    PointSet(const TYPE *array, const size_t maxlen) : super(maxlen) {
      for(size_t i=0; i < maxlen; i+=2) {
        super::at(i).setX(array[i]);
        super::at(i+1).setY(array[i+1]);
      }
    }
    
    bool checkIndependent() {
      bool check = true;
      for(size_t i = 0; i < super::size(); i++) {
        for(size_t j = i; j < super::size(); j++) {
          if(!(i==j) && (super::at(i) == super::at(j))) {
            std::cerr << "CHECK-INDEPENDENT ERROR : NO GRID-LAYOUTED." << std::endl;
            std::cerr << i << " : " << super::at(i) << " | "
                      << j << " : " << super::at(j) << std::endl;
            check = false;
          }
        }
      }
      return check;
    }
    
    PointSet &operator=(PointSet &set) {
      for(size_t i=0; i < super::size(); ++i) {
        super::at(i) = set[i];
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

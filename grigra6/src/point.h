#ifndef GRID_LAYOUT_POINT_H
#define GRID_LAYOUT_POINT_H

/* <encode : utf-8>

  Pointテンプレートクラスの定義と、
  重複点情報の計算用の関数。

*/

#include "misc.h"

template<typename TYPE>
class Point {
  TYPE x, y;

  inline TYPE calc_u(TYPE a, int grid) {
    return modulo<TYPE>(std::abs(a), (TYPE)grid) * (a > 0 ? -1 : 1);
  }
  
  inline TYPE calc_v(TYPE a, TYPE u, int grid) {
    return (grid - std::abs(u)) * (a > 0 ? 1 : -1); 
  }

  inline TYPE ifswap(TYPE v, TYPE a, TYPE b) {
    return (v == a) ? b : a;
  }

public:

  inline Point rightTop(Point b) {
    return Point(std::max(x, b.x), std::max(y, b.y));
  }

  Point() : x(0), y(0) {}
  Point(TYPE x, TYPE y) : x(x), y(y) {}
  Point(const Point &p) : x(p.x), y(p.y) {}
  ~Point() {}
  TYPE getX () const { return x ; }
  TYPE getY () const { return y ; }
  void setX (TYPE x) { this-> x = x; }
  void setY (TYPE y) { this-> y = y; }
  Point trans(Point px, Point py, int grid) {
    Point rt = px.rightTop(py);
    Point t(*this - rt);

    TYPE ux = calc_u(t.x, grid), vx = calc_v(t.x, ux, grid);
    TYPE uy = calc_u(t.y, grid), vy = calc_v(t.y, uy, grid);
    
    px = px - rt;
    py = py - rt;
    
    Point r = Point(ux,uy);
    r.y = std::abs(uy) < std::abs(vy) ? uy : vy;
    r.x = std::abs(ux) < std::abs(vx) ? ux : vx;
    
    Point tmp = t + r;
    if(tmp.x == 0) {
      r.x = ifswap(r.x, ux, vx);
      if(t.x == 0) r.x = grid;
    } else if(tmp.y == 0) {
      r.y = ifswap(r.y, uy, vy);
      if(t.y == 0) r.y = grid;
    } else if(tmp.x < 0 && tmp.y < 0) {
      if(t.x >= 0) {
        r.x = ifswap(r.x, ux, vx);
      } else if(t.y >= 0) {
        r.y = ifswap(r.y, uy, vy);
      }
    }
    
    return r;
  }
  TYPE sum() const { return x + y; }
  TYPE length() const { return std::abs(x) + std::abs(y); }
  bool is_zero() const { return x == 0 && y == 0; }
  bool operator ==(Point &p) { return (x == p.x) && (y == p.y); }
  Point &operator =(Point p) { x=p.x; y=p.y; return *this; }
  Point operator +(Point p) { Point q(x + p.x, y + p.y); return q; }
  Point &operator +=(Point p) { x += p.x; y += p.y; return *this; }
  Point &operator -=(Point p) { x -= p.x; y -= p.y; return *this; }
  Point operator -(Point &p) { Point q(x - p.x, y - p.y); return q; }
  void print(std::ostream &out) { out << x << " " << y; }
};

template<typename TYPE>
std::ostream &operator <<(std::ostream &out, Point<TYPE> &p) {
  p.print(out);
  return out;
}

template<typename TYPE>
Point<TYPE> rectMultiPoints(int n, TYPE grid_size) {
  if(n <= 1) {
    return Point<TYPE>(0,0);
  }
  int ix = 0, iy = 0;
  for(int j=1,k=1; j<n; ++ix, k += 2, j += k);
  for(int j=2,k=2; j<n; ++iy, k += 2, j += k);
  return Point<TYPE>(ix * grid_size, iy * grid_size);
}

template<typename TYPE>
TYPE sumMultiPointsDistance(int n, TYPE grid_size) {
  return rectMultiPoints(n, grid_size).length();
}

#endif

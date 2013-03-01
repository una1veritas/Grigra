#ifndef GRID_LAYOUT_MAN_H
#define GRID_LAYOUT_MAN_H

/* <encode : utf-8>

  グリッドレイアウトアルゴリズムの実装。

*/

#include "table.h"
using namespace gridlayout;

namespace {
  template <typename TYPE>
  class GridLayoutMan {
    typedef Point<TYPE> POINT_T;
    typedef PointSet<TYPE> PSET_T;
    typedef PointSequence<TYPE> PSEQ_T;
    typedef std::vector< std::list< Point<int> > > RDIC_T;
    enum DIRECTION_T {
      MISS = 0,
      RIGHT = 1,
      TOP = 2,
      RIGHT_TOP = 3
    };
    enum SQUARE_T {
      NONE = 0,
      SINGLE = 1,
      DOUBLE = 2
    };

    TYPE grid_size; 

    int checkPointPair(int i, int j, PSEQ_T &x, PSEQ_T &y) {
      POINT_T &p = x.ref(i), &q = y.ref(j);
      if(p == q) {
        return SINGLE;
      }
      if(p.getX() >= q.getX() && p.getY() <= q.getY()) {
        return DOUBLE;
      }
      return NONE;
    }
    
    bool checkMultiPoints(int i, PSEQ_T &s) {
      if(i+1 < s.size() && s.ref(i) == s.ref(i+1)) {
        return true;
      }
      if(0 <= i-1 && s.ref(i) == s.ref(i-1)) {
        return true;
      }
      return false;
    }
    
    int rewindMultiPoints(int i, PSEQ_T &s) {
      while(0 <= i-1 && s.ref(i) == s.ref(i-1)) {
        --i;
      }
      return i;
    }
    
    int multiPointsLen(int i, PSEQ_T &s) {
      int j = i;
      while(j+1 < s.size() && s.ref(i) == s.ref(j)) {
        ++j;
      }
      return j - i;
    }
    
    POINT_T rectPush(POINT_T p, POINT_T rt) {
      POINT_T q = p.rightTop(rt) - rt;
      return q;
    }
    
    void undiplicate(PSET_T &set, PSEQ_T &x, PSEQ_T &y) {
      TYPE prev, bias;
      prev = x.ref(0).getX();
      bias = 0;
      for(int i=1; i<set.size(); ++i) {
        if(x.ref(i).getX() + bias <= prev) {
          bias += grid_size;
        }
        x.ref(i).setX(x.ref(i).getX() + bias);
        prev = x.ref(i).getX();
      }
      prev = y.ref(0).getY();
      bias = 0;
      for(int i=1; i<set.size(); ++i) {
        if(y.ref(i).getY() + bias <= prev) {
          bias += grid_size;
        }
        y.ref(i).setY(y.ref(i).getY() + bias);
        prev = y.ref(i).getY();
      }
    }
    
    int prevX(int ix, int iy, PSEQ_T &x, PSEQ_T &y) {
      TYPE t = y.ref(iy).getY();
      TYPE u = y.ref(iy).getX();
      do {
        if(ix <= 0) {
          return -1;
        }
      } while(t < x.ref(--ix).getY()
              || (t == x.ref(ix).getY() && u < x.ref(ix).getX()));
      return ix;
    }
    
    int prevY(int ix, int iy, PSEQ_T &x, PSEQ_T &y) {
      TYPE t = x.ref(ix).getX();
      TYPE u = x.ref(ix).getY();
      do {
        if(iy <= 0) {
          return -1;
        }
      } while(t < y.ref(--iy).getX()
              || (t == y.ref(iy).getX() && u < y.ref(iy).getY()));
      return iy;
    }
    
    void listCountRects(PSET_T &set, PSEQ_T &x, PSEQ_T &y) {
      grid<int> cr(set.size());
      RDIC_T rd(set.size());
      int pi, pj, v;
      for(unsigned int i=0; i<set.size(); ++i) {
        for(unsigned int j=0; j<set.size(); ++j) {
          if(i != rewindMultiPoints(i, x)) {
            continue;
          }
          if(j != rewindMultiPoints(j, y)) {
            continue;
          }
          if(!checkPointPair(i,j,x,y)) {
            continue;
          }
          pi = prevX(i,j,x,y);
          pi = rewindMultiPoints(pi, x);
          v = pi < 0 ? 0 : cr.ref(pi, j);
          rd[v+1].push_back(Point<int>(i,j));
          cr.ref(i,j) = v+1;
        }
      }
      calcTranslateTable(set, x, y, rd);
    }
    
    void calcTranslateTable(PSET_T &set, PSEQ_T &x, PSEQ_T &y, RDIC_T &rd) {
      grid<POINT_T> pt(set.size()), tt(set.size());
      grid<int> dir(set.size());
      int i, j, pi, pj;
      bool multix, multiy;
      TYPE mxlen, mylen;
      POINT_T rt, art, brt, a, b, pa, pb, ta, tb;
      for(RDIC_T::iterator u = rd.begin(); u != rd.end(); ++u) {
        for(RDIC_T::value_type::iterator v = u->begin(); v != u->end(); ++v) {
          i = v->getX();
          j = v->getY();
          i = rewindMultiPoints(i, x);
          j = rewindMultiPoints(j, y);
          pi = prevX(i,j,x,y);
          pj = prevY(i,j,x,y);
          pi = rewindMultiPoints(pi, x);
          pj = rewindMultiPoints(pj, y);
          switch(checkPointPair(i,j,x,y)) {
            case SINGLE : {
              art = pi < 0 ? POINT_T(0,0) : x.ref(pi);
              art = art.rightTop(pj < 0 ? POINT_T(0,0) : y.ref(pj));

              a = x.ref(i).trans(pi < 0 ? POINT_T(0,0) : x.ref(pi),
                                 pj < 0 ? POINT_T(0,0) : y.ref(pj),
                                 grid_size);
              ta = rectPush(x.ref(i) + a + rectMultiPoints(multiPointsLen(i,x), grid_size), art)
                 + (pi < 0 || pj < 0 ? POINT_T(0,0) : tt.ref(pi, pj)); 
              pa = a - art;

              tt.ref(i,j) = ta;
              pt.ref(i,j) = pa;
              dir.ref(i,j) = RIGHT_TOP;
            } break;
            case DOUBLE : {
              art = x.ref(pi).rightTop(y.ref(j));
              a = x.ref(i).trans(x.ref(pi), y.ref(j), grid_size);
              ta = rectPush(x.ref(i) + a + rectMultiPoints(multiPointsLen(i,x), grid_size), art)
                 + tt.ref(pi, j);
              pa = a - art;
              
              brt = x.ref(i).rightTop(y.ref(pj));
              b = y.ref(j).trans(x.ref(i), y.ref(pj), grid_size);
              tb = rectPush(y.ref(j) + b + rectMultiPoints(multiPointsLen(j,y), grid_size), brt)
                 + tt.ref(i, pj);
              pb = b - brt;
              
              if(ta.length() < tb.length()) {
                tt.ref(i,j) = ta;
                pt.ref(i,j) = pa;
                dir.ref(i,j) = RIGHT;
              } else {
                tt.ref(i,j) = tb;
                pt.ref(i,j) = pb;
                dir.ref(i,j) = TOP;
              }
            } break;
          }
        }
      }

      applyLayout(set,x,y,tt,pt,dir);
    }

    void applyTranslate(PSET_T &tmp, std::list<int> &ap, PSEQ_T &s, int i, POINT_T &trans) {
      tmp[s[i]] += trans;
      ap.push_front(s[i]);
      int it = i+1, rb = 1, tb = 1, rc = 1, tc = 0, l = multiPointsLen(it,s);
      POINT_T rect = rectMultiPoints<TYPE>(l, grid_size);
      while((it - i <= l) && s.ref(i) == s.ref(it)) {
        tmp[s[it]] = POINT_T(rc * grid_size, tc * grid_size);
        ap.push_front(s[it]);
        if(tc == tb) {
          if(rc == 0) {
            ++rb;
            ++tb;
            rc = rb;
            tc = 0;
          } else {
            --rc;
          }
        } else {
          ++tc;
        }
        ++it;
      }
    }
    
    void applyLayout(PSET_T &set, PSEQ_T &x, PSEQ_T &y, grid<POINT_T> &tt, grid<POINT_T> &pt, grid<int> &dir) {
      bool multix, multiy;
      int ix = set.size()-1, iy = set.size()-1, px = 0, py = 0;
      POINT_T trans, maximum = tt.ref(ix, iy);
      PSET_T tmp(set);
      std::list<int> ap;

      // Calc Rectangle List.
      while(ix >= 0 && iy >= 0) {
        multix = checkMultiPoints(ix, x);
        multiy = checkMultiPoints(iy, y);
        ix = rewindMultiPoints(ix, x);
        iy = rewindMultiPoints(iy, y);
        if(!dir.ref(ix,iy)) {
          std::cerr << "APPLY FAILEDED at " << ix << " " << iy << std::endl;
          std::cerr << x.ref(px) << " " << y.ref(py) << std::endl;
          std::cerr << tt.ref(ix, iy) << " : " << x[ix] << " " << y[iy] << std::endl;
          return;
        }
        trans = pt.ref(ix, iy);
        px = prevX(ix,iy,x,y);
        py = prevY(ix,iy,x,y);
        px = rewindMultiPoints(px, x);
        py = rewindMultiPoints(py, y);
        switch(checkPointPair(ix,iy,x,y)) {
          case SINGLE : {
            applyTranslate(tmp, ap, x, ix, trans);
            ix=px;
            iy=py;
          } break;
          case DOUBLE : {
            if(dir.ref(ix,iy) != TOP) {
              applyTranslate(tmp, ap, x, ix, trans);
              ix=px;
            } else {
              applyTranslate(tmp, ap, y, iy, trans);
              iy=py;
            }
          } break;
        }
      }

      // Apply Layout
      POINT_T rt(0, 0);
      for(typename std::list<int>::iterator i = ap.begin();
          i != ap.end();)
      {
        tmp[*i] += rt;
        POINT_T o = tmp[*i];
        int n = 1, pi = *i;
        ++i;
        while(set[pi] == set[*i]) {
          tmp[*i] += o;
          ++n;
          pi = *i; ++i;
          if(i == ap.end()) break;
        }
        o += rectMultiPoints(n, grid_size);
        rt = rt.rightTop(o);
      }

      set = tmp;
    }

    void foldLayout(PSET_T &set) {
      PSEQ_T x(set, true), y(set, false);
      //undiplicate(set, x, y);
      for(int i=1; i<x.size(); ++i)
      {
        if( (x.ref(i).getX() == x.ref(i-1).getX() + grid_size) &&
            (x.ref(i).getY() > x.ref(i-1).getY()) )
        {
          for(int j=i; j<x.size(); ++j) {
            x.ref(j) += POINT_T(-grid_size, 0);
          }
        }
      }
      for(int i=1; i<y.size(); ++i)
      {
        if( (y.ref(i).getY() == y.ref(i-1).getY() + grid_size) &&
            (y.ref(i).getX() > y.ref(i-1).getX()) )
        {
          for(int j=i; j<y.size(); ++j) {
            y.ref(j) += POINT_T(0, -grid_size);
          }
        }
      }
    }
  public:
    GridLayoutMan(int grid_size) : grid_size(grid_size) {}
    ~GridLayoutMan() {}
    
    PSET_T &match(PSET_T &p) {
      PSEQ_T sortx(p, true), sorty(p, false);
      listCountRects(p, sortx, sorty);
      //foldLayout(p);
      return p;
    }
    
    bool checkMatch(PSET_T &p) {
      for(int i=0; i<p.size(); ++i) {
        if(p[i].getX() % grid_size != 0 || p[i].getY() % grid_size != 0) {
          return false;
        }
      }
      return true;
    }
  };
}

#endif

#include "layout.hpp"

#include <iostream>

bool is_multipoint_leader(size_t i, ilist &a, pset &set) {
  if(!is_right_index(i))
    return false;
  if(0 < i && set[a[i]] == set[a[i-1]])
    return false;
  return true;
}

size_t rewind_multipoint(size_t i, ilist &a, pset &set) {
  if(!is_right_index(i)) return i;
  while(0 < i && set[a[i]] == set[a[i-1]]) --i;
  return i;
}

size_t size_corner(point &p, point &q) {
  return p == q ? 1 : p.x >= q.x && p.y <= q.y ? 2 : 0;
}

size_t prev_xy(size_t i, size_t j, ilist &xy, ilist &yx, pset &set) {
  if(!is_right_index(i)) return OUT_OF_INDEX;
  if(!is_right_index(j)) return OUT_OF_INDEX;
  
  // <yx を満たす xy 方向の最も右の点を探索する
  point p = set[yx[j]];
  do if(i <= 0) return OUT_OF_INDEX;
    while(p.lt_yx(set[xy[--i]]));

  // 重複点の代表点まで巻き戻す
  return rewind_multipoint(i, xy, set);
}

size_t prev_yx(size_t i, size_t j, ilist &xy, ilist &yx, pset &set) {
  if(!is_right_index(i)) return OUT_OF_INDEX;
  if(!is_right_index(j)) return OUT_OF_INDEX;
  
  // <xy を満たす yx 方向の最も上の点を探索する
  point p = set[xy[i]];
  do if(j <= 0) return OUT_OF_INDEX;
    while(p.lt_xy(set[yx[--j]]));

  // 重複点の代表点まで巻き戻す
  return rewind_multipoint(j, yx, set);
}

inline num_t calc_u(num_t a, num_t g) {
  return (std::abs(a) % g) * (a > 0 ? -1 : 1);
}

inline num_t calc_v(num_t a, num_t u, num_t g) {
  return (g - std::abs(u)) * (a > 0 ? 1 : -1);
}

inline num_t ifswap(num_t x, num_t a, num_t b) {
  return (x == a) ? b : a;
}

point trans(point p, point rt, num_t g, point sumt) {
  point t = p - rt;
  
  // 各軸毎の隣接するグリッド線2本との距離を求める
  num_t ux = calc_u(t.x, g), vx = calc_v(t.x, ux, g);
  num_t uy = calc_u(t.y, g), vy = calc_v(t.y, uy, g);

  // 距離が最も小さい組み合わせを選ぶ
  point r = point( std::abs(ux) < std::abs(vx) ? ux : vx,
                   std::abs(uy) < std::abs(vy) ? uy : vy );

  // 右上角の内側に突入する編集を反転させる
  point tmp = t + r;
  if(tmp.x == 0)
    r.x = t.x != 0 ? ifswap(r.x, ux, vx) : g;
  else if(tmp.y == 0)
    r.y = t.y != 0 ? ifswap(r.y, uy, vy) : g;
  else if(tmp.x < 0 && tmp.y < 0) {
    if(t.x >= 0)
      r.x = ifswap(r.x, ux, vx);
    else if(t.y >= 0)
      r.y = ifswap(r.y, uy, vy);
  }

  // 編集距離を返す
  return r;
}

point sum_transrect(point p, size_t pi, size_t pj, ttable &tt, size_t g, ilist &xy, ilist &yx, pset &set, point *pout) {
  point r = is_right_index(pi) ? set[xy[pi]] : point();
  point t = is_right_index(pj) ? set[yx[pj]] : point(); 
  point rt = r.right_top(t);
  point pt = is_right_index(pi) && is_right_index(pj) ? tt.ref(pi, pj) : point();
  point a = trans(p, rt, g, pt);
  if(pout) *pout = a - rt;
  return rt.right_top(p + a) - rt + pt;
}

void per_tt_cell(ttable &tt, ttable &pt, size_t i, size_t j, ilist &xy, ilist &yx, num_t g, pset &set) {
  // 無効な添え字の場合はスキップする
  if(!is_right_index(i)) return;
  if(!is_right_index(j)) return;
  if(!is_multipoint_leader(i, xy, set)) return;
  if(!is_multipoint_leader(j, yx, set)) return;

  point &p = set[xy[i]], &q = set[yx[j]];
  size_t pi = prev_xy(i,j,xy,yx, set);
  size_t pj = prev_yx(i,j,xy,yx, set);
  point ta, tb, pa, pb;
  switch(size_corner(p, q)) {
    case 0: // イリーガルな組み合わせはスキップする
      return;
    case 1: // 単一点の場合
      ta = sum_transrect(p, pi, pj, tt, g, xy, yx, set, &pa);
      tt.ref(i, j) = ta;
      pt.ref(i, j) = pa;
      break;
    case 2: // 二点の場合
      ta = sum_transrect(p, pi, j, tt, g, xy, yx, set, &pa);
      tb = sum_transrect(q, i, pj, tt, g, xy, yx, set, &pb);
      if(ta.length() < tb.length()) {
        tt.ref(i, j) = ta;
        pt.ref(i, j) = pa;
      } else {
        tt.ref(i, j) = tb;
        pt.ref(i, j) = pb;
      }
      break;
  }
}

void per_expand_point(pset &set, ilist &ex, size_t i, ilist &s, point trans) {
  set[s[i]] += trans;
  ex.push_back(s[i]);

  // 重複点の処理
}

void expand_ilist(ilist &ex, ttable &tt, ttable &pt, size_t g, ilist &xy, ilist &yx, pset &set) {
  size_t i = xy.size() - 1, j = yx.size() - 1;
  while(is_right_index(i) && is_right_index(j)) {
    std::cerr << i << " " << j << std::endl;
    point p = set[xy[i]], q = set[yx[j]];
    size_t pi = prev_xy(i, j, xy, yx, set);
    size_t pj = prev_yx(i, j, xy, yx, set);
    switch(size_corner(p, q)) {
      case 0: // 例外なセル参照
        std::cerr << "Error : Illegal Access Translation Table." << std::endl;
        return;
      case 1:
        per_expand_point(set, ex, i, xy, pt.ref(i, j));
        i = pi; j = pj;
        break;
      case 2:
        // 編集距離の再計算を行い、どちらの選択を行ったかを判定する
        if( sum_transrect(p, pi, j, tt, g, xy, yx, set).length()
            < sum_transrect(q, i, pj, tt, g, xy, yx, set).length() )
        {
          per_expand_point(set, ex, i, xy, pt.ref(i, j));
          i = pi;
        } else {
          per_expand_point(set, ex, j, yx, pt.ref(i, j));
          j = pj;
        }
        break;
    }
  }
}

void trans_grid(pset &set, ilist &ex, ttable &pt) {
  point rt;
  for(size_t i = ex.size()-1; i >= 0; --i) {
    set[ex[i]] += rt;
    rt = rt.right_top(set[ex[i]]);

    // 重複点の処理
  }
}

void layout(pset &set, num_t g, num_t exp) {
  // ソート列の生成
  std::cerr << "-sort xy, yx." << std::endl;
  ilist xy, yx;
  init_ilist(xy, set); sort_xy(xy, set);
  init_ilist(yx, set); sort_yx(yx, set);
  std::cerr << "done." << std::endl;

  // 編集距離テーブルの生成
  //   テーブルのアクセス順が一方向であれば、必ず部分矩形の計算は終了している。
  //   ここでは矩形毎に含まれる点数を省略することができる。
  std::cerr << "-trans-table." << std::endl;
  ttable tt(set.size()), pt(set.size());
  for(size_t i=0; i<xy.size(); ++i)
    for(size_t j=0; j<yx.size(); ++j)
      per_tt_cell(tt, pt, i, j, xy, yx, g, set);
  std::cerr << "done." << std::endl;

  // 拡張点列の生成
  std::cerr << "-expand-list." << std::endl;
  ilist ex;
  expand_ilist(ex, tt, pt, g, xy, yx, set);
  std::cerr << "done." << std::endl;

  // 点のグリッド上への再配置
  std::cerr << "-trans-grid." << std::endl;
  trans_grid(set, ex, pt);
  std::cerr << "done." << std::endl;
}


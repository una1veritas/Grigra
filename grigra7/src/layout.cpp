#include "layout.hpp"

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
    r.y = t.y != 0 ? t.yifswap(r.y, uy, vy) : g;
  else if(tmp.x < 0 && tmp.y < 0)
    if(t.x >= 0)
      r.x = ifswap(r.x, ux, vx);
    else if(t.y >= 0)
      r.y = ifswap(r.y, uy, vy);

  // 編集距離を返す
  return r;
}

void per_tt_cell(ttable &tt, size_t i, size_t j, ilist &xy, ilist &yx, num_t g, pset &set) {
  
  // 無効な添え字の場合はスキップする
  if(!is_right_index(i)) return;
  if(!is_right_index(j)) return;
  if(!is_multipoint_leader(i, xy, set)) return;
  if(!is_multipoint_leader(j, yx, set)) return;

  point &p = set[xy[i]], &q = set[yx[j]];
  size_t pi = prev_xy(i,j,xy,yx);
  size_t pj = prev_yx(i,j,xy,yx);
  
  switch(size_corner(p, q)) {
    case 0: // イリーガルな組み合わせはスキップする
      return;
    case 1: // 単一点の場合
      // 前任矩形の計算
      art = is_right_index(pi) ? point() : set[xy[pi]];
      art = art.right_top( is_right_index(pj) ? point() : set[yx[pj]] );
      // 前までの総編集距離
      pta = is_right_index(pi) && is_right_index(pj) ? tt.ref(pi, pj) : point(0,0);
      // 今回の相対点編集距離
      a = trans(p, art, g, pta);
      // 今回までの矩形編集距離
      ta = art.right_top(p + a) - art + pta;
      // 今回の絶対点編集距離
      pa = a - art;

      // テーブルへの保存
      tt.ref(i, j) = ta;
      pt.ref(i, j) = pa;
      break;
    case 2: // 二点の場合
      art = set[xy[pi]].right_top(q);
      pta = tt.ref(pi, j);
      a = trans(p, art, g, pta);
      ta = art.right_top(p + a) - art + pta;
      pa = a - art;

      brt = p.right_top(set[yx[pj]]);
      ptb = tt.ref(i, pj);
      b = trans(q, art, g, ptb);
      ta = brt.right_top(q + a) - brt + ptb;
      pb = b - brt;

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

void layout(pset &set, num_t g, num_t exp) {

  // ソート列の生成
  ilist xy, yx;
  init_ilist(xy, set); sort_xy(xy, set);
  init_ilist(yx, set); sort_yx(yx, set);

  // 編集距離テーブルの生成
  //   テーブルのアクセス順が一方向であれば、必ず部分矩形の計算は終了している。
  //   ここでは矩形毎に含まれる点数を省略することができる。
  ttable tt(set.size());
  for(size_t i=0; i<xy.size(); ++i)
    for(size_t j=0; j<yx.size(); ++j)
      per_tt_cell(tt, i, j, xy, yx, g, set);

  // 拡張点列の生成

  // 点のグリッド上への再配置

}


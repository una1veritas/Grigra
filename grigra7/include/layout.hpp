#ifndef LAYOUT_HPP
#define LAYOUT_HPP

#include "point.hpp"
#include "table.hpp"

// 重複点の代表点であるかをチェックする
// 成分に重複を持つ点は代表点 ( ソート列に対し最も前任のもの ) である1点とする
bool is_multipoint_leader(size_t i, ilist &a, pset &set);

size_t rewind_multipoint(size_t i, ilist &a, pset &set);

// 右上角となる添え字組の実際の点数
// 0 : 無効な添え字の組み合わせ
// 1 : 単一の点による右上角
// 2 : 二点による右上角
size_t size_corner(point &p, point &q);

// xy方向およびyx方向における境界矩形内の前任点の添え字(*)
// prev_xyはxyにおける添え字を、prev_yxはyxにおける添え字を返す
// 前任点がいない場合は、OUT_OF_INDEX を返す
//
// 制約 : 入力<i, j> が size_corner において 0 でない
size_t prev_xy(size_t i, size_t j, ilist &xy, ilist &yx, pset &set);
size_t prev_yx(size_t i, size_t j, ilist &xy, ilist &yx, pset &set);

// 編集距離の計算
// p : 編集される点の元位置
// rt : pを除いた境界矩形の右上角
// g : グリッド幅
// sumt : rtがグリッド配置されるまでの編集距離
point trans(point p, point rt, num_t g, point sumt);

// 矩形編集距離の計算
point sum_transrect(point p, size_t pi, size_t pj, ttable &tt, size_t g, ilist &xy, ilist &yx, pset &set, point *pout = NULL);

// 編集距離テーブルの各々のセルに対する計算
void per_tt_cell(ttable &tt, size_t i, size_t j, ilist &xy, ilist &yx, num_t g, pset &set);

// 点毎の処理
void per_expand_point(pset &set, ilist &ex, size_t i, ilist &s, point trans);

// 拡張点列の計算
void expand_ilist(ilist &ex, ttable &tt, ttable &pt, size_t g, ilist &xy, ilist &yx, pset &set);

// グリッドへの再配置
void trans_grid(pset &set, ilist &ex, ttable &pt);

// グリッドレイアウトの適用(setが変更されます)
// set : 入力および出力点集合オブジェクト
// g : グリッド幅
// exp (optional) : 計算時に保障する固定小数
void layout(pset &set, num_t g, num_t exp = 0);

#endif

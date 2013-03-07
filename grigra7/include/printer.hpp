#ifndef PRINTER_HPP
#define PRINTER_HPP

#include "point.hpp"
#include <iostream>

// Point Set Printer.
// out : 出力先ストリーム
// set : 出力する点集合オブジェクト
// exp (optional) : 出力に保障する固定小数桁数
void print_pset(pset &set, std::ostream &out = std::cout, num_t exp = 0);

// Printer Config
// rawは要素ごとのデリミタ (標準は " ")
// colはラインの末尾のデリミタ (標準は "")
//   * colの後にstd::endlマニピュレータが呼び出される。
extern const char *pset_raw_delimiter;
extern const char *pset_col_delimiter;

// Debug Checker.
bool check_overlap(pset &set, std::ostream &err = std::cerr);
bool check_gridded(pset &set, num_t g, std::ostream &err = std::cerr);
void check_gridlayout_successed(pset &set, num_t g, std::ostream &err = std::cerr);

#endif

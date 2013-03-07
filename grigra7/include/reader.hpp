#ifndef READER_HPP
#define READER_HPP

#include "point.hpp"
#include <iostream>

// Point Set Reader.
// in : 入力元ストリーム
// set : 出力先の点集合オブジェクト
// exp (optional) : 保障する固定小数の桁数
void read_pset(pset &set, std::istream &in = std::cin, num_t exp = 0);

#endif


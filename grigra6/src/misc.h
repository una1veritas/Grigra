#ifndef GRID_LAYOUT_MISC_H
#define GRID_LAYOUT_MISC_H

/* <encode : utf-8>

  グリッドレイアウトプログラム用のちょっとした関数。

*/

#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <algorithm>
#include <functional>
#include <cmath>
#include <list>
#include <limits>

template <typename TYPE>
TYPE modulo(TYPE a, TYPE b) {
  return a % b;
}
template <>
float modulo(float a, float b) {
  return std::fmod(a,b);
}
template <>
double modulo(double a, double b) {
  return std::fmod(a,b);
}
template <>
int modulo(int a, int b) {
  return a % b;
}

#endif

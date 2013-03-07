
#include "reader.hpp"
#include "printer.hpp"
#include "layout.hpp"

// Entry Point.
int main(int argc, char **argv) {
  num_t g = 0, e = 0;
  pset set;
  
  read_pset(set, std::cin, e);
  layout(set, g, e);

  // 出力時のデリミタ変更
  // 空白が嫌なときに使ってください
  //pset_raw_delimiter = ",";

  print_pset(set, std::cout, e);

  return 0;
}

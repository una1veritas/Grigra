
#include "reader.hpp"
#include "printer.hpp"
#include "layout.hpp"

#include <iostream>
#include <fstream>
#include <cstdlib>

// Entry Point.
int main(int argc, char **argv) {
  num_t g = 0, e = 0;
  pset set;

  if(argc < 3) {
    std::cerr << "Usage : *** [g] [e] < IN > OUT" << std::endl;
    std::cerr << "Usage : *** [g] [e] filename > OUT" << std::endl;
    std::cerr << "Usage : *** [g] [e] filename out-filename" << std::endl;
    return 0;
  }

  g = std::strtoul(argv[1], 0, 0);
  e = std::strtoul(argv[2], 0, 0);

  std::cerr << "GridLayout - start!  grid-size : " << g << " , exp10 : " << e << std::endl;

  if(argc > 3) {
    std::ifstream fin(argv[3]);
    if(!fin.is_open()) {
      std::cerr << "File not exit : " << argv[3] << std::endl;
      return 0;
    }
    read_pset(set, fin, e);
  } else {
    read_pset(set, std::cin, e);
  }

  std::cerr << "Read InputPointSet ... Done." << std::endl;
  std::cerr << " size : " << set.size() << std::endl;

  layout(set, g, e);

  std::cerr << "Gridlayout ... Done." << std::endl;

  check_gridlayout_successed(set, g, std::cerr);

  std::cerr << "Write PointSet - start!" << std::endl;

  // 出力時のデリミタ変更
  // 空白が嫌なときに使ってください
  //pset_raw_delimiter = ",";

  if(argc > 4) {
    std::ofstream fout(argv[4]);
    if(!fout.is_open()) {
      std::cerr << "File not exit : " << argv[4] << std::endl;
      return 0;
    }
    print_pset(set, fout, e);
  } else {
    print_pset(set, std::cout, e);
  }

  return 0;
}

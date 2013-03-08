
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "layout.hpp"

int main(int argc, char **argv) {
  using namespace gridlayout;
  PointSetProxy<int> pset;

  int g = 0;

  if(argc < 2) {
    std::cerr << "USAGE : layout [gridsize/int] < [input] > [output]" << std::endl;
    return 0;
  }
  g = atoi(argv[1]);
  if (argc == 2 ) {
	  pset.readfile(std::cin);
  } else {
	  pset.readfile(argv[2]);
  }
  
  clock_t clk = clock();
  GridLayout<int>(&pset, g);
  clk = clock() - clk;
  std::cout.flush();
  std::cerr << "TIME : " << clk / (double)CLOCKS_PER_SEC << std::endl;
  
  pset.print(std::cout);

  return 0;
}

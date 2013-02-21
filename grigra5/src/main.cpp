
#include <iostream>
#include <fstream>
#include <iomanip>

#include <stdlib.h>
#include <time.h>

#include "layout.hpp"

int main(int argc, char **argv) {
  using namespace gridlayout;

  std:: ifstream inputf;
  int g = 0;
  PointSetProxy<int> * pset;

  if (argc >= 2) {
	  for(int i = 0; i < argc; i++) {
		  std::cout << argv[i] << ", ";
	  }
	  std::cout << std::endl;
	  g = atoi(argv[1]);
	  if ( argc == 3 ) {
		  pset = new PointSetProxy<int>(std::cin);
	  } else {
		  pset = new PointSetProxy<int>(argv[2]);
	  }
  } else {
    std::cerr << "USAGE : layout [gridsize/int] < [input] > [output]" << std::endl;
    return 0;
  }

  
  clock_t clk = clock();
  GridLayout<int>(pset, g);
  clk = clock() - clk;
  std::cerr << "TIME : " << clk / (double)CLOCKS_PER_SEC << std::endl;
  
  pset->print(std::cout);

  return 0;
}

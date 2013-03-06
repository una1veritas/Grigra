#ifndef READER_HPP
#define READER_HPP

#include "point.hpp"
#include <iostream>

// Point Set Reader.
std::istream &operator >>(std::istream &in, pset &set);

#endif


#include "point.hpp"

point::point() : x(0), y(0) {
}

point::point(num_t x, num_t y) : x(x), y(y) {
}

point::point(const point &p) : x(p.x), y(p.y) {
}

point::~point() {
}

point point::right_top(point p) {
  return point(std::max(x, p.x), std::max(y, p.y));
}

num_t point::length() const {
  return std::abs(x) + std::abs(y);
}

bool point::lt_xy(point &p) {
  return x < p.x || ( x == p.x && y < p.y );
}

bool point::lt_yx(point &p) {
  return y < p.y || ( y == p.y && x < p.x );
}

bool point::operator == (point &p) {
  return x == p.x && y == p.y;
}

bool point::operator != (point &p) {
  return !(*this == p);
}

point &point::operator = (point p) {
  x = p.x;
  y = p.y;
  return *this;
}

point point::operator + (point p) {
  return point(x + p.x, y + p.y);
}

point point::operator - (point p) {
  return point(x - p.x, y - p.y);
}

point &point::operator += (point p) {
  x += p.x;
  y += p.y;
  return *this;
}

point &point::operator -= (point p) {
  x -= p.x;
  y -= p.y;
  return *this;
}



/* <encode : utf-8>

  繧ｰ繝ｪ繝�ラ繝ｬ繧､繧｢繧ｦ繝医い繝ｫ繧ｴ繝ｪ繧ｺ繝��螳溯｣��

*/

#include "layout.hpp"
#include "layoutman.h"

template<typename TYPE>
gridlayout::PointSetProxy<TYPE>::PointSetProxy() : set_p(__null) {
}

template<typename TYPE>
gridlayout::PointSetProxy<TYPE>::PointSetProxy(const char *filename) : set_p(__null) {
	readfile(filename);
}

template<typename TYPE>
void gridlayout::PointSetProxy<TYPE>::readfile(const char fname[]) {
	std::ifstream fin(fname);
	if(fin.is_open()) {
		set_p = new gridlayout::PointSet<TYPE>(fin);
	}
}

template<typename TYPE>
void gridlayout::PointSetProxy<TYPE>::readfile(std::istream & fin) {
	set_p = new gridlayout::PointSet<TYPE>(fin);
}

template<typename TYPE>
gridlayout::PointSetProxy<TYPE>::PointSetProxy(std::istream &pIn) : set_p(__null) {
	readfile(pIn);
}

template<typename TYPE>
gridlayout::PointSetProxy<TYPE>::PointSetProxy(const TYPE *pset, const size_t length) : set_p(__null) {
  this->set_p = new gridlayout::PointSet<TYPE>(pset, length);
}


template<typename TYPE>
gridlayout::PointSetProxy<TYPE>::~PointSetProxy() {
  if(set_p) delete set_p;
}

template<typename TYPE>
size_t gridlayout::PointSetProxy<TYPE>::length() {
  return set_p->size();
}

template<typename TYPE>
void gridlayout::PointSetProxy<TYPE>::print() {
  std::cout << *set_p << std::endl;
}

template<typename TYPE>
void gridlayout::PointSetProxy<TYPE>::print(std::ostream &sOut) {
  sOut << *set_p << std::endl;
}

template<typename TYPE>
void gridlayout::PointSetProxy<TYPE>::print(TYPE *out_p, const size_t maxlen) {
  size_t k=0;
  for(typename std::vector<Point<TYPE> >::iterator i = set_p->begin();
      i != set_p->end() || k < maxlen;
      ++i, k+=2)
  {
    out_p[k] = i->getX();
    out_p[k+1] = i->getY();
  }
}

template<typename TYPE>
int gridlayout::GridLayout(PointSetProxy<TYPE> *pointset, const TYPE gridsize)
{
  if(!pointset->set_p) {
    return -1;
  }
  GridLayoutMan<TYPE> gl(gridsize);
  gl.match(*(pointset->set_p));
  if(!pointset->set_p->checkIndependent()) {
    std::cerr << "NOT INDEPENDENT MATCH!" << std::endl;
  }
  return 0;
}

//
// Concrete.
//
template class gridlayout::PointSetProxy<int>;
template class gridlayout::PointSetProxy<float>;
template class gridlayout::PointSetProxy<double>;
template int gridlayout::GridLayout(PointSetProxy<int> *pointset, const int gridsize);
template int gridlayout::GridLayout(PointSetProxy<float> *pointset, const float gridsize);
template int gridlayout::GridLayout(PointSetProxy<double> *pointset, const double gridsize);


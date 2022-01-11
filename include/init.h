#ifndef _INIT_H_
#define _INIT_H_

#include <vector>
#include <unordered_map>
#include <armadillo>

#include "util.h"

namespace lonelynodes {

  using gumap = std::unordered_map<unsigned int, vecu>;

}



void gFillEach_(const unsigned int tidx,
                ln::vecu& fillNodes);

ln::gumap gumapInit(const arma::umat& m);

ln::vecu gNodeCount_(const arma::umat& m);

#endif // _INIT_H_

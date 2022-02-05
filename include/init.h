#ifndef _INIT_H_
#define _INIT_H_

#include <algorithm>
#include <armadillo>
#include <unordered_map>
#include <vector>

#include "util.h"

namespace lonelynodes {

using gumap = std::unordered_map<unsigned int, vecu>;
} // namespace lonelynodes


void gFillEach_(const size_t tidx, ln::vecu& fillNodes);

ln::gumap gumapInit(const arma::umat& m);

ln::vecu gNodeCount_(const arma::umat& m);

arma::umat gidcInit(const ln::gumap& g);

#endif // _INIT_H_

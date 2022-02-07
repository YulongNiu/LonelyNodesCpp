#ifndef _PIVOT_H_
#define _PIVOT_H_

#include "util.h"

// `indicator` is a bit vector
arma::uword First0Idx_(const arma::uvec& idc);

arma::uword NextNodeIdx_(const ln::vecu&   eachNodes,
                         const ln::vecu&   eachXnodes,
                         const arma::umat& gidc);

#endif // _PIVOT_H_

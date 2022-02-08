#ifndef _PIVOT_H_
#define _PIVOT_H_

#include "util.h"

// `indicator` is a bit vector
arma::uword NextNodeIdx_(const ln::vecu&   sclique,
                         const ln::vecu&   nodes,
                         const ln::vecu&   xnodes,
                         const arma::umat& gidc);

arma::uword First0Idx_(const arma::uvec& idc);

arma::uvec MergeNodes_(const ln::vecu& sclique, const ln::vecu& nodes);

#endif // _PIVOT_H_

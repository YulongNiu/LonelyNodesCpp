#ifndef _PIVOT_H_
#define _PIVOT_H_

#include "util.h"

ln::iterv FirstPnode_(ln::vecu& eachNodes, const arma::uvec& eachIdc);

ln::iterv NextPnode_(ln::vecu&         eachNodes,
                     const ln::vecu&   eachXnodes,
                     const arma::umat& gidc);

#endif // _PIVOT_H_

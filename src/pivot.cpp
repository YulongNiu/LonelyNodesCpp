#include <armadillo>
#include <vector>

#include "util.h"

using namespace std;
using namespace arma;
using namespace ln;


// first index of non-intersection node
// `indicator` is a bit vector
arma::uword First0Idx_(const arma::uvec& idc) {

  uword i = 0;
  for (; i != idc.n_elem && (idc[i] == 1); ++i) {}

  return i;
}


// longest intersection
arma::uword NextNodeIdx_(const ln::vecu&   eachNodes,
                         const ln::vecu&   eachXnodes,
                         const arma::umat& gidc) {

  if (eachXnodes.empty()) { return 0; }

  umat splitIdc = gidc.submat(STD2ARMAuv(eachNodes), STD2ARMAuv(eachXnodes));

  // column contains max searched linked-nodes
  auto maxCol = sum(splitIdc, 0).index_max();

  return First0Idx_(splitIdc.col(maxCol));
}

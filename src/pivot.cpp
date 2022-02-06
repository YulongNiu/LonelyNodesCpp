#include <armadillo>
#include <vector>

#include "util.h"

using namespace std;
using namespace arma;
using namespace ln;


// first index of non-intersection node
// `nodes` and `indicator`.
// `indicator` is a bit vector
ln::iterv FirstPnode_(ln::vecu& eachNodes, const arma::uvec& eachIdc) {

  auto pnode = eachNodes.begin();

  for (uword i = 0; i != eachIdc.n_elem && (eachIdc[i] == 1); ++i, ++pnode) {}

  return pnode;
}


// longest intersection
ln::iterv NextPnode_(ln::vecu&         eachNodes,
                     const ln::vecu&   eachXnodes,
                     const arma::umat& gidc) {

  if (eachXnodes.empty()) { return eachNodes.begin(); }

  umat splitIdc = gidc.submat(STD2ARMAuv(eachNodes), STD2ARMAuv(eachXnodes));

  // column contains max searched linked-nodes
  auto maxCol = sum(splitIdc, 0).index_max();

  return FirstPnode_(eachNodes, splitIdc.col(maxCol));
}

#include "pivot.h"
#include "util.h"

using namespace std;
using namespace arma;
using namespace ln;

// first index of non-intersection node.
// Because the `SearchLeaf_()` always search the left node without
// check on each step, the `0` may occur in `sclique`.

// longest intersection
arma::uword NextNodeIdx_(const ln::vecu&   sclique,
                         const ln::vecu&   nodes,
                         const ln::vecu&   xnodes,
                         const arma::umat& gidc) {

  if (xnodes.empty() || nodes.empty()) { return 0; }

  uvec snodes   = MergeNodes_(sclique, nodes);
  umat splitIdc = gidc.submat(snodes, STD2ARMAuv(xnodes));

  // column contains max searched linked-nodes
  auto maxCol = sum(splitIdc, 0).index_max();
  auto idx    = First0Idx_(splitIdc.col(maxCol));

  return (idx > sclique.size()) ? (idx - sclique.size()) : 0;
}


// `indicator` is a bit vector
arma::uword First0Idx_(const arma::uvec& idc) {

  uword i = 0;
  for (; i != idc.n_elem && (idc[i] == 1); ++i) {}

  return i;
}


arma::uvec MergeNodes_(const ln::vecu& sclique, const ln::vecu& nodes) {
  return join_cols(STD2ARMAuv(sclique), STD2ARMAuv(nodes));
}

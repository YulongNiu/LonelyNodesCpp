#include <iostream>
#include <unordered_map>

#include "clique.h"
#include "init.h"
#include "pivot.h"
#include "util.h"

using namespace std;
using namespace arma;

namespace lonelynodes {

// Leaf NextLeaf(const Leaf& leaf, const gumap& g) {
//   auto searchNode = leaf.snode;

//   // push `searchNode` to the end of last elem in `nseeds`;
//   auto nseeds = leaf.get_seeds();
//   nseeds.push_back(searchNode);

//   // push `searchNode` to the end of `nstem`;
//   auto nstem = leaf.get_stem();


//   // push `lastClique` to the end of `clique`.
//   auto lastClique = sclique.back(); // never empty!
//   lastClique.push_back(searchNode);


//   // erase 1st node of `searchNodes`
//   nodes.back().erase(nodes.back().begin());

//   // next leaf
//   searchNodes leaf = ;
// }

// // search for the next leaf
// vecu Leaf::next_seeds() const {
//   vecu res = seeds;
//   res.push_back(snode);
//   return res;
// }

// Leaf::next_leaf(const gumap& g) const {}

arma::uword Leaf::next_nodeidx(const arma::umat& gidc) const {
  // branches may not need to check
  if (seeds.empty() || branches.empty()) { return 0; }

  auto crown    = this->get_crown();
  umat splitIdc = gidc.submat(STD2ARMAuv(crown), STD2ARMAuv(seeds));

  // column contains max searched linked-nodes
  auto maxCol = sum(splitIdc, 0).index_max();
  auto idx    = First0Idx_(splitIdc.col(maxCol));

  return (idx > stem.size()) ? (idx - stem.size()) : 0;
}

vecvu SearchLeafObj(const Leaf& start, const arma::umat& gidc) {

  vecvu   cliques;
  vecleaf vleaf{ start };

  for (; !vleaf.empty();) {
    // step1: check next node idx for last elem
    auto lastLeaf = vleaf.back();
    vleaf.pop_back();

    auto idx = lastLeaf.next_nodeidx(gidc);
    if (!lastLeaf.is_skippable(idx)) {
      vleaf.push_back(lastLeaf.update_leaf(idx));
      vleaf.push_back(lastLeaf.next_leaf(idx, gidc));
    } else {
      continue;
    }

    // step2: find maximal clique
    if (vleaf.back().branches_empty()) {
      cliques.push_back(vleaf.back().get_stem());
      // BackSkipLeafObj(vleaf);
      vleaf.pop_back();
    }
  }

  return cliques;
}


void BackSkipLeafObj(vecleaf& vleaf) {

  auto p = next(vleaf.rbegin());

  for (auto bestSize = vleaf.back().stem_size();
       (p != vleaf.rend()) && ((*p).crown_size() < bestSize);
       ++p) {}

  // vleaf.erase(p.base());
  // vleaf.erase(p.base(), vleaf.end());
}

} // namespace lonelynodes

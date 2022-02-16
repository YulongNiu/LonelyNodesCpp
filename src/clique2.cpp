#include "clique.h"
#include "init.h"
#include "pivot.h"
#include "util.h"

using namespace std;
using namespace arma;

namespace lonelynodes {

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

      cout << "1st nodes size: " << vleaf.front().branches_size()
           << "; node size: " << vleaf.size()
           << "; #cliques: " << cliques.size() << "; srnodes is: ";
      Printvecu(vleaf.back().get_seeds());

      BackSkipLeafObj(vleaf);
    }
  }

  return cliques;
}


void BackSkipLeafObj(vecleaf& vleaf) {

  auto p = next(vleaf.rbegin());

  for (auto bestSize = vleaf.back().stem_size();
       (p != vleaf.rend()) && ((*p).crown_size() < bestSize);
       ++p) {}

  vleaf.erase(p.base(), vleaf.end());
}

} // namespace lonelynodes

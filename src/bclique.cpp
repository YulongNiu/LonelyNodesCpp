#include "bclique.h"
#include "init.h"
#include "util.h"

using namespace std;
using namespace arma;

namespace lonelynodes {

arma::uword LeafBit::next_nodeidx(const vecdbit& gdbit) const {

  if (seeds.empty() || this->branches_empty()) { return branches.find_first(); }

  auto crown = this->get_crown();
  auto f0    = First0dbit_(crown, seeds, gdbit);

  return First0IdxBit_(stem, branches, f0);
}


dbit ComplementBit(const dbit& a, const dbit& b) {
  return a & (~b);
}

dbit First0dbit_(const dbit& crown, const vecu& seed, const vecdbit& gdbit) {
  uword lct    = 0;
  uword maxIdx = 0;

  for (uword i = 0; i < seed.size(); ++i) {
    auto eachIdx   = seed.at(i);
    auto eachInter = crown & gdbit.at(eachIdx);
    auto eachCount = eachInter.count();

    if (eachCount >= lct) {
      lct    = eachCount;
      maxIdx = eachIdx;
    }
  }

  return ComplementBit(crown, gdbit.at(maxIdx));
}

arma::uword
First0IdxBit_(const dbit& stem, const dbit& branches, const dbit& f0) {

  return (stem & f0).any() ? branches.find_first() : f0.find_first();
}


vecdbit SearchLeafBit(const LeafBit& start, const vecdbit& gdbit) {

  vecdbit    cliques;
  vecleafbit vleaf{ start };

  // count, will be deleted
  uword i = 0; // d
  uword j = 0; // d

  for (; !vleaf.empty();) {

    auto lastLeaf = vleaf.back();
    vleaf.pop_back();

    auto idx = lastLeaf.next_nodeidx(gdbit);
    ++i; // d
    if (!lastLeaf.is_skippable(idx)) {
      // step1: check next node idx for last elem
      vleaf.push_back(lastLeaf.update_leaf(idx));
      vleaf.push_back(lastLeaf.next_leaf(idx, gdbit));
      ++j; // d

      // step2: find maximal clique
      if (vleaf.back().branches_empty()) {
        cliques.push_back(vleaf.back().get_stem());

        cout << "1st nodes size: " << vleaf.front().branches_size()
             << "; node size: " << vleaf.size()
             << "; #cliques: " << cliques.size() << "; #loop: " << i
             << "; #search: " << j << "; srnodes is: "; // d
        Printvecu(vleaf.back().get_seeds());            // d

        BackSkipLeafBit(vleaf);
        i = 0; // d
        j = 0; // d
      }
    }
  }

  return cliques;
}


void BackSkipLeafBit(vecleafbit& vleaf) {

  auto p = next(vleaf.rbegin());

  for (auto bestSize = vleaf.back().stem_size();
       (p != vleaf.rend()) && ((*p).crown_size() < bestSize);
       ++p) {}

  vleaf.erase(p.base(), vleaf.end());
}

} // namespace lonelynodes

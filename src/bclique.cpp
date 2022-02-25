#include "bclique.h"
#include "init.h"
#include "util.h"
#include <memory>

using namespace std;

namespace lonelynodes {

arma::uword LeafBit::next_nodeidx(const vecdbit& gdbit) const {

  // No need to check branches empty.
  // Case1: `branches_size() == 1`,
  // then branches in "next_leaf" is empty and will be checked;
  // both "next_leaf" and "update_leaf" will be skipped.
  // Case2: `branches_size() >= 2` and branches in "next_leaf" is empty.
  // "next_leaf" will be checked and skipped.
  // But branches in "update_leaf" >= 1,
  // so case1 will be repeated.
  // In total, empty branches will not appear here.

  // No need to check seeds empty.
  // If `seeds.empty()`, `branches.find_first()` always returns.

  auto crown = get_crown();
  auto f0    = First0dbit_(crown, seeds, gdbit);

  return First0IdxBit_(stem, branches, f0, gdbit);
}


dbit ComplementBit(const dbit& a, const dbit& b) {
  return a & (~b);
}

// If `seeds.empty()`, return `crown` that will never be empty.
dbit First0dbit_(const dbit& crown, const vecu& seeds, const vecdbit& gdbit) {
  arma::uword maxCt = 0;

  dbit maxInter(crown.size(), 0);

  for (const auto& elem : seeds) {
    auto eachInter = crown & gdbit.at(elem);
    auto eachCount = eachInter.count();

    if (eachCount > maxCt) {
      maxCt    = eachCount;
      maxInter = eachInter;
    }
  }

  return crown ^ maxInter;
}


arma::uword First0IdxBranchesBit_(const dbit& branches, const vecdbit& gdbit) {

  auto i = branches.find_first();

  arma::uword maxIdx = i;
  arma::uword maxCt  = 0;

  for (; i != dbit::npos; i = branches.find_next(i)) {

    auto eachCt = (branches & gdbit.at(i)).count();

    if (eachCt > maxCt) {
      maxCt  = eachCt;
      maxIdx = i;
    }
  }

  return maxIdx;
}


// If `seeds.empty()`, `f0 == crown`. In this case, if `stem.any()`,
// `branches.find_first()` returns; if `stem.none()`,
// `f0.find_first()` equal to `branches.find_first()`, returns.
// In total, if `seeds.empty()`, `branches.find_first()` always returns.
//
arma::uword First0IdxBit_(const dbit&    stem,
                          const dbit&    branches,
                          const dbit&    f0,
                          const vecdbit& gdbit) {

  // return (stem & f0).any() ? branches.find_first() : f0.find_first();
  return (stem & f0).any() ? First0IdxBranchesBit_(branches, gdbit) :
                             f0.find_first();
}


vecdbit SearchLeafBit(const LeafBit& start, const vecdbit& gdbit) {

  vecdbit     cliques;
  vecpleafbit vpleaf;
  vpleaf.push_back(make_shared<LeafBit>(start));

  // count, will be deleted
  arma::uword i = 0, j = 0; // d

  for (; !vpleaf.empty();) {

    auto& lastpLeaf = vpleaf.back();

    auto idx = lastpLeaf->next_nodeidx(gdbit);
    ++i; // d

    if (!lastpLeaf->is_skippable(idx)) {
      // step1: check next node idx for last elem
      auto uLeaf    = lastpLeaf->update_leaf(idx);
      auto nLeaf    = lastpLeaf->next_leaf(idx, gdbit);
      vpleaf.back() = uLeaf;
      vpleaf.push_back(nLeaf);
      ++j; // d

      // cout << "----------" << endl;
      // lastLeaf->print();
      // lastLeaf->update_leaf(idx).print();
      // lastLeaf->next_leaf(idx, gdbit).print();

      // step2: find maximal clique
      if (nLeaf->branches_empty()) {

        auto eachClique = nLeaf->get_stem();
        if (isMaximalCliqueBit_(eachClique, nLeaf->get_seeds(), gdbit)) {
          cliques.push_back(eachClique);
        }

        cout << "vleaf size: " << vpleaf.size()
             << "; #cliques: " << cliques.size()
             << "; clique size: " << eachClique.count() << "; #loop: " << i
             << "; #search: " << j << "; seeds: "; // d
        Printvecu(vpleaf.back()->get_seeds());     // d

        BackSkipLeafBit_(vpleaf);
        i = 0, j = 0; // d
      }
    } else {
      vpleaf.pop_back();
    }
  }

  return cliques;
}


void BackSkipLeafBit_(vecpleafbit& vpleaf) {

  auto p = next(vpleaf.rbegin());

  for (auto bestSize = vpleaf.back()->stem_size();
       (p != vpleaf.rend()) && ((*p)->crown_size() < bestSize);
       ++p) {}

  vpleaf.erase(p.base(), vpleaf.end());
}


bool isMaximalCliqueBit_(const dbit&    clique,
                         const vecu&    seeds,
                         const vecdbit& gdbit) {

  if (seeds.empty()) { return true; }

  arma::uword i = 0;
  for (; (i < seeds.size()) && !clique.is_subset_of(gdbit.at(seeds.at(i)));
       ++i) {}

  return i == seeds.size();
}
} // namespace lonelynodes

#ifndef _BCLIQUE_H_
#define _BCLIQUE_H_

#include <memory>

#include "BS_thread_pool.hpp"
#include "init.h"
#include "util.h"

namespace lonelynodes {

class LeafBit {
public:
  LeafBit() : seeds{}, stem{}, branches{} {}
  LeafBit(const dbit& seeds, const dbit& stem, const dbit& branches)
      : seeds{ seeds }, stem{ stem }, branches{ branches } {}

  dbit get_seeds() const { return seeds; };
  dbit get_stem() const { return stem; };
  dbit get_branches() const { return branches; };
  dbit get_crown() const {
    return stem | branches;
  } // union of `stem` and `branches`.

  arma::uword stem_size() const { return stem.count(); }
  arma::uword branches_size() const { return branches.count(); }
  arma::uword crown_size() const { return stem.count() + branches.count(); }

  // find next search node index
  arma::uword next_nodeidx(const vecdbit& gdbit) const;
  bool is_skippable(const arma::uword idx) const { return idx == dbit::npos; };

  // check maximal clique
  bool branches_empty() const { return branches.none(); }
  bool seeds_empty() const { return seeds.none(); }
  bool is_maximalclique() const { return branches.none() && seeds.none(); }

  // next elem
  dbit next_branches(const arma::uword idx, const vecdbit& gdbit) const;
  dbit next_stem(const arma::uword idx) const;
  dbit next_seeds(const arma::uword idx, const vecdbit& gdbit) const;
  std::shared_ptr<LeafBit> next_leaf(const arma::uword idx,
                                     const vecdbit&    gdbit) const;

  // update current elem
  dbit                     update_branches(arma::uword idx) const;
  dbit                     update_stem() const;
  dbit                     update_seeds(const arma::uword idx) const;
  std::shared_ptr<LeafBit> update_leaf(const arma::uword idx) const;

  void print() const;

private:
  // `seeds`: searched nodes, each of which has been completely searched
  // for maximal cliques.
  // `stem`: known cliques nodes in current leaf.
  // `branches`: nodes for next search.
  // No intersections among `seeds`, `branches`, or `steam`.
  const dbit seeds, stem, branches;
};

inline dbit LeafBit::next_branches(const arma::uword idx,
                                   const vecdbit&    gdbit) const {
  return branches & gdbit.at(idx);
}

inline dbit LeafBit::next_stem(const arma::uword idx) const {
  dbit res{ stem };
  res.set(idx);
  return res;
}

inline dbit LeafBit::next_seeds(const arma::uword idx,
                                const vecdbit&    gdbit) const {
  return seeds & gdbit.at(idx);
}

inline dbit LeafBit::update_branches(arma::uword idx) const {
  dbit res{ branches };
  res.reset(idx);
  return res;
}

inline dbit LeafBit::update_stem() const {
  return stem;
}

inline dbit LeafBit::update_seeds(const arma::uword idx) const {
  dbit res{ seeds };
  res.set(idx);
  return res;
}

inline std::shared_ptr<LeafBit> LeafBit::next_leaf(const arma::uword idx,
                                                   const vecdbit& gdbit) const {
  return std::make_shared<LeafBit>(
    LeafBit(next_seeds(idx, gdbit), next_stem(idx), next_branches(idx, gdbit)));
}

inline std::shared_ptr<LeafBit>
LeafBit::update_leaf(const arma::uword idx) const {
  return std::make_shared<LeafBit>(
    LeafBit(update_seeds(idx), update_stem(), update_branches(idx)));
}


// print `LeafBit` obj
inline void LeafBit::print() const {

  std::cout << "\n";

  std::cout << "seeds are: ";
  Printvecu(DBIT2VECU_(seeds));

  std::cout << "stem is: ";
  Printvecu(DBIT2VECU_(stem));

  std::cout << "branches is: ";
  Printvecu(DBIT2VECU_(branches));
}

using pleafbit    = std::shared_ptr<LeafBit>;
using vecpleafbit = std::vector<pleafbit>;

arma::uword First0IdxBranchesBit_(const dbit& branches, const vecdbit& gdbit);

// may equal to `dbit::npos`
arma::uword First0IdxBit_(const dbit&    stem,
                          const dbit&    branches,
                          const dbit&    f0,
                          const vecdbit& gdbit);


vecdbit SearchLeafBit(const LeafBit& start, const vecdbit& gdbit);

void BackSkipLeafBit_(vecpleafbit& vpleaf);

// void ChainReact(const pleafbit&  pleaf,
//                 const vecdbit&   gdbit,
//                 BS::thread_pool& tpool);

void SearchLeafBit2(const pleafbit& pleaf,
                    const vecdbit&  gdbit,
                    vecdbit&        cliques);
} // namespace lonelynodes

#endif // _BCLIQUE_H_

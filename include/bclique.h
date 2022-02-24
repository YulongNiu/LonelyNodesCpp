#ifndef _BCLIQUE_H_
#define _BCLIQUE_H_

#include "init.h"
#include "util.h"
#include <memory>

namespace lonelynodes {

class LeafBit {
public:
  LeafBit() : seeds{}, stem{}, branches{} {}
  LeafBit(const vecu& seeds, const dbit& stem, const dbit& branches)
      : seeds{ seeds }, stem{ stem }, branches{ branches } {}

  vecu get_seeds() const { return seeds; };
  dbit get_stem() const { return stem; };
  dbit get_branches() const { return branches; };
  dbit get_crown() const; // concatenate `stem` and `branches`.

  arma::uword next_nodeidx(const arma::umat& gidc) const;

  bool branches_empty() const { return branches.none(); }

  arma::uword stem_size() const { return stem.count(); }
  arma::uword branches_size() const { return branches.count(); }
  arma::uword crown_size() const { return stem.count() + branches.count(); }

  // find next search node index
  arma::uword next_nodeidx(const vecdbit& gdbit) const;

  bool is_skippable(const arma::uword idx) const { return idx == dbit::npos; };

  // next elem
  dbit next_branches(const arma::uword idx, const vecdbit& gdbit) const;
  dbit next_stem(const arma::uword idx) const;
  vecu next_seeds() const;
  std::shared_ptr<LeafBit> next_leaf(const arma::uword idx,
                                     const vecdbit&    gdbit) const;

  // update current elem
  dbit                     update_branches(arma::uword idx) const;
  dbit                     update_stem() const;
  vecu                     update_seeds(const arma::uword idx) const;
  std::shared_ptr<LeafBit> update_leaf(const arma::uword idx) const;

  void print() const;

private:
  // `seeds`: searched nodes, each of which has been completely searched
  // for maximal cliques.
  // `branches`: nodes for next search.
  // `stem`: known cliques nodes in current leaf.
  // No intersections among `seeds`, `branches`, or `steam`.
  const vecu seeds;
  const dbit stem, branches;
};

inline dbit LeafBit::get_crown() const {
  return stem | branches;
}

inline dbit LeafBit::next_branches(const arma::uword idx,
                                   const vecdbit&    gdbit) const {
  return branches & gdbit.at(idx);
}

inline dbit LeafBit::next_stem(const arma::uword idx) const {
  dbit res{ stem };
  res.set(idx);
  return res;
}

inline vecu LeafBit::next_seeds() const {
  return seeds;
}

inline dbit LeafBit::update_branches(arma::uword idx) const {
  dbit res{ branches };
  res.reset(idx);
  return res;
}

inline dbit LeafBit::update_stem() const {
  return stem;
}

inline vecu LeafBit::update_seeds(const arma::uword idx) const {
  vecu res{ seeds };
  res.push_back(idx);
  return res;
}

inline std::shared_ptr<LeafBit> LeafBit::next_leaf(const arma::uword idx,
                                                   const vecdbit& gdbit) const {
  return std::make_shared<LeafBit>(
    LeafBit(next_seeds(), next_stem(idx), next_branches(idx, gdbit)));
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
  Printvecu(seeds);

  std::cout << "stem is: ";
  Printvecu(DBIT2VECU_(stem));

  std::cout << "branches is: ";
  Printvecu(DBIT2VECU_(branches));
}

using pleafbit    = std::shared_ptr<LeafBit>;
using vecpleafbit = std::vector<pleafbit>;

// complement a \ b
dbit ComplementBit(const dbit& a, const dbit& b);

dbit First0dbit_(const dbit& crown, const vecu& seed, const vecdbit& gdbit);

// may equal to `dbit::npos`
arma::uword
First0IdxBit_(const dbit& stem, const dbit& branches, const dbit& f0);

vecdbit SearchLeafBit(const LeafBit& start, const vecdbit& gdbit);

void BackSkipLeafBit_(vecpleafbit& vpleaf);

bool isMaximalCliqueBit_(const dbit&    clique,
                         const vecu&    seeds,
                         const vecdbit& gdbit);

} // namespace lonelynodes

#endif // _BCLIQUE_H_

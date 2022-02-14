#ifndef _CLIQUE_H_
#define _CLIQUE_H_

#include <iostream>

#include "init.h"
#include "util.h"

namespace lonelynodes {

class Leaf {
public:
  Leaf() : seeds{}, stem{}, branches{} {}
  Leaf(const vecu& seeds, const vecu& stem, const vecu& branches)
      : seeds{ seeds }, stem{ stem }, branches{ branches } {}

  vecu get_seeds() const { return seeds; };
  vecu get_stem() const { return stem; };
  vecu get_branches() const { return branches; };
  vecu get_crown() const; // concatenate `stem` and `branches`.

  // check whether branches are searched
  arma::sword next_nodeidx(arma::umat& gidc) const;

  // vecu next_seeds() const;
  // vecu next_branches() const;
  // vecu next_stem() const;
  // Leaf next_leaf(const gumap& g) const;

  void print() const;

private:
  // `seeds`: searched nodes, each of which has been completely searched
  // for maximal cliques.
  // `branches`: nodes for next search.
  // `stem`: known cliques nodes in current leaf.
  // No intersections among `seeds`, `branches`, or `steam`.
  const vecu seeds, stem, branches;
};


Leaf NextLeaf(const Leaf& leaf, const gumap& g);

inline vecu Leaf::get_crown() const {
  vecu crown = branches;
  crown.insert(crown.end(), branches.begin(), branches.end());

  return crown;
}

// print `Leaf` obj
inline void Leaf::print() const {
  std::cout << "seeds are: ";
  Printvecu(seeds);

  std::cout << "stem is: ";
  Printvecu(stem);

  std::cout << "branch is: ";
  Printvecu(branches);
}
} // namespace lonelynodes

void SearchTree_(ln::vecvu&        cliques,
                 ln::vecvu&        sclique,
                 ln::vecvu&        nodes,
                 ln::vecvu&        xnodes,
                 ln::vecu&         srdnodes,
                 const arma::umat& gidc);

bool isMaximalClique_(const ln::vecu&   clique,
                      const ln::vecu&   srdnodes,
                      const arma::umat& gidc);

// void CompareClique_(ln::vecvu &cliques, ln::vecvu &sclique);

void TrimLeaf_(ln::vecvu&        sclique,
               ln::vecvu&        nodes,
               ln::vecvu&        xnodes,
               const arma::umat& gidc);

void BackTrimLeaf_(ln::vecvu&        sclique,
                   ln::vecvu&        nodes,
                   ln::vecvu&        xnodes,
                   const arma::umat& gidc);

void BackSkipLeaf_(ln::vecvu& sclique, ln::vecvu& nodes, ln::vecvu& xnodes);

bool isSkippable_(const ln::vecu&   eachSclique,
                  const ln::vecu&   eachNodes,
                  const arma::uword bestSize);

void SearchLeaf_(ln::vecvu&        sclique,
                 ln::vecvu&        nodes,
                 ln::vecvu&        xnodes,
                 ln::vecu&         srdnodes,
                 const arma::umat& gidc);

void NextLeaf_(ln::vecvu&        sclique,
               ln::vecvu&        nodes,
               ln::vecvu&        xnodes,
               const ln::vecu&   srdnodes,
               const arma::umat& gidc);

ln::gumap TrimGraph_(const ln::vecu& nodes, const ln::gumap& g);

#endif // _CLIQUE_H_

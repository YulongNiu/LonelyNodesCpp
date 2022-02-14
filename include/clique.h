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

  vecu        get_seeds() const { return seeds; };
  vecu        get_stem() const { return stem; };
  vecu        get_branches() const { return branches; };
  vecu        get_crown() const; // concatenate `stem` and `branches`.
  arma::uword get_node(const arma::uword idx) const;

  // check whether branches are searched
  arma::uword next_nodeidx(const arma::umat& gidc) const;

  vecu next_branches(const arma::uword idx, const arma::umat& gidc) const;
  vecu next_stem(const arma::uword idx) const;
  vecu next_seeds() const;

  vecu update_branches(arma::uword idx) const;
  vecu update_stem() const;
  vecu update_seeds(const arma::uword idx) const;

  void print() const;

private:
  // `seeds`: searched nodes, each of which has been completely searched
  // for maximal cliques.
  // `branches`: nodes for next search.
  // `stem`: known cliques nodes in current leaf.
  // No intersections among `seeds`, `branches`, or `steam`.
  const vecu seeds, stem, branches;
};

inline vecu Leaf::get_crown() const {
  vecu crown = stem;
  crown.insert(crown.end(), branches.begin(), branches.end());

  return crown;
}

inline arma::uword Leaf::get_node(const arma::uword idx) const {
  return branches.at(idx);
}

inline vecu Leaf::next_branches(const arma::uword idx,
                                const arma::umat& gidc) const {
  return IntersectNodes_(branches, this->get_node(idx), gidc);
}

inline vecu Leaf::next_stem(arma::uword idx) const {
  vecu res = stem;
  res.push_back(this->get_node(idx));
  return res;
}

inline vecu Leaf::next_seeds() const {
  return seeds;
}

inline vecu Leaf::update_branches(arma::uword idx) const {
  vecu res = branches;
  res.erase(res.begin() + idx);
  return res;
}

inline vecu Leaf::update_stem() const {
  return stem;
}

inline vecu Leaf::update_seeds(const arma::uword idx) const {
  vecu res = seeds;
  res.push_back(this->get_node(idx));
  return res;
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

Leaf NextLeaf(const Leaf& leaf, const gumap& g);
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

#ifndef _CLIQUE_H_
#define _CLIQUE_H_

#include <iostream>

#include "init.h"
#include "util.h"

namespace lonelynodes {

class Leaf {
public:
  //`snode`: next searched node.
  unsigned int snode;

  Leaf(const vecu seeds, const vecu branches, const vecu stem)
      : seeds{ seeds }, branches{ branches }, stem{ stem } {
    snode = branches.front();
  }

  vecu get_seeds() const { return seeds; };
  vecu get_branches() const { return branches; };
  vecu get_stem() const { return stem; };

  // next leaf functions
  vecu next_seeds() const;
  // vecu next_branches() const;
  // vecu next_stem() const;
  // Leaf next_leaf(const gumap& g) const;

  void print();

private:
  // `seeds`: searched nodes, each of which has been completely searched
  // for maximal cliques.
  // `branches`: nodes for next search.
  // `stem`: known cliques in current leaf.
  const vecu seeds, branches, stem;
};


Leaf NextLeaf(const Leaf& leaf, const gumap& g);

// print `Leaf` obj
inline void Leaf::print() {
  std::cout << "seeds are: ";
  Printvecu(seeds);

  std::cout << "stem is: ";
  Printvecu(stem);

  std::cout << "branch is: ";
  Printvecu(branches);
}

} // namespace lonelynodes

void SearchTree_(ln::vecvu&       cliques,
                 ln::vecvu&       sclique,
                 ln::vecvu&       nodes,
                 ln::vecvu&       xnodes,
                 ln::vecu&        srdnodes,
                 const ln::gumap& g);

bool isMaximalClique_(const ln::vecu&  clique,
                      const ln::vecu&  srdnodes,
                      const ln::gumap& g);

// void CompareClique_(ln::vecvu &cliques, ln::vecvu &sclique);

void TrimLeaf_(ln::vecvu&       sclique,
               ln::vecvu&       nodes,
               ln::vecvu&       xnodes,
               const ln::gumap& g);

void BackTrimLeaf_(ln::vecvu&       sclique,
                   ln::vecvu&       nodes,
                   ln::vecvu&       xnodes,
                   const ln::gumap& g);

void BackSkipLeaf_(ln::vecvu& sclique, ln::vecvu& nodes, ln::vecvu& xnodes);

bool isSkippable(const ln::vecu&   eachSclique,
                 const ln::vecu&   eachNodes,
                 unsigned long int bestSize);

void SearchLeaf_(ln::vecvu&       sclique,
                 ln::vecvu&       nodes,
                 ln::vecvu&       xnodes,
                 const ln::vecu&  srdnodes,
                 const ln::gumap& g);

void NextLeaf_(ln::vecvu&       sclique,
               ln::vecvu&       nodes,
               ln::vecvu&       xnodes,
               const ln::vecu&  srdnodes,
               const ln::gumap& g);

ln::gumap TrimGraph_(const ln::vecu& nodes, const ln::gumap& g);

ln::vecu SortNodes_(const ln::vecu& nodes, const ln::gumap& g);

void Count_(ln::vecu& degree, const ln::vecu& nodes, const ln::vecu& tnodes);

ln::vecu SortIdx_(const ln::vecu& v);

#endif // _CLIQUE_H_

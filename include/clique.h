#ifndef _CLIQUE_H_
#define _CLIQUE_H_

#include <iostream>

#include "init.h"
#include "util.h"

namespace lonelynodes {

class Leaf {
public:
  Leaf();
  Leaf(vecu, vecu, vecu);
  void print();

private:
  // searched nodes, each of which has been completely searched
  // for maximal cliques.
  vecu seeds;

  vecu branches; // nodes for next search.
  vecu stem;     // known cliques in current search.
};

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

void TrimLeaf_(ln::vecvu& sclique, ln::vecvu& nodes, ln::vecvu& xnodes);

void BackSkipLeaf_(ln::vecvu& sclique, ln::vecvu& nodes, ln::vecvu& xnodes);

void SearchLeaf_(ln::vecvu&       sclique,
                 ln::vecvu&       nodes,
                 ln::vecvu&       xnodes,
                 const ln::vecu&  srdnodes,
                 const ln::gumap& g);

void NextLeaf_(ln::vecvu& sclique, ln::vecvu& nodes, const ln::gumap& g);

void PushHead_(ln::vecvu&      sclique,
               ln::vecvu&      nodes,
               ln::vecvu&      xnodes,
               const ln::vecu& srdnodes);

ln::vecu SortNodes_(const ln::vecu& nodes, const ln::gumap& g);

void Count_(ln::vecu& degree, const ln::vecu& nodes, const ln::vecu& tnodes);

ln::vecu SortIdx_(const ln::vecu& v);

#endif // _CLIQUE_H_

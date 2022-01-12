#ifndef _CLIQUE_H_
#define _CLIQUE_H_

#include <iostream>

#include "init.h"
#include "util.h"

namespace lonelynodes {

class Seed {
public:
  vecu stem;          // known cliques
  vecu branches;      // nodes for next search
  unsigned int level; // record level

  void print() {
    std::cout << "stem is: ";
    Printvecu(stem);

    std::cout << "branch is: ";
    Printvecu(branches);

    std::cout << "level is: " << level << std::endl;
  }
};

} // namespace lonelynodes

void SearchTree_(ln::vecvu &cliques, ln::vecvu &sclique, ln::vecvu &nodes,
                 ln::vecvu &xnodes, ln::vecu &srdnodes, const ln::gumap &g);

bool isMaximalClique_(const ln::vecu &clique, const ln::vecu &srdnodes,
                      const ln::gumap &g);

// void CompareClique_(ln::vecvu &cliques, ln::vecvu &sclique);

void TrimLeaf_(ln::vecvu &sclique, ln::vecvu &nodes, ln::vecvu &xnodes);

void BackSkipLeaf_(ln::vecvu &sclique, ln::vecvu &nodes, ln::vecvu &xnodes);

void SearchLeaf_(ln::vecvu &sclique, ln::vecvu &nodes, ln::vecvu &xnodes,
                 const ln::vecu &srdnodes, const ln::gumap &g);

void NextLeaf_(ln::vecvu &sclique, ln::vecvu &nodes, const ln::gumap &g);

void PushHead_(ln::vecvu &sclique, ln::vecvu &nodes, ln::vecvu &xnodes,
               const ln::vecu &srdnodes);

ln::vecu SortNodes_(const ln::vecu &nodes, const ln::gumap &g);

void Count_(ln::vecu &degree, const ln::vecu &nodes, const ln::vecu &tnodes);

ln::vecu SortIdx_(const ln::vecu &v);

#endif // _CLIQUE_H_

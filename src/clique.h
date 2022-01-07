#ifndef _CLIQUE_H_
#define _CLIQUE_H_

#include <iostream>

#include "util.h"
#include "init.h"

namespace lonelynodes {

  class Seed {
  public:
    vecu stem; // known cliques
    vecu branches; // nodes for next search
    unsigned int level; // record level

    void print(){
      std::cout << "stem is: ";
      Printvecu(stem);

      std::cout << "branch is: ";
      Printvecu(branches);

      std::cout << "level is: " << level << std::endl;
    }
  };

}

ln::vecvu MaxCliques(const ln::gumap& g,
                     const unsigned int node);

void SearchTree_(ln::vecvu& cliques,
                 ln::vecvu& sclique,
                 ln::vecvu& nodes,
                 const ln::gumap& g);

void CompareClique_(ln::vecvu& cliques,
                    ln::vecvu& sclique);

void TrimLeaf_(ln::vecvu& sclique,
               ln::vecvu& nodes,
               const unsigned int bestSize);

void SearchLeaf_(ln::vecvu& cliques,
                 ln::vecvu& nodes,
                 const ln::gumap& g);

void NextLeaf_(ln::vecvu& sclique,
               ln::vecvu& nodes,
               const ln::gumap& g);

void PushHead_(ln::vecvu& cliques,
               ln::vecvu& nodes);

ln::vecu SortNodes_(const ln::vecu& nodes,
                    const ln::gumap& g);

void Count_(ln::vecu& degree,
            const ln::vecu& nodes,
            const ln::vecu& tnodes);

ln::vecu SortIdx_(const ln::vecu& v);

#endif // _CLIQUE_H_

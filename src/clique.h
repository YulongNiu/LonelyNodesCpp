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


ln::vecvu FindAllCliques2(const ln::vecu& nodes,
                          const ln::gumap& g);

void SearchForest_(ln::vecvu& cliques,
                   ln::vecu& roots,
                   const ln::vecu& lnodes,
                   const ln::gumap& g);

void SearchTree_(ln::vecvu& cliques,
                 ln::vecvu& sclique,
                 ln::vecvu& nodes,
                 const ln::gumap& g);

void TrimLeaf_(ln::vecvu& sclique,
               ln::vecvu& nodes);

void SearchLeaf_(ln::vecvu& cliques,
                 ln::vecvu& nodes,
                 const ln::gumap& g);

void NextLeaf_(ln::vecvu& sclique,
               ln::vecvu& nodes,
               const ln::gumap& g);

void PushHead_(ln::vecvu& cliques,
               ln::vecvu& nodes);


#endif // _CLIQUE_H_

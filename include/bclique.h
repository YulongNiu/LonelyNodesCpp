#ifndef _BCLIQUE_H_
#define _BCLIQUE_H_

#include "util.h"

void bBackSkipLeaf_(ln::vecdbit& sclique,
                    ln::vecdbit& nodes,
                    ln::vecvu&   xnodes);

bool bisSkippable_(const ln::dbit&   eachSclique,
                   const ln::dbit&   eachNodes,
                   const arma::uword bestSize);

void bSearchLeaf_(ln::vecdbit&       sclique,
                  ln::vecdbit&       nodes,
                  ln::vecvu&         xnodes,
                  const ln::vecu&    srdnodes,
                  const ln::vecdbit& gidc);


void bNextLeaf_(ln::vecdbit&       sclique,
                ln::vecdbit&       nodes,
                ln::vecvu&         xnodes,
                const ln::vecu&    srdnodes,
                const ln::vecdbit& gdbit);

#endif // _BCLIQUE_H_

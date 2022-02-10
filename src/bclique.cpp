#include "bclique.h"
#include "util.h"

using namespace std;
using namespace ln;


// `BackSkipLeaf_()` is a quick skip method.
void bBackSkipLeaf_(ln::vecdbit& sclique,
                    ln::vecdbit& nodes,
                    ln::vecvu&   xnodes) {

  if (nodes.empty()) { return; }

  auto ps = next(sclique.rbegin());
  auto pn = next(nodes.rbegin());
  auto px = next(xnodes.rbegin());

  for (auto bestSize = sclique.back().count();
       (pn != nodes.rend()) && bisSkippable_(*ps, *pn, bestSize);
       ++ps, ++pn, ++px) {}

  sclique.erase(ps.base(), sclique.end());
  nodes.erase(pn.base(), nodes.end());
  xnodes.erase(px.base(), xnodes.end());
}


bool bisSkippable_(const ln::dbit&   eachSclique,
                   const ln::dbit&   eachNodes,
                   const arma::uword bestSize) {
  return (eachSclique.count() + eachNodes.count()) < bestSize;
}


// find one clique by search the left tree
void bSearchLeaf_(ln::vecdbit&       sclique,
                  ln::vecdbit&       nodes,
                  ln::vecvu&         xnodes,
                  const ln::vecu&    srdnodes,
                  const ln::vecdbit& gidc) {

  if (nodes.back().none()) { return; }

  // push head and generate new clique
  bNextLeaf_(sclique, nodes, xnodes, srdnodes, gidc);

  // recursion
  bSearchLeaf_(sclique, nodes, xnodes, srdnodes, gidc);
}


void bNextLeaf_(ln::vecdbit&       sclique,
                ln::vecdbit&       nodes,
                ln::vecvu&         xnodes,
                const ln::vecu&    srdnodes,
                const ln::vecdbit& gdbit) {

  // step1: next search node.
  // `searchNode` is index of next search node,
  // which is always the most left nodes.
  // then erase `searchNode` in previous nodes.
  auto searchNode = nodes.back().find_first();
  nodes.back().reset(searchNode);

  // step2: next `xnodes`
  // push `searchNode` to the end of last elem in `xnodes`;
  // push `srdnodes` to the end of `xnodes`.
  xnodes.back().push_back(searchNode);
  xnodes.push_back(srdnodes);

  // step3: next `sclique`
  // push `searchNode` to the end of `lastClique`;
  // push `lastClique` to the end of `clique`.
  auto nextClique = sclique.back(); // never empty!
  nextClique.set(searchNode);
  sclique.push_back(nextClique);

  // step4: next nodes
  auto nextNodes = nodes.back() & gdbit.at(searchNode);
  nodes.push_back(nextNodes);
}

#include <algorithm> //std::stable_sort std::sort std::includes
#include <iostream>
#include <unordered_map>

#include "clique.h"
#include "init.h"
#include "util.h"

using namespace std;

namespace lonelynodes {

// Leaf NextLeaf(const Leaf& leaf, const gumap& g) {
//   auto searchNode = leaf.snode;

//   // push `searchNode` to the end of last elem in `nseeds`;
//   auto nseeds = leaf.get_seeds();
//   nseeds.push_back(searchNode);

//   // push `searchNode` to the end of `nstem`;
//   auto nstem = leaf.get_stem();


//   // push `lastClique` to the end of `clique`.
//   auto lastClique = sclique.back(); // never empty!
//   lastClique.push_back(searchNode);


//   // erase 1st node of `searchNodes`
//   nodes.back().erase(nodes.back().begin());

//   // next leaf
//   searchNodes leaf = ;
// }

// search for the next leaf
vecu Leaf::next_seeds() const {
  vecu res = seeds;
  res.push_back(snode);
  return res;
}

// Leaf::next_leaf(const gumap& g) const {}


} // namespace lonelynodes

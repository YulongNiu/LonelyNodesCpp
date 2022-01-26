#include <iostream>
#include <numeric>
#include <vector>

#include "init.h"
#include "util.h"

using namespace std;
using namespace lonelynodes;


// indicator of intersection in `fv`
ln::vecu IntersectionIdc_(const ln::vecu& fv, const ln::vecu& tv) {
  auto fvsize = fv.size();
  auto tvsize = tv.size();
  vecu res(fvsize, 0);

  for (size_t i = 0; i < fvsize; ++i) {

    size_t j = 0;
    for (; (j < tvsize) && (fv.at(i) != tv.at(j)); ++j) {}
    if (j != tvsize) { res.at(i) = 1; }
  }

  return res;
}


// first non-intersection node
// `nodes` and `indicator`.
// `indicator` is a bit vector
ln::citerv NextPnode_(const ln::vecu& eachNodes,
                      const ln::vecu& eachIndicators) {
  auto pnode = eachNodes.begin();

  for (auto i = eachIndicators.begin();
       (i != eachIndicators.end() && (*i == 1));
       ++i, ++pnode) {}

  return pnode;
}


// longest intersection
ln::vecu NextIdc_(const ln::vecu&  eachNodes,
                  const ln::vecu&  eachXnodes,
                  const ln::gumap& g) {
  size_t maxSize = 0;
  vecu   res(eachNodes.size(), 0);

  if (eachXnodes.empty()) { return res; }

  for (auto elem : eachXnodes) {
    auto eachIdc  = IntersectionIdc_(eachNodes, g.at(elem));
    auto eachSize = accumulate(eachIdc.begin(), eachIdc.end(), 0);
    if (eachSize > maxSize) {
      res     = eachIdc;
      maxSize = eachSize;
    } else {
    }
  }

  return res;
}


ln::vecu NextLeaf_(const ln::vecu     eachNodes,
                   const unsigned int searchNode,
                   const ln::gumap&   g) {

  return Intersection(eachNodes, g.at(searchNode));
}

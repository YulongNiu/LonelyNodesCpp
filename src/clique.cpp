#include <unordered_map>
#include <vector> // std::insert
#include <algorithm>

#include "util.h"
#include "init.h"
#include "clique.h"

using namespace std;
using namespace lonelynodes;


// find cliques by search the left tree
void SearchTree_(ln::vecvu& cliques,
                 ln::vecvu& sclique,
                 ln::vecvu& nodes,
                 const ln::gumap& g) {

  do {
    // step1: search left leaf
    SearchLeaf_(sclique, nodes, g);
    CompareClique_(cliques, sclique);

    // step2: trim if leaf exist.
    TrimLeaf_(sclique, nodes);

    cout << "1st nodes size: " << nodes.front().size() <<
      "; sclique size: " << sclique.size() <<
      "; nodes size: " << nodes.size() <<
      "; cliques size: " << cliques.size() << endl;

  } while (!nodes.empty());

}



// if new cliques is larger, then replace all old cliques.
// if new cliques' size is equal with old cliques, then append.
void CompareClique_(ln::vecvu& cliques,
                    ln::vecvu& sclique) {

  auto existSize = cliques.back().size();
  auto newSize = sclique.back().size();

  if (newSize == existSize) {
    cliques.push_back(sclique.back());
  }
  else if (newSize > existSize) {
    cliques.erase(cliques.begin(), cliques.end());
    cliques.push_back(sclique.back());
  }
  else {}

}


// void SearchTree_(ln::vecvu& cliques,
//                  ln::vecvu& sclique,
//                  ln::vecvu& nodes,
//                  const ln::gumap& g) {

//   if (nodes.empty()) {
//     return;
//   } else {}

//   // step1: search left leaf, then trim if leaf exist.
//   SearchLeaf_(sclique, nodes, g);
//   cliques.push_back(sclique.back());

//   TrimLeaf_(sclique, nodes);

//   cout << "1st nodes size: " << nodes.front().size() <<
//     "; sclique size: " << sclique.size() <<
//     "; nodes size: " << nodes.size() <<
//     "; cliques size: " << cliques.size() << endl;

//   // step2: recursion
//   SearchTree_(cliques, sclique, nodes, g);
// }


// case1 (1 node): TrimLeaf_({{0}, {0, 1}}, {{}, {}})
// case2 (typical): TrimLeaf_({{0}, {0, 3}, {0, 3, 4}, {0, 3, 4, 5}}, {{4, 5}, {5}, {}, {}}
// @keywords internal
void TrimLeaf_(ln::vecvu& sclique,
               ln::vecvu& nodes) {

  // optimization:
  // 1. check if `sclique.back().size()` is the largest so far.
  // 2. last elem of `sclique` is always is the best, so skip.
  auto ps = next(sclique.rbegin());
  auto pn = next(nodes.rbegin());
  auto bestSize = sclique.back().size();

  for (; pn != nodes.rend(); ++ps, ++pn) {

    auto eachSize = (*ps).size() + (*pn).size();

    if (eachSize >= bestSize) {
      break;
    } else {}
  }

  sclique.erase(ps.base(), sclique.end());
  nodes.erase(pn.base(), nodes.end());
}



// find one clique by search the left tree
void SearchLeaf_(ln::vecvu& sclique,
                 ln::vecvu& nodes,
                 const ln::gumap& g) {

  if (nodes.back().empty()) {
    // no nodes left, then end.
    return;
  } else {}

  // step1: push head and generate new clique
  PushHead_(sclique, nodes);

  // step2: migrate common elems of `nodes` to end, then delete common elems in previous end.
  NextLeaf_(sclique, nodes, g);

  // step3: recursion
  SearchLeaf_(sclique, nodes, g);
}


void NextLeaf_(ln::vecvu& sclique,
               ln::vecvu& nodes,
               const ln::gumap& g) {

  auto searchNode = sclique.back().back();
  auto nextLinkNodes = g.at(searchNode);

  auto nextNodes = Intersection(nodes.back(), nextLinkNodes);
  nodes.push_back(nextNodes);
}


void PushHead_(ln::vecvu& sclique,
               ln::vecvu& nodes) {

  vecu lastNodes = nodes.back();
  vecu lastClique = sclique.back(); // never empty!

  // push 1st nodes of `lastNodes` to
  // the end of `lastClique`;
  // push `lastClique` to
  // the end of `clique`.
  lastClique.push_back(lastNodes.front());
  sclique.push_back(lastClique);

  // erase 1st node of `lastNodes`
  nodes.back().erase(nodes.back().begin());

}



// // expand nodes into children nodes
// // @keywords internal
// void ExpandLeaf_(const vecu& stem,
//                  const vecu& branches,
//                  const gumap& g) {

//   vecu b = branches;

//   do {
//     // step1: add first node to stem.
//     auto node = b.front();
//     b.erase(b.begin());

//     vecu newSteam = stem;
//     newSteam.push_back(node);

//     // step2: common nodes as new branch.
//     vecu newBranch = Intersection(branches, g.at(node));

//     // step3: remove searched nodes.
//     b = Difference(b, newBranch);

//     cout << "stem is: ";
//     Printvecu(newSteam);
//     cout << "branch is: ";
//     Printvecu(newBranch);
//   } while (b.size() > 0);
// }



// // [[Rcpp::export]]
// void TestExpandLeaf(const arma::umat& m,
//                     const arma::uword node) {

//   auto g = gumapInit(m);

//   vecu stem = {node};
//   vecu branches = g.at(node);

//   ExpandLeaf_(stem, branches, g);

//   Seed firstSeed;
//   firstSeed.stem = {node};
//   firstSeed.branches = g.at(node);
//   firstSeed.print();
// }

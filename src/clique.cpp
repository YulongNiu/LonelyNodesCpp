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
    cliques.push_back(sclique.back());

    // step2: trim if leaf exist.
    TrimLeaf_(sclique, nodes);

    cout << "1st nodes size: " << nodes.front().size() <<
      "; sclique size: " << sclique.size() <<
      "; nodes size: " << nodes.size() <<
      "; cliques size: " << cliques.size() << endl;

  } while (!nodes.empty());

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


// case1: TrimLeaf_({{0}, {0, 1}}, {{}, {}})
// case2: TrimLeaf_({{0}, {0, 1}, {0, 1, 2}}, {{4, }, {3}, {}})
// @keywords internal
void TrimLeaf_(ln::vecvu& sclique,
               ln::vecvu& nodes) {

  // trim from the end, and size of `nodes` > 1.
  // end of `nodes` is always empty, so end is skipped.
  auto ps = sclique.rbegin() + 1;
  auto pn = nodes.rbegin() + 1;

  for (; pn != nodes.rend(); ++ps, ++pn) {
    if ((*pn).size() - (*(pn - 1)).size() > 1) {
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

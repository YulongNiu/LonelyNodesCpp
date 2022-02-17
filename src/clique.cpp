#include "clique.h"
#include "init.h"
#include "pivot.h"
#include "util.h"

using namespace arma;
using namespace std;
using namespace ln;

void SearchTree_(ln::vecvu&        cliques,
                 ln::vecvu&        sclique,
                 ln::vecvu&        nodes,
                 ln::vecvu&        xnodes,
                 ln::vecu&         srdnodes,
                 const arma::umat& gidc) {

  do {
    // step1: search left leaf.
    SearchLeaf_(sclique, nodes, xnodes, srdnodes, gidc);

    // step2: check if latest clique is maximal.
    // `eachClique` must be checked, because now we only trim
    // according to ONE `xnodes`. We do not know the it is a
    // maximal clique or not, when `nodes.back().empty()` is true.
    // For example, `nodes` has two searched parts belong
    // to `xnodes1` and `xnodes2`.
    auto eachClique = sclique.back();
    if (isMaximalClique_(eachClique, srdnodes, gidc)) {
      cliques.push_back(eachClique);
    }

    // step3: trim leaves, if exist.
    // May be empty after trim.
    TrimLeaf_(sclique, nodes, xnodes, gidc);
    if (!nodes.empty()) { srdnodes = xnodes.back(); }

    cout << "1st nodes size: " << nodes.front().size()
         << "; node size: " << nodes.size() << "; #cliques: " << cliques.size()
         << "; srnodes is: ";
    Printvecu(srdnodes);
  } while (!nodes.empty());
}


void PrintTreeInfo_(const ln::vecvu& cliques,
                    const ln::vecvu& sclique,
                    const ln::vecvu& nodes,
                    const ln::vecvu& xnodes,
                    const ln::vecu&  srdnodes,
                    const string     pos) {

  cout << "~~~~~~~~~~~~~~~~~~~\n";
  cout << pos + " trim \n";
  cout << "cliques are: \n";
  Printvecvu(cliques);
  cout << "scliques are: \n";
  Printvecvu(sclique);
  cout << "nodes are: \n";
  Printvecvu(nodes);
  cout << "xnodes are: \n";
  Printvecvu(xnodes);
  cout << "srdnodes are: \n";
  Printvecu(srdnodes);
  cout << "end." << endl;
  cout << "~~~~~~~~~~~~~~~~~~~~\n\n\n";
}


// void SearchTree_(ln::vecvu&        cliques,
//                  ln::vecvu&        sclique,
//                  ln::vecvu&        nodes,
//                  ln::vecvu&        xnodes,
//                  ln::vecu&         srdnodes,
//                  const arma::umat& gidc) {

//   for (uword i = 0; i < 10 && !nodes.empty(); ++i) {

//     cout << "First node size is: \n" << nodes.front().size() << endl;
//     cout << "First node is: \n";
//     Printvecu(nodes.front());

//     // step1: search left leaf.
//     SearchLeaf_(sclique, nodes, xnodes, srdnodes, gidc);

//     // step2: check if latest clique is maximal.
//     auto eachClique = sclique.back();
//     if (isMaximalClique_(eachClique, srdnodes, gidc)) {
//       cliques.push_back(eachClique);
//     }

//     PrintTreeInfo_(cliques, sclique, nodes, xnodes, srdnodes, "before");

//     // step3: trim leaves, if exist.
//     TrimLeaf_(sclique, nodes, xnodes, gidc);
//     if (!nodes.empty()) { srdnodes = xnodes.back(); }

//     cout << "1st nodes size: " << nodes.front().size()
//          << "; node size: " << nodes.size() << "; #cliques: " <<
//          cliques.size()
//          << endl;

//     PrintTreeInfo_(cliques, sclique, nodes, xnodes, srdnodes, "after");
//   }


//   // //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//   // cout << "First node size is: \n" << nodes.front().size() << endl;
//   // cout << "First node is: \n";
//   // Printvecu(nodes.front());

//   // SearchLeaf_(sclique, nodes, xnodes, srdnodes, gidc);
//   // auto eachClique = sclique.back();
//   // if (isMaximalClique_(eachClique, srdnodes, gidc)) {
//   //   cliques.push_back(eachClique);
//   // }

//   // PrintTreeInfo_(cliques, sclique, nodes, xnodes, srdnodes, "before");

//   // // BackSkipLeaf_(sclique, nodes, xnodes);
//   // // BackTrimLeaf_(sclique, nodes, xnodes, gidc);
//   // TrimLeaf_(sclique, nodes, xnodes, gidc);
//   // if (!nodes.empty()) { srdnodes = xnodes.back(); }

//   // cout << "1st nodes size: " << nodes.front().size()
//   //      << "; node size: " << nodes.size() << "; #cliques: " <<
//   cliques.size()
//   //      << endl;

//   // PrintTreeInfo_(cliques, sclique, nodes, xnodes, srdnodes, "after");
//   // //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// }


// Check if one clique is maximal.
bool isMaximalClique_(const ln::vecu&   clique,
                      const ln::vecu&   srdnodes,
                      const arma::umat& gidc) {

  if (srdnodes.empty()) { return true; }

  umat splitIdc = gidc.submat(STD2ARMAuv(clique), STD2ARMAuv(srdnodes));

  uword i = 0;
  for (; i != splitIdc.n_cols && (!all(splitIdc.col(i))); ++i) {}

  return i == splitIdc.n_cols;
}


// // for maximum clique
// // if new cliques is larger, then replace all old cliques.
// // if new cliques' size is equal with old cliques, then append.
// void CompareClique_(ln::vecvu& cliques,
//                     ln::vecvu& sclique) {

//   auto existSize = cliques.back().size();
//   auto newSize = sclique.back().size();

//   if (newSize == existSize) {
//     cliques.push_back(sclique.back());
//   }
//   else if (newSize > existSize) {
//     cliques.erase(cliques.begin(), cliques.end());
//     cliques.push_back(sclique.back());
//   }
//   else {}

// }


// case1 (1 node):
// TrimLeaf_({{0}, {0, 1}}, {{}, {}})
//
// case2 (typical):
// TrimLeaf_({{0}, {0, 3}, {0, 3, 4}, {0, 3, 4, 5}},
// {{4, 5}, {5}, {}, {}})

// optimization:
// 1. backtrack: check if `sclique.back().size()` is the largest so far.
void TrimLeaf_(ln::vecvu&        sclique,
               ln::vecvu&        nodes,
               ln::vecvu&        xnodes,
               const arma::umat& gidc) {

  // quick back skip
  BackSkipLeaf_(sclique, nodes, xnodes);

  // skip longest maximal clique
  BackTrimLeaf_(sclique, nodes, xnodes, gidc);
}


// `BackTrimLeaf_()` jump over nodes all in **one** maximal clique
void BackTrimLeaf_(ln::vecvu&        sclique,
                   ln::vecvu&        nodes,
                   ln::vecvu&        xnodes,
                   const arma::umat& gidc) {

  if (nodes.empty()) { return; }

  auto lastNodes = nodes.back();
  auto nextIdx   = NextNodeIdx_(sclique.back(), lastNodes, xnodes.back(), gidc);
  auto pnode     = lastNodes.begin() + nextIdx;

  if (pnode != lastNodes.end()) {
    // swap
    iter_swap(pnode, lastNodes.begin());
    nodes.back() = lastNodes;
    return;
  } else {
    // skip
    sclique.pop_back();
    nodes.pop_back();
    xnodes.pop_back();
  }

  BackTrimLeaf_(sclique, nodes, xnodes, gidc);
}


// `BackSkipLeaf_()` is a quick skip method.
void BackSkipLeaf_(ln::vecvu& sclique, ln::vecvu& nodes, ln::vecvu& xnodes) {

  if (nodes.empty()) { return; }

  auto ps = next(sclique.rbegin());
  auto pn = next(nodes.rbegin());
  auto px = next(xnodes.rbegin());

  for (auto bestSize = sclique.back().size();
       (pn != nodes.rend()) && isSkippable_(*ps, *pn, bestSize);
       ++ps, ++pn, ++px) {}

  sclique.erase(ps.base(), sclique.end());
  nodes.erase(pn.base(), nodes.end());
  xnodes.erase(px.base(), xnodes.end());
}


bool isSkippable_(const ln::vecu&   eachSclique,
                  const ln::vecu&   eachNodes,
                  const arma::uword bestSize) {
  return (eachSclique.size() + eachNodes.size()) < bestSize;
}


// find one clique by search the left tree
void SearchLeaf_(ln::vecvu&        sclique,
                 ln::vecvu&        nodes,
                 ln::vecvu&        xnodes,
                 ln::vecu&         srdnodes,
                 const arma::umat& gidc) {

  if (nodes.back().empty()) { return; }

  // push head and generate new clique
  NextLeaf_(sclique, nodes, xnodes, srdnodes, gidc);

  //~~~~~~~~~~~check if skippable~~~~~~~~~~~~
  if (nodes.back().empty()) { return; } // find clique and break

  BackTrimLeaf_(sclique, nodes, xnodes, gidc);
  if (nodes.empty()) { return; } // trim to top
  srdnodes = xnodes.back();
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  // recursion
  SearchLeaf_(sclique, nodes, xnodes, srdnodes, gidc);
}


// always search left node
void NextLeaf_(ln::vecvu&        sclique,
               ln::vecvu&        nodes,
               ln::vecvu&        xnodes,
               const ln::vecu&   srdnodes,
               const arma::umat& gidc) {

  // step1: next search node.
  // `searchNode` is always the most left nodes.
  // then erase `searchNode` in previous nodes.
  auto searchNode = nodes.back().front();
  nodes.back().erase(nodes.back().begin());

  // step2: next `xnodes`
  // push `searchNode` to the end of last elem in `xnodes`;
  // push `srdnodes` to the end of `xnodes`.
  xnodes.back().push_back(searchNode);
  xnodes.push_back(srdnodes);

  // step3: next `sclique`
  // push `searchNode` to the end of `lastClique`;
  // push `lastClique` to the end of `clique`.
  auto nextClique = sclique.back(); // never empty!
  nextClique.push_back(searchNode);
  sclique.push_back(nextClique);

  // step4: next nodes
  auto nextNodes = IntersectNodes_(nodes.back(), searchNode, gidc);
  nodes.push_back(nextNodes);
}

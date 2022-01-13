#include <unordered_map>
#include <algorithm> //std::stable_sort std::sort std::includes

#include "util.h"
#include "init.h"
#include "clique.h"
#include <iostream>

using namespace std;
using namespace lonelynodes;

// // find maximum clique(s) by a given `node` in graph `g`.
// ln::vecvu MaxCliques(const ln::gumap& g,
//                      const unsigned int node) {

//   // step1: sort nodes according to degree by decreasing order.
//   // auto lnodes = SortNodes_(g.at(node), g);
//   auto lnodes = g.at(node);
//   vecvu cliques{{}};
//   vecvu sclique = {{node}};
//   vecvu nodes = {lnodes};

//   // step2: search
//   SearchTree_(cliques, sclique, nodes, g);

//   return cliques;
// }

void SearchTree_(ln::vecvu &cliques,
                 ln::vecvu &sclique, ln::vecvu &nodes,
                 ln::vecvu &xnodes, ln::vecu &srdnodes,
                 const ln::gumap &g) {

  do {
    // step1: search left leaf.
    SearchLeaf_(sclique, nodes, xnodes, srdnodes, g);


    // cout << "------\n"
    //      << "srdnodes: \n";
    // Printvecu(srdnodes);
    // cout << "xnodes: \n";
    // Printvecvu(xnodes);
    // cout << "end"
    //      << "sclique: \n";
    // Printvecvu(sclique);
    // cout << "end\n"
    //      << "nodes: \n";
    // Printvecvu(nodes);
    // cout << "end \n"
    //      << "is maximal clique: " << isMaximalClique_(sclique.back(), srdnodes, g)
    //      << "\n------\n" << endl;

    // step2: check if latest clique is maximal.
    auto eachClique = sclique.back();
    if (isMaximalClique_(eachClique, srdnodes, g)) {
      cliques.push_back(eachClique);
      // CompareClique_(cliques, sclique);
    } else {}

    // step3: trim leaves, if exist.
    TrimLeaf_(sclique, nodes, xnodes);
    srdnodes = xnodes.back();

    cout << "1st nodes size: " << nodes.front().size()
         << "; nodes size: " << nodes.size()
         << "; last node size: " << nodes.back().size()
         << "; #cliques: " << cliques.size() << endl;

  } while (!nodes.empty());
}


// Check if one clique is maximal.
bool isMaximalClique_(const ln::vecu &clique, const ln::vecu &srdnodes,
                      const ln::gumap &g) {

  vecu cliqueSort = clique;
  sort(cliqueSort.begin(), cliqueSort.end());

  // if `srdnodes` is empty
  if (srdnodes.empty()) {
    return true;
  } else {}

  for (auto elem : srdnodes) {
    // `cliqueSort` a subset of linked nodes of `elem`.
    vecu lnodes = g.at(elem);
    sort(lnodes.begin(), lnodes.end());

    if (includes(lnodes.begin(), lnodes.end(), cliqueSort.begin(),
                 cliqueSort.end())) {
      return false;
    } else {}
  }

  return true;
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


// case1 (1 node): TrimLeaf_({{0}, {0, 1}}, {{}, {}})
// case2 (typical): TrimLeaf_({{0}, {0, 3}, {0, 3, 4}, {0, 3, 4, 5}}, {{4, 5}, {5}, {}, {}}
// optimization:
// 1. backtrack:
// 1. check if `sclique.back().size()` is the largest so far.
void TrimLeaf_(ln::vecvu &sclique, ln::vecvu &nodes, ln::vecvu &xnodes) {

  BackSkipLeaf_(sclique, nodes, xnodes);
}

void BackSkipLeaf_(ln::vecvu &sclique, ln::vecvu &nodes, ln::vecvu &xnodes) {

  auto ps = next(sclique.rbegin());
  auto pn = next(nodes.rbegin());
  auto px = next(xnodes.rbegin());

  auto bestSize = sclique.back().size();

  for (; pn != nodes.rend(); ++ps, ++pn, ++px) {

    auto eachSize = (*ps).size() + (*pn).size();

    if (eachSize >= bestSize) {
      break;
    } else {
    }
  }

  sclique.erase(ps.base(), sclique.end());
  nodes.erase(pn.base(), nodes.end());
  xnodes.erase(px.base(), xnodes.end());
}

// find one clique by search the left tree
void SearchLeaf_(ln::vecvu& sclique,
                 ln::vecvu& nodes,
                 ln::vecvu& xnodes,
                 const ln::vecu& srdnodes,
                 const ln::gumap& g) {

  if (nodes.back().empty()) {
    // no nodes left, then end.
    return;
  } else {}

  // step1: push head and generate new clique
  PushHead_(sclique, nodes, xnodes, srdnodes);

  // step2: migrate common elems of `nodes` to end, then delete common elems in previous end.
  NextLeaf_(sclique, nodes, g);

  // step3: recursion
  SearchLeaf_(sclique, nodes, xnodes, srdnodes, g);
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
               ln::vecvu& nodes,
               ln::vecvu& xnodes,
               const ln::vecu& srdnodes) {

  auto searchNode = nodes.back().front();

  // push `searchNode` to the end of `lastClique`;
  // push `lastClique` to the end of `clique`.
  auto lastClique = sclique.back(); // never empty!
  lastClique.push_back(searchNode);
  sclique.push_back(lastClique);

  // push `searchNode` to the end of last elem in `xnodes`;
  // push `srdnodes` to the end of `xnodes`.
  xnodes.back().push_back(searchNode);
  xnodes.push_back(srdnodes);

  // erase 1st node of `searchNodes`
  nodes.back().erase(nodes.back().begin());
}


// sort linked nodes by the degree in decreasing order.
ln::vecu SortNodes_(const ln::vecu& nodes,
                    const ln::gumap& g) {

  // step1: count degree
  vecu degree(nodes.size(), 0);

  for (auto elem : nodes) {
    Count_(degree, nodes, g.at(elem));
  }

  // step2: decreasing order of degree
  auto degreeIdx = SortIdx_(degree);

  vecu res(nodes.size());
  auto pres = res.begin();
  auto pdi = degreeIdx.rbegin();
  for (;
       pdi != degreeIdx.rend();
       *pres = nodes.at(*pdi), ++pres, ++pdi) {}

  return res;
}


void Count_(ln::vecu& degree,
            const ln::vecu& nodes,
            const ln::vecu& tnodes) {

  for (unsigned int i = 0; i < nodes.size(); ++i) {

    auto snode = nodes.at(i);
    for (auto p = tnodes.begin(); p != tnodes.end(); ++p) {
      if (snode == *p) {
        ++degree.at(i);
        break;
      } else {}
    }

  }
}

ln::vecu SortIdx_(const ln::vecu& v) {

  // get index in not decreasing order
  vecu idx(v.size());
  iota(idx.begin(), idx.end(), 0);

  stable_sort(idx.begin(), idx.end(),
              [&v](size_t i1, size_t i2) {
                return v[i1] < v[i2];
              });

  return idx;
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

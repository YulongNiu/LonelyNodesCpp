#include <cstddef>
#include <iostream>

#include "clique.h"
#include "init.h"
#include "pivot.h"
#include "util.h"

using namespace std;
using namespace lonelynodes;
using namespace arma;

void TestDiffIntersect(ln::vecu& fv, ln::vecu& tv) {
  cout << "original fv is: " << '\n';
  Printvecu(fv);
  cout << "original tv is: " << '\n';
  Printvecu(tv);

  DiffIntersect(fv, tv);

  cout << "processed fv is: " << '\n';
  Printvecu(fv);
  cout << "processed tv is: " << '\n';
  Printvecu(tv);
}


void TestNextLeaf(const ln::gumap& g) {
  vecvu sclique{ {}, { 1 } };
  vecvu nodes{ { 2, 3, 4, 5, 6, 7 }, { 2, 3, 4 } };
  vecvu xnodes{ { 1 }, {} };
  vecu  srdnodes{};

  NextLeaf_(sclique, nodes, xnodes, srdnodes, g);

  cout << "sclique is: \n";
  Printvecvu(sclique);
  cout << "nodes is: \n";
  Printvecvu(nodes);
  cout << "xnodes is: \n";
  Printvecvu(xnodes);
  cout << "end. \n" << endl;

  vecvu sclique2{ {}, { 1 } };
  vecvu nodes2{ { 2, 3, 4, 5, 6, 7 }, { 3, 4 } };
  vecvu xnodes2{ { 1 }, { 2 } };
  vecu  srdnodes2{ 2 };

  NextLeaf_(sclique2, nodes2, xnodes2, srdnodes2, g);

  cout << "sclique2 is: \n";
  Printvecvu(sclique2);
  cout << "nodes2 is: \n";
  Printvecvu(nodes2);
  cout << "xnodes2 is: \n";
  Printvecvu(xnodes2);
  cout << "end. \n" << endl;
}


// ln::vecvu TestSearchLeaf(const ln::gumap& g, const unsigned int node) {

//   vecvu sclique{ { node } };
//   vecvu nodes{ g.at(node) };
//   vecvu xnodes{ {} };
//   vecu  srdnodes{};

//   SearchLeaf_(sclique, nodes, xnodes, srdnodes, g);

//   cout << "sclique are: \n";
//   Printvecvu(sclique);
//   cout << "nodes are: \n";
//   Printvecvu(nodes);
//   cout << "xnodes is: \n";
//   Printvecvu(xnodes);
//   cout << "end. \n" << endl;

//   return nodes;
// }


// ln::vecvu TestSearchTree(const ln::gumap& g, const unsigned int node) {

//   vecvu cliques{ {} };
//   vecvu sclique{ {} };
//   vecvu nodes{ g.at(node) };
//   vecvu xnodes{ {} };
//   vecu  srdnodes{};

//   cout << "raw first nodes size is: " << nodes.front().size() << endl;

//   SearchTree_(cliques, sclique, nodes, xnodes, srdnodes, g);

//   return cliques;
// }


int main() {
  // //~~~~~~~~~~test DiffIntersect~~~~~~~~~~~~~~~~~~~
  // vecu fv = {1, 2, 3, 7, 4};
  // vecu tv = {9, 2, 10};

  // TestDiffIntersect(fv, tv);
  // //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  // //~~~~~~~~~~test read csv to umat~~~~~~~~~~~~~~~~
  // umat testm;
  // testm.load("../test/testm.bin", arma_binary);
  // testm.print("testm is: ");

  // umat testg;
  // testg.load("../test/testg.bin", arma_binary);
  // testg.brief_print("testg is: ");

  // umat testgbig;
  // testgbig.load("../test/testgbig.bin", arma_binary);
  // testgbig.brief_print("testgbig is: ");
  // //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  // //~~~~~~~~~~~~~~~~~test init gumap~~~~~~~~~~~~~~~~~~~
  // umat testm;
  // testm.load("../test/testm.bin", arma_binary);
  // auto gm = gumapInit(testm);
  // //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  // //~~~~~~~~~~~~~~~~~~~~test TestSortNodes~~~~~~~~~~~~~~~~~~
  // // vecu ln = {4, 8, 3, 10};
  // // vecu tn = {4, 20, 100, 34, 3, 28, 9};
  // // vecu degree(ln.size(), 0);

  // // Count_(degree, ln, tn);
  // // Printvecu(degree);
  // // Printvecu(SortIdx_(ln));

  // // umat testm;
  // // testm.load("../test/testm.bin", arma_binary);
  // // auto gm = gumapInit(testm);
  // // testm.print("gm is: ");

  // // Printvecu(gm.at(0));
  // // Printvecu(SortNodes_(gm.at(0), gm));
  // //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  // // ~~~~~~~~~~~~~~~~~test intersection and move~~~~~~~~~~~~~
  // vecu fv{ 1, 2, 3, 4, 5, 6, 7 };
  // vecu tv{ 1, 5 };
  // Printvecu(IntersectionIdc_(fv, tv));

  // // blog graph test
  // umat testblog = { { 1, 2 }, { 1, 3 }, { 1, 4 }, { 2, 3 }, { 2, 4 }, { 3, 4
  // },
  //                   { 2, 5 }, { 4, 5 }, { 5, 7 }, { 4, 6 }, { 0, 1 }, { 0, 2
  //                   }, { 0, 3 }, { 0, 4 }, { 0, 5 }, { 0, 6 }, { 0, 7 } };
  // auto gblog    = gumapInit(testblog);
  // testblog.brief_print("gblog is: ");

  // Printvecu(NextIdc_(fv, tv, gblog));
  // // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  //~~~~~~~~~~~~~~~~~test TestPushHead~~~~~~~~~~~~~~~~~~~
  // blog graph test
  umat testblog = { { 1, 2 }, { 1, 3 }, { 1, 4 }, { 2, 3 }, { 2, 4 }, { 3, 4 },
                    { 2, 5 }, { 4, 5 }, { 5, 7 }, { 4, 6 }, { 0, 1 }, { 0, 2 },
                    { 0, 3 }, { 0, 4 }, { 0, 5 }, { 0, 6 }, { 0, 7 } };
  auto gblog    = gumapInit(testblog);
  TestNextLeaf(gblog);
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  //~~~~~~~~~~~~~~~~~test SearchTree~~~~~~~~~~~~~~~~~~~
  // umat testm; // small graph
  // testm.load("../test/testm.bin", arma_binary);
  // auto gm = gumapInit(testm);
  // testm.print("gm is: ");

  // TestSearchLeaf(gm, 0);
  // auto treem = TestSearchTree(gm, 0);
  // Printvecvu(treem);

  // auto mcm = MaxCliques(gm, 0);
  // Printvecvu(mcm);

  // umat testg; // median graph
  // testg.load("/Users/yulong/RESEARCH/LonelyNodesCpp/test/testg.bin",
  //            arma_binary);
  // auto gg = gumapInit(testg);
  // testg.brief_print("gg is: ");

  // size_t nodeIdx = 366;
  // auto   ggtrim  = TrimGraph_(gg.at(nodeIdx), gg);

  // vecvu cliques;
  // vecvu sclique{ { 366 } };
  // vecvu nodes{ ggtrim.at(nodeIdx) };
  // vecvu xnodes{ {} };
  // vecu  srdnodes{};

  // SearchLeaf_(sclique, nodes, xnodes, srdnodes, ggtrim);
  // cliques.push_back(sclique.back());
  // TrimLeaf_(sclique, nodes, xnodes);
  // srdnodes = xnodes.back();

  // cout << "different nodes are: \n";
  // Printvecu(Difference(nodes.back(), cliques.back()));

  // cout << "Search space is: \n";
  // Printvecu(ggtrim.at(nodeIdx));
  // cout << "cliques are: \n";
  // Printvecvu(cliques);
  // cout << "srdnodes are: \n";
  // Printvecu(srdnodes);
  // cout << "next search nodes are: \n";
  // Printvecu(nodes.back());
  // cout << "end." << endl;

  // TestSearchLeaf(ggtrim, nodeIdx);
  // cout << "vertex number is: " << gg.size() << '\n' << endl;
  // auto treeg = TestSearchTree(gg, nodeIdx);
  // Printvecvu(treeg);

  // auto mcg = MaxCliques(gg, nodeIdx);
  // Printvecvu(mcg);

  // // large graph
  // umat testgbig;
  // testgbig.load("../tests/testgbig.bin", arma_binary);
  // auto gbig = gumapInit(testgbig);
  // testgbig.brief_print("gbig is: ");

  // unsigned int nodeIdx = 9117;
  // auto mcbig = MaxCliques(gbig, nodeIdx);
  // Printvecvu(mcbig);

  // blog graph test
  // umat testblog = {{1, 2}, {1, 3}, {2, 3}, {2, 4},
  //                  {0, 1}, {0, 2}, {0, 3}, {0, 4}};

  // umat testblog = { { 1, 2 }, { 1, 3 }, { 1, 4 }, { 2, 3 }, { 2, 4 }, { 3,
  // 4
  // },
  //                   { 2, 5 }, { 4, 5 }, { 5, 7 }, { 4, 6 }, { 0, 1 }, { 0,
  //                   2
  //                   }, { 0, 3 }, { 0, 4 }, { 0, 5 }, { 0, 6 }, { 0, 7 } };
  // Auto gblog    = gumapInit(testblog);
  // testblog.brief_print("gblog is: ");

  // // TestSearchLeaf(gblog, 0);

  // auto cliqueblog = TestSearchTree(gblog, 0);
  // Printvecvu(cliqueblog);
  // //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  // //~~~~~~~~~~~~~~~~~~~~~test Leaf obj~~~~~~~~~~~~~~~~~~~
  // Leaf firstLeaf{ { 1 }, { 2, 3 }, { 4 } };
  // firstLeaf.print();
  // Printvecu(firstLeaf.next_seeds());
  // //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  return 0;
}

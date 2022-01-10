#include <iostream>

#include "util.h"
#include "init.h"
#include "clique.h"

using namespace std;
using namespace lonelynodes;
using namespace arma;

void TestDiffIntersect(ln::vecu& fv,
                       ln::vecu& tv) {
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


void TestPushHead() {
  vecvu sclique = {{1, 2, 3},
                   {2, 3, 4}};

  vecvu nodes = {{5, 7},
                 {9}};

  PushHead_(sclique, nodes);

  Printvecvu(sclique);
  Printvecvu(nodes);

  vecvu sclique2 = {{}};
  vecvu nodes2 = {{1, 10},
                  {2, 10, 12}};

  PushHead_(sclique2, nodes2);

  cout << "sclique2 is: \n";
  Printvecvu(sclique2);
  cout << "nodes2 is : \n";
  Printvecvu(nodes2);

}


ln::vecvu TestSearchLeaf(const ln::gumap& g,
                         const unsigned int node) {

  vecvu sclique = {{node}};
  vecvu nodes = {g.at(node)};

  SearchLeaf_(sclique, nodes, g);

  cout << "sclique are: \n";
  Printvecvu(sclique);
  cout << "nodes are: \n";
  Printvecvu(nodes);

  return nodes;
}


ln::vecvu TestSearchTree(const ln::gumap& g,
                         const unsigned int node) {

  vecvu cliques{{}};
  vecvu sclique = {{node}};
  vecvu nodes = {g.at(node)};

  cout << "raw first nodes size is: " << nodes.front().size() << endl;

  SearchTree_(cliques, sclique, nodes, g);

  return cliques;
}



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

  // //~~~~~~~~~~~~~~~~~test TestPushHead~~~~~~~~~~~~~~~~~~~
  // TestPushHead();
  // //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  // //~~~~~~~~~~~~~~~~~~~~test TestSortNodes~~~~~~~~~~~~~~~~~~
  // vecu ln = {4, 8, 3, 10};
  // vecu tn = {4, 20, 100, 34, 3, 28, 9};
  // vecu degree(ln.size(), 0);

  // Count_(degree, ln, tn);
  // Printvecu(degree);
  // Printvecu(SortIdx_(ln));

  // umat testm;
  // testm.load("../tests/testm.bin", arma_binary);
  // auto gm = gumapInit(testm);
  // testm.print("gm is: ");

  // Printvecu(gm.at(0));
  // Printvecu(SortNodes_(gm.at(0), gm));

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  //~~~~~~~~~~~~~~~~~test SearchTree~~~~~~~~~~~~~~~~~~~
  // small graph
  umat testm;
  testm.load("../tests/testm.bin", arma_binary);
  auto gm = gumapInit(testm);
  testm.print("gm is: ");

  // TestSearchLeaf(gm, 0);
  // auto treem = TestSearchTree(gm, 0);
  // Printvecvu(treem);

  auto mcm = MaxCliques(gm, 0);
  Printvecvu(mcm);

  // median graph
  umat testg;
  testg.load("../tests/testg.bin", arma_binary);
  auto gg = gumapInit(testg);
  testg.brief_print("gg is: ");

  unsigned int nodeIdx = 366;
  // TestSearchLeaf(gg, nodeIdx);
  cout << "vertex number is: " << gg.size() << '\n' << endl;
  auto treeg = TestSearchTree(gg, nodeIdx);
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

  // umat testblog = {{1, 2}, {1, 3}, {1, 4},
  //                  {2, 3}, {2, 4}, {3, 4},
  //                  {2, 5}, {4, 5},
  //                  {5, 7}, {4, 6},
  //                  {0, 1}, {0, 2}, {0, 3}, {0, 4},
  //                  {0, 5}, {0, 6}, {0, 7}};
  // auto gblog = gumapInit(testblog);
  // testblog.brief_print("gblog is: ");

  // TestSearchLeaf(gblog, 0);
  // auto cliqueblog = TestSearchTree(gblog, 0);
  // Printvecvu(cliqueblog);
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  return 0;
}



#include <chrono>
#include <cstddef>
#include <ctime>
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


ln::vecvu TestSearchLeaf(const ln::gumap& g, const unsigned int node) {

  vecvu sclique{ { node } };
  vecvu nodes{ g.at(node) };
  vecvu xnodes{ {} };
  vecu  srdnodes{};

  SearchLeaf_(sclique, nodes, xnodes, srdnodes, g);

  cout << "sclique are: \n";
  Printvecvu(sclique);
  cout << "nodes are: \n";
  Printvecvu(nodes);
  cout << "xnodes is: \n";
  Printvecvu(xnodes);
  cout << "end. \n" << endl;

  return nodes;
}


ln::vecvu TestSearchTree(const ln::gumap&  g,
                         const arma::umat& gidc,
                         const arma::uword node) {

  vecvu cliques;
  vecvu sclique{ {} };
  vecvu nodes{ g.at(node) };
  vecvu xnodes{ {} };
  vecu  srdnodes{};

  cout << "raw first nodes size is: " << nodes.front().size() << endl;

  SearchTree_(cliques, sclique, nodes, xnodes, srdnodes, g, gidc);

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
  // umat testblog = { { 1, 2 }, { 1, 3 }, { 1, 4 }, { 2, 3 }, { 2, 4 }, { 3,
  // 4
  // },
  //                   { 2, 5 }, { 4, 5 }, { 5, 7 }, { 4, 6 }, { 0, 1 }, { 0,
  //                   2
  //                   }, { 0, 3 }, { 0, 4 }, { 0, 5 }, { 0, 6 }, { 0, 7 } };
  // auto gblog    = gumapInit(testblog);
  // testblog.brief_print("gblog is: ");

  // Printvecu(NextIdc_(fv, tv, gblog));
  // // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  // //~~~~~~~~~~~~~~~~~test TestNextLeaf~~~~~~~~~~~~~~~~~~~
  // // blog graph test
  // umat testblog = { { 1, 2 }, { 1, 3 }, { 1, 4 }, { 2, 3 }, { 2, 4 }, { 3,
  // 4
  // },
  //                   { 2, 5 }, { 4, 5 }, { 5, 7 }, { 4, 6 }, { 0, 1 }, { 0,
  //                   2
  //                   }, { 0, 3 }, { 0, 4 }, { 0, 5 }, { 0, 6 }, { 0, 7 } };

  // // umat testblog = { { 1, 2 }, { 1, 3 }, { 1, 4 }, { 2, 3 }, { 2, 4 },
  // //                   { 3, 4 }, { 2, 5 }, { 4, 5 }, { 5, 7 }, { 4, 6 } };
  // auto gblog = gumapInit(testblog);
  // TestNextLeaf(gblog);
  // TestSearchLeaf(gblog, 2);
  // Printvecvu(TestSearchTree(gblog, 0));
  // //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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

  umat testg; // median graph
  testg.load("/Users/yulong/RESEARCH/LonelyNodesCpp/test/testg.bin",
             arma_binary);
  testg.brief_print("gg is: ");


  auto gg   = gumapInit(testg);
  auto gidc = gidcInit(gg);
  gidc.brief_print("gidc is: ");

  auto  start      = chrono::system_clock::now();
  auto  start_time = chrono::system_clock::to_time_t(start);
  uword nodeIdx    = 332;
  auto  ggtrim     = TrimGraph_(gg.at(nodeIdx), gg);
  TestSearchTree(gg, gidc, nodeIdx);
  auto end      = chrono::system_clock::now();
  auto end_time = chrono::system_clock::to_time_t(end);

  std::chrono::duration<double> elapsed_seconds = end - start;
  cout << "start computation at " << std::ctime(&start_time)
       << "end computation at " << std::ctime(&end_time)
       << "elapsed time: " << elapsed_seconds.count() << "s\n";

  // umat testgbig; // large graph
  // testgbig.load("/Users/yulong/RESEARCH/LonelyNodesCpp/test/testgbig.bin",
  //               arma_binary);
  // auto gbig = gumapInit(testgbig);
  // testgbig.brief_print("gbig is: ");

  // auto   start      = chrono::system_clock::now();
  // auto   start_time = chrono::system_clock::to_time_t(start);
  // size_t nodeIdx    = 9116;
  // auto   gbigtrim   = TrimGraph_(gbig.at(nodeIdx), gbig);
  // TestSearchTree(gbigtrim, nodeIdx);

  // auto end      = chrono::system_clock::now();
  // auto end_time = chrono::system_clock::to_time_t(end);

  // std::chrono::duration<double> elapsed_seconds = end - start;
  // cout << "start computation at " << std::ctime(&start_time)
  //      << "end computation at " << std::ctime(&end_time)
  //      << "elapsed time: " << elapsed_seconds.count() << "s\n";

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

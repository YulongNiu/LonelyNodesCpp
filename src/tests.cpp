#include <bit>
#include <bitset>
#include <boost/assert.hpp>
#include <boost/dynamic_bitset.hpp>
#include <chrono>
#include <cstddef>
#include <ctime>
#include <iostream>
#include <type_traits>

#include "bclique.h"
#include "clique.h"
#include "init.h"
#include "pivot.h"
#include "util.h"

using namespace std;
using namespace ln;
using namespace arma;


// length of each clique
ln::vecu Lenvecvu(const ln::vecvu& v) {
  vecu res;

  for (uword i = 0; i < v.size(); ++i) {
    res.push_back(v.at(i).size());
  }

  return res;
}


// sort each clique
void Sortvecvu(ln::vecvu& v) {
  for (uword i = 0; i < v.size(); ++i) {
    sort(v.at(i).begin(), v.at(i).end());
  }
}


void TestNextLeaf(const arma::umat& gidc) {
  vecvu sclique{ {}, { 1 } };
  vecvu nodes{ { 2, 3, 4, 5, 6, 7 }, { 2, 3, 4 } };
  vecvu xnodes{ { 1 }, {} };
  vecu  srdnodes{};

  NextLeaf_(sclique, nodes, xnodes, srdnodes, gidc);

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

  NextLeaf_(sclique2, nodes2, xnodes2, srdnodes2, gidc);

  cout << "sclique2 is: \n";
  Printvecvu(sclique2);
  cout << "nodes2 is: \n";
  Printvecvu(nodes2);
  cout << "xnodes2 is: \n";
  Printvecvu(xnodes2);
  cout << "end. \n" << endl;
}


ln::vecvu TestSearchLeaf(const ln::gumap&  g,
                         const arma::umat& gidc,
                         const arma::uword node) {

  vecvu sclique{ { node } };
  vecvu nodes{ g.at(node) };
  vecvu xnodes{ {} };
  vecu  srdnodes{};

  SearchLeaf_(sclique, nodes, xnodes, srdnodes, gidc);

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

  SearchTree_(cliques, sclique, nodes, xnodes, srdnodes, gidc);

  return cliques;
}

int main() {

  // //~~~~~~~~~~~~~~~~~~test dynamic_bitset~~~~~~~~~~~~~~~~~~~
  // dbit db1(10, 28); // 101
  // cout << "db1 is: " << db1 << "; npos is: " << dbit::npos << endl;

  // dbit a{ string("0101100") };
  // dbit b{ string("1011101") };
  // cout << "a is: " << a << "; b is: " << b
  //      << "; complement a\b is: " << ComplementBit(a, b) << endl;

  dbit empdbitTest{ string{ "0000000" } };
  BOOST_ASSERT_MSG(empdbitTest.find_first() == dbit::npos,
                   "find_first() for no 1 in dbit is checked");

  // db1.push_back(1);
  // cout << db1 << endl;

  // dbit a{ string("11111110") };
  // cout << "~a is: " << ~a << endl;
  // //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  //~~~~~~~~~~~~~~~~load graph~~~~~~~~~~~~~~~~~~~~~~~
  string basepath = "/Users/yulong/RESEARCH/LonelyNodesCpp/test/";
  // string basepath = "/share/data2/niuyulong/LonelyNodesCpp/test/";

  // string gfile   = "testm.bin"; // small graph
  // uword  nodeIdx = 0;           // #maximal clique 4

  // string gfile   = "testg.bin"; // median graph
  // uword  nodeIdx = 332;         // #maximal clique 94
  // uword nodeIdx = 10; // #maximal clique 5

  // string gfile   = "testgbig.bin"; // large graph
  // uword  nodeIdx = 9116;           // #maximal clique 3764
  // uword nodeIdx = 100; // #maximal clique 264

  string gfile   = "testblog.bin"; // blog graph
  uword  nodeIdx = 0;              // #maximal clique 4

  // string gfile   = "c-fat200-5.bin"; // c-fat200-5 graph
  // uword  nodeIdx = 99;

  // string gfile   = "p-hat500-2.bin"; // c-fat200-5 graph
  // uword  nodeIdx = 10;

  umat testg;
  testg.load(basepath + gfile, arma_binary);
  testg.brief_print("gg is: ");

  auto gg    = gumapInit(testg);
  auto gidc  = gidcInit(gg);
  auto gdbit = gdbitInit(gg);
  gidc.brief_print("gidc is: ");

  // gidc.print("gidc is: ");'
  // Printvecdbit(gdbit);

  // all vertices
  auto gdbitall = gdbitAll(gdbit);
  // cout << "#total nodes: " << gdbitall << endl;
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  // //~~~~~~~~~~~~~~~~~test Leaf obj~~~~~~~~~~~~~~~~~~~~~~~
  // Leaf testLeaf{ { 1 }, { 2, 3 }, { 4, 6, 9 } };
  // testLeaf.print();

  // Leaf startn({}, {}, { gg.at(nodeIdx) });
  // auto idx     = startn.next_nodeidx(gidc);
  // auto nextn   = startn.next_leaf(idx, gidc);
  // auto updaten = startn.update_leaf(idx);
  // startn.print();
  // nextn.print();
  // updaten.print();

  dbit    dbitemptyTest(gdbit.size(), 0);
  LeafBit startnTest({}, dbitemptyTest, gdbit.at(nodeIdx));
  BOOST_ASSERT_MSG(startnTest.next_nodeidx(gdbit) ==
                     gdbit.at(nodeIdx).find_first(),
                   "idx for `seeds.empty()` is checked.");
  // //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  // //~~~~~~~~~~~~~~~~~~~test pivot~~~~~~~~~~~~~~~~~~~~~
  // vecu eachNodes  = { 57,  58,  59,  61,  62,  64,  66,  69,  71,  73,  74,
  // 75,
  //                    76,  79,  81,  83,  87,  88,  91,  92,  95,  96,  97,
  //                    101, 102, 104, 105, 106, 107, 114, 115, 116, 117, 120,
  //                    122, 125, 126, 128, 130, 131, 132, 135, 136, 137, 142,
  //                    149, 151, 154, 155, 157, 162, 163, 167, 174, 175, 177,
  //                    185, 195, 197, 199, 203, 204, 206, 207, 209, 211, 213,
  //                    215, 218, 221, 225, 226, 228, 230, 234, 235, 237, 238,
  //                    260, 261, 263, 264, 266, 267, 271, 273, 274, 275, 277,
  //                    278, 289, 292, 293, 294, 297, 299, 304, 308, 310, 311,
  //                    313, 314, 316, 318, 319, 320, 321, 324, 326, 332, 333,
  //                    334, 335, 336, 337, 340, 343, 344, 345, 346, 347, 349,
  //                    350, 352, 353, 355, 356, 359, 363, 365, 366, 369, 370,
  //                    374, 376, 378, 379, 380, 385, 406 };
  // vecu eachNodes2 = {
  //   12,  13,  15,  19,  20,  22,  24,  25,  28,  30,  31,  34,  37,  40,
  //   42, 43,  44,  45,  46,  47,  51,  55,  57,  58,  59,  61,  62,  64, 66,
  //   69, 71,  73,  74,  75,  76,  79,  81,  83,  87,  88,  91,  92,  95, 96,
  //   97, 101, 102, 104, 105, 106, 107, 114, 115, 116, 117, 120, 122, 125,
  //   126, 128, 130, 131, 132, 135, 136, 137, 142, 149, 151, 154, 155, 157,
  //   162, 163, 167, 174, 175, 177, 185, 195, 197, 199, 203, 204, 206, 207,
  //   209, 211, 213, 215, 218, 221, 225, 226, 228, 230, 234, 235, 237, 238,
  //   260, 261, 263, 264, 266, 267, 271, 273, 274, 275, 277, 278, 289, 292,
  //   293, 294, 297, 299, 304, 308, 310, 311, 313, 314, 316, 318, 319, 320,
  //   321, 324, 326, 332, 333, 334, 335, 336, 337, 340, 343, 344, 345, 346,
  //   347, 349, 350, 352, 353, 355, 356, 359, 363, 365, 366, 369, 370, 374,
  //   376, 378, 379, 380, 385, 406
  // };
  // vecu eachXnodes = { 14, 56 };

  // umat splitIdc = gidc.submat(STD2ARMAuv(eachNodes2),
  // STD2ARMAuv(eachXnodes)); splitIdc.print("split idc is: "); cout << "next
  // node idx is: " << NextNodeIdx_(eachNodes, eachXnodes, gidc)
  //      << endl;
  // //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  // //~~~~~~~~~~test DiffIntersect~~~~~~~~~~~~~~~~~~~
  // vecu fv = {1, 2, 3, 7, 4};
  // vecu tv = {9, 2, 10};

  // TestDiffIntersect(fv, tv);

  // umat para3 = { { 0, 1, 1 }, { 1, 0, 1 }, { 1, 1, 0 } };
  // para3.print("para3 is: ");

  // vecu para1 = { 0, 2 };
  // // vecu para1 = {};
  // // vecu para2 = { 1 };
  // vecu para2 = {};
  // auto nidx  = NextNodeIdx_(para1, para2, para3);
  // cout << "nidx is: " << nidx << "\n";

  // //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  // //~~~~~~~~~~test read csv to umat~~~~~~~~~~~~~~~~
  // umat testblog;
  // testblog.load(basepath + "p-hat500-2.csv", csv_ascii);
  // testblog.brief_print("p-hat500-2 is: ");
  // testblog.save(basepath + "p-hat500-2.bin", arma_binary);
  // //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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

  // //~~~~~~~~~~~~~~~~~test TestSearchTree~~~~~~~~~~~~~~~~~
  // // TestSearchLeaf(gg, gidc, nodeIdx);
  // // TestbSearchLeaf(gbit, nodeIdx);
  // vecvu cliques{ { 1, 2, 3, 4 }, { 5, 4, 2 }, { 5, 7 }, { 6, 4 } };
  // vecvu sclique{ {} };
  // vecvu nodes{ { 7, 2, 3, 4 } };
  // vecvu xnodes{ { 1, 5, 6 } };
  // vecu  srdnodes{ 1, 5, 6 };

  // // SearchLeaf_(sclique, nodes, xnodes, srdnodes, gidc);
  // // NextLeaf_(sclique, nodes, xnodes, srdnodes, gidc);
  // cout << "next node is: "
  //      << NextNodeIdx_(sclique.back(), nodes.back(), xnodes.back(), gidc)
  //      << endl;
  // BackTrimLeaf_(sclique, nodes, xnodes, gidc);
  // PrintTreeInfo_(cliques, sclique, nodes, xnodes, srdnodes, "test");

  // dbit crown{ string("00110000") };
  // vecu seed{ 1, 2, 7 };
  // cout << "First0dbit_ is: " << First0dbit_(crown, seed, gdbit) << "\n";
  // //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  //~~~~~~~~~~~~~~~~~~~~~~~test find_first and find_next~~~~~~~~
  uword       num = 123456;
  bitset<100> testFindf{ num };
  cout << "`testFindf` is: " << testFindf << endl;

  cout << "find first of `testFindf` is: " << countr_zero(num) << endl;
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  //~~~~~~~~~~~~~~~~~test SearchTree~~~~~~~~~~~~~~~~~~~
  auto start      = chrono::system_clock::now();
  auto start_time = chrono::system_clock::to_time_t(start);

  dbit dbitempty(gdbit.size(), 0);
  // LeafBit startn({}, dbitempty, gdbitall);
  LeafBit startn({}, dbitempty, gdbit.at(nodeIdx));
  auto    cliques = SearchLeafBit(startn, gdbit);

  // Leaf object method
  // Leaf startn({}, {}, { gg.at(nodeIdx) });
  // auto cliques = SearchLeafObj(startn, gidc);

  // raw vector method
  // auto cliques = TestSearchTree(gg, gidc, nodeIdx);

  for (uword i = 0; i < 10000; ++i) {}

  auto end      = chrono::system_clock::now();
  auto end_time = chrono::system_clock::to_time_t(end);

  chrono::duration<double> elapsed_seconds = end - start;
  cout << "start computation: " << ctime(&start_time)
       << "end computation: " << ctime(&end_time)
       << "elapsed time: " << elapsed_seconds.count() << "s\n";

  // Printvecdbit(cliques);

  // cout << "\n"
  //      << "cliques are: \n";
  // Sortvecvu(cliques);
  // Printvecvu(cliques);

  // cout << "\n"
  //      << "cliques size are: \n";
  // Printvecu(Lenvecvu(cliques));
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  // //~~~~~~~~~~~~~~~~~~~~~test Leaf obj~~~~~~~~~~~~~~~~~~~
  // Leaf firstLeaf{ { 1 }, { 2, 3 }, { 4 } };
  // firstLeaf.print();
  // Printvecu(firstLeaf.next_seeds());
  // //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  return 0;
}

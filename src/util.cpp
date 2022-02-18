#include "util.h"

using namespace arma;
using namespace std;
using namespace lonelynodes;

//~~~~~~~~~~~~~~~~~~~indicator version~~~~~~~~~~~~~~~~~~~~~~~~~
// convert `ln::vecu` to `arma::uvec`
arma::uvec STD2ARMAuv(const ln::vecu& v) {
  uvec res(v.data(), v.size());
  return res;
}


ln::vecu IntersectNodes_(const ln::vecu&   nodes,
                         const arma::uword idx,
                         const arma::umat& gidc) {

  uvec idc = gidc.col(idx);

  return SelectInterset_(nodes, idc);
}


// seems faster, but ugly.
// ln::vecu IntersectNodes_(const ln::vecu&   nodes,
//                          const arma::uword idx,
//                          const arma::umat& gidc) {

//   auto nodesv = STD2ARMAuv(nodes);

//   uvec idc     = gidc.col(idx);
//   uvec nodeidc = idc.elem(nodesv);

//   uvec resv = nodesv.elem(find(nodeidc));

//   return conv_to<vecu>::from(resv);
// }


ln::vecu SelectInterset_(const ln::vecu& nodes, const arma::uvec& idc) {

  vecu res;

  for (uword i = 0; i != nodes.size(); ++i) {
    auto eachNode = nodes.at(i);
    if (idc.at(eachNode) == 1) { res.push_back(eachNode); }
  }

  return res;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


void Printvecu(const ln::vecu& v) {
  for_each(v.begin(), v.end(), [](auto elem) { cout << elem << ','; });

  cout << endl;
}


void Printvecvu(const ln::vecvu& v) {
  for (const auto& elem : v) {
    Printvecu(elem);
  }
}


void Printvecdbit(const ln::vecdbit& v) {
  for (const auto& elem : v) {
    Printvecu(DBIT2VECU_(elem));
  }
}

vecu DBIT2VECU_(const ln::dbit& v) {
  vecu res;
  for (auto i = v.find_first(); i != dbit::npos; i = v.find_next(i)) {
    res.push_back(i);
  }

  return res;
}

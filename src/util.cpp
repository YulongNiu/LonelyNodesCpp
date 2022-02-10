#include <algorithm> //std::sort std::set_intersection std::set_difference std::find
#include <armadillo>
#include <iostream> //std::cout std::endl
#include <iterator> //std::back_inserter
#include <vector>   //std::vector

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


ln::vecu Intersection(const ln::vecu& fv, const ln::vecu& tv) {
  vecu res;
  vecu f = fv;
  vecu t = tv;

  // sort
  sort(f.begin(), f.end());
  sort(t.begin(), t.end());

  set_intersection(f.begin(), f.end(), t.begin(), t.end(), back_inserter(res));
  return res;
}


ln::vecu Difference(const ln::vecu& fv, const ln::vecu& tv) {

  vecu res;
  vecu f = fv;
  vecu t = tv;

  // sort
  sort(f.begin(), f.end());
  sort(t.begin(), t.end());

  set_difference(f.begin(), f.end(), t.begin(), t.end(), back_inserter(res));
  return res;
}


// new `fv` is set_difference(fv, tv)
// new `tv` is set_intersection(fv, tv)
void DiffIntersect(ln::vecu& fv, ln::vecu& tv) {
  vecu diff;
  vecu intersect;

  for (auto pfv = fv.begin(); pfv != fv.end(); ++pfv) {
    auto ptv = tv.begin();

    for (; ptv != tv.end(); ++ptv) {
      if (*pfv == *ptv) {
        // add intersection
        intersect.push_back(*pfv);
        break;
      } else {
      }
    }

    if (ptv == tv.end()) {
      // add difference
      diff.push_back(*pfv);
    } else {
    }
  }

  fv = diff;
  tv = intersect;
}

void Printvecu(const ln::vecu& v) {
  for_each(v.begin(), v.end(), [](auto elem) { cout << elem << ','; });

  cout << endl;
}


void Printvecvu(const ln::vecvu& v) {
  for (auto eachv : v) {
    Printvecu(eachv);
  }
}


void Printvecdbit(const ln::vecdbit& g) {
  for (auto elem : g) {
    cout << elem << endl;
  }
}


ln::citerv FirstDiff(ln::citerv ffirst,
                     ln::citerv flast,
                     ln::citerv tfirst,
                     ln::citerv tlast) {

  while (ffirst != flast) {
    auto p = find(tfirst, tlast, *ffirst);

    if (p == tlast) { return ffirst; }

    ++ffirst;
  }

  return ffirst;
}

#include <vector> //std::vector
#include <algorithm> //std::sort std::set_intersection std::set_difference std::find
#include <iterator> //std::back_inserter
#include <iostream> //std::cout std::endl

#include "util.h"

using namespace std;
using namespace lonelynodes;

ln::vecu Intersection(const ln::vecu& fv,
                      const ln::vecu& tv) {
  vecu res;
  vecu f = fv;
  vecu t = tv;

  // sort
  sort(f.begin(), f.end());
  sort(t.begin(), t.end());

  set_intersection(f.begin(), f.end(),
                   t.begin(), t.end(),
                   back_inserter(res));
  return res;
}


ln::vecu Difference(const ln::vecu& fv,
                    const ln::vecu& tv) {

  vecu res;
  vecu f = fv;
  vecu t = tv;

  // sort
  sort(f.begin(), f.end());
  sort(t.begin(), t.end());

  set_difference(f.begin(), f.end(),
                 t.begin(), t.end(),
                 back_inserter(res));
  return res;
}



// new `fv` is set_difference(fv, tv)
// new `tv` is set_intersection(fv, tv)
void DiffIntersect(ln::vecu& fv,
                   ln::vecu& tv) {
  vecu diff;
  vecu intersect;

  for (auto pfv = fv.begin(); pfv != fv.end(); ++pfv) {
    auto ptv = tv.begin();

    for (; ptv != tv.end(); ++ptv) {
      if (*pfv == *ptv) {
        // add intersection
        intersect.push_back(*pfv);
        break;
      } else {}
    }

    if (ptv == tv.end()) {
      // add difference
      diff.push_back(*pfv);
    } else {}

  }

  fv = diff;
  tv = intersect;
}


// example:
// MoveHead_(c(5, 7, 8, 9), 5)
// MoveHead_(c(5, 7, 8, 9), 7)
// MoveHead_(c(5), 7)
ln::vecu MoveHead_(const ln::vecu& v,
               const unsigned int start) {

  vecu res = v;

  // not deal v with only 1 element.
  if (v.size() == 1) {
    return res;
  } else {}

  res.front() = start;

  for (unsigned int i = 1; i < res.size(); ++i) {
    if (res.at(i) == start) {
      res.at(i) = v.front();
      break;
    }  else {}
  }

  return res;
}


void Printvecu(const ln::vecu& test) {
  for_each(test.begin(),
           test.end(),
           [](auto elem) {
             std::cout << elem << ',';
           });

  cout << endl;
}



void Printvecvu(const ln::vecvu& test) {
  for (auto eachv : test) {
    Printvecu(eachv);
  }
}


ln::citerv FirstDiff(ln::citerv ffirst, ln::citerv flast,
                     ln::citerv tfirst, ln::citerv tlast) {

  while(ffirst != flast) {
    auto p = find(tfirst, tlast, *ffirst);

    if (p == tlast) {
      return ffirst;
    } else {}

    ++ffirst;
  }

  return ffirst;
}



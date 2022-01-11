#ifndef _UTIL_H_
#define _UTIL_H_

#include <vector>
#include <iterator>

namespace lonelynodes {

  using vecu = std::vector<unsigned int>;
  using vecvu = std::vector<vecu>;

  using iterv = vecu::iterator;
  using citerv = vecu::const_iterator;
  using itervv = vecvu::iterator;
  using citervv = vecvu::const_iterator;

} // namespace lonelynodes

namespace ln = lonelynodes;

ln::vecu Intersection(const ln::vecu& fv,
                      const ln::vecu& tv);

ln::vecu Difference(const ln::vecu& fv,
                    const ln::vecu& tv);

void DiffIntersect(ln::vecu& fv,
                   ln::vecu& tv);

ln::vecu MoveHead_(const ln::vecu& v,
                   const unsigned int start);

void Printvecu(const ln::vecu& test);

void Printvecvu(const ln::vecvu& test);

ln::citerv FirstDiff(ln::citerv ffirst, ln::citerv flast,
                     ln::citerv tfirst, ln::citerv tlast);

#endif // _UTIL_H_

#ifndef _UTIL_H_
#define _UTIL_H_

#include <armadillo>
#include <boost/dynamic_bitset.hpp>
#include <iterator>
#include <vector>

namespace lonelynodes {

using vecu  = std::vector<arma::uword>;
using vecvu = std::vector<vecu>;

using iterv   = vecu::iterator;
using citerv  = vecu::const_iterator;
using itervv  = vecvu::iterator;
using citervv = vecvu::const_iterator;

using dbit    = boost::dynamic_bitset<>;
using vecdbit = std::vector<dbit>;
} // namespace lonelynodes

namespace ln = lonelynodes;

arma::uvec STD2ARMAuv(const ln::vecu& v);

ln::vecu IntersectNodes_(const ln::vecu&   nodes,
                         const arma::uword idx,
                         const arma::umat& gidc);

ln::vecu SelectInterset_(const ln::vecu& nodes, const arma::uvec& idc);

void Printvecu(const ln::vecu& test);

void Printvecvu(const ln::vecvu& test);

void Printvecdbit(const ln::vecdbit& g);

#endif // _UTIL_H_

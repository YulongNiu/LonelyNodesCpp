#ifndef _CLIQUE_H_
#define _CLIQUE_H_

#include "init.h"
#include "util.h"

namespace lonelynodes {

class Leaf {
public:
  Leaf() : seeds{}, stem{}, branches{} {}
  Leaf(const vecu& seeds, const vecu& stem, const vecu& branches)
      : seeds{ seeds }, stem{ stem }, branches{ branches } {}

  vecu        get_seeds() const { return seeds; };
  vecu        get_stem() const { return stem; };
  vecu        get_branches() const { return branches; };
  vecu        get_crown() const; // concatenate `stem` and `branches`.
  arma::uword get_node(const arma::uword idx) const {
    return branches.at(idx);
  };

  bool branches_empty() const { return branches.empty(); }

  arma::uword stem_size() const { return stem.size(); }
  arma::uword branches_size() const { return branches.size(); }
  arma::uword crown_size() const { return stem.size() + branches.size(); }

  // find next search node index
  arma::uword next_nodeidx(const arma::umat& gidc) const;

  bool is_skippable(const arma::uword idx) const {
    return idx == branches.size();
  };

  // next elem
  vecu next_branches(const arma::uword idx, const arma::umat& gidc) const;
  vecu next_stem(const arma::uword idx) const;
  vecu next_seeds() const;
  Leaf next_leaf(const arma::uword idx, const arma::umat& gidc) const;

  // update current elem
  vecu update_branches(arma::uword idx) const;
  vecu update_stem() const;
  vecu update_seeds(const arma::uword idx) const;
  Leaf update_leaf(const arma::uword idx) const;

  void print() const;

private:
  // `seeds`: searched nodes, each of which has been completely searched
  // for maximal cliques.
  // `branches`: nodes for next search.
  // `stem`: known cliques nodes in current leaf.
  // No intersections among `seeds`, `branches`, or `steam`.
  const vecu seeds, stem, branches;
};

inline vecu Leaf::get_crown() const {
  vecu crown = stem;
  crown.insert(crown.end(), branches.begin(), branches.end());
  return crown;
}

inline vecu Leaf::next_branches(const arma::uword idx,
                                const arma::umat& gidc) const {
  return IntersectNodes_(branches, this->get_node(idx), gidc);
}

inline vecu Leaf::next_stem(arma::uword idx) const {
  vecu res = stem;
  res.push_back(this->get_node(idx));
  return res;
}

inline vecu Leaf::next_seeds() const {
  return seeds;
}

inline vecu Leaf::update_branches(arma::uword idx) const {
  vecu res = branches;
  res.erase(res.begin() + idx);
  return res;
}

inline vecu Leaf::update_stem() const {
  return stem;
}

inline vecu Leaf::update_seeds(const arma::uword idx) const {
  vecu res = seeds;
  res.push_back(this->get_node(idx));
  return res;
}


inline Leaf Leaf::next_leaf(const arma::uword idx,
                            const arma::umat& gidc) const {
  return Leaf(this->next_seeds(),
              this->next_stem(idx),
              this->next_branches(idx, gidc));
}


inline Leaf Leaf::update_leaf(const arma::uword idx) const {
  return Leaf(this->update_seeds(idx),
              this->update_stem(),
              this->update_branches(idx));
}


// print `Leaf` obj
inline void Leaf::print() const {

  std::cout << "\n";

  std::cout << "seeds are: ";
  Printvecu(seeds);

  std::cout << "stem is: ";
  Printvecu(stem);

  std::cout << "branches is: ";
  Printvecu(branches);
}

using vecleaf = std::list<ln::Leaf>;

vecvu SearchLeafObj(const Leaf& start, const arma::umat& gidc);

void BackSkipLeafObj(vecleaf& vleaf);
} // namespace lonelynodes

void SearchTree_(ln::vecvu&        cliques,
                 ln::vecvu&        sclique,
                 ln::vecvu&        nodes,
                 ln::vecvu&        xnodes,
                 ln::vecu&         srdnodes,
                 const arma::umat& gidc);

// void CompareClique_(ln::vecvu &cliques, ln::vecvu &sclique);

bool isMaximalClique_(const ln::vecu&   clique,
                      const ln::vecu&   srdnodes,
                      const arma::umat& gidc);

void PrintTreeInfo_(const ln::vecvu&  cliques,
                    const ln::vecvu&  sclique,
                    const ln::vecvu&  nodes,
                    const ln::vecvu&  xnodes,
                    const ln::vecu&   srdnodes,
                    const std::string pos);

void TrimLeaf_(ln::vecvu&        sclique,
               ln::vecvu&        nodes,
               ln::vecvu&        xnodes,
               const arma::umat& gidc);

void BackTrimLeaf_(ln::vecvu&        sclique,
                   ln::vecvu&        nodes,
                   ln::vecvu&        xnodes,
                   const arma::umat& gidc);

void BackSkipLeaf_(ln::vecvu& sclique, ln::vecvu& nodes, ln::vecvu& xnodes);

bool isSkippable_(const ln::vecu&   eachSclique,
                  const ln::vecu&   eachNodes,
                  const arma::uword bestSize);

void SearchLeaf_(ln::vecvu&        sclique,
                 ln::vecvu&        nodes,
                 ln::vecvu&        xnodes,
                 ln::vecu&         srdnodes,
                 const arma::umat& gidc);

void NextLeaf_(ln::vecvu&        sclique,
               ln::vecvu&        nodes,
               ln::vecvu&        xnodes,
               const ln::vecu&   srdnodes,
               const arma::umat& gidc);

#endif // _CLIQUE_H_

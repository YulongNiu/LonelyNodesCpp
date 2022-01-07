#include <vector>
#include <unordered_map>
#include <armadillo>

#include "init.h"

using namespace arma;
using namespace std;
using namespace lonelynodes;


//' Initiate graph as node-linked_nodes
//'
//' \itemize{
//'   \item \code{gumapInit()}: "node-linked nodes" initiation as a "key-value" by \code{std::unordered_map}. "key" is node, and "value" is a \code{arma::uvec} storing linked nodes.
//'   \item \code{gFillEach_()}: fill each linked nodes.
//'   \item \code{gNodeCount_()}: number of linked nodes (edges) for each nodes. The index of number is in the same with node index.
//' }
//'
//' @title Initiate node-linked_nodes
//' @param tidx A \code{unsigned int} is the index of "to" node.
//' @param fillNodes A \code{std::vector<arma::uword>} is the vector to store linked nodes.
//' @return
//' \itemize{
//'   \item \code{gumapInit()}: A \code{gumap}.
//'   \item \code{gFillEach_()}: \code{void}.
//'   \item \code{gNodeCount_()}: A \code{std::vector<arma::uword>}.
//' }
//' @author Yulong Niu \email{yulong.niu@@hotmail.com}
//' @rdname initg
//' @keywords internal
// [[Rcpp::export]]
void gFillEach_(const unsigned int tidx,
                ln::vecu& fillNodes) {
  fillNodes.emplace_back(tidx);
}


//' @param m A \code{arma::umat} contains two columns. 1st column is index of "from" vertex. 2nd column is the index of "to" vertex.
// @rdname initg
// @keywords internal
ln::gumap gumapInit(const arma::umat& m) {
  gumap glink;

  // get edges number
  auto edgeNum = gNodeCount_(m);

  for (uword i = 0; i < edgeNum.size(); ++i) {
    if (edgeNum[i] > 0) {
      vecu eachNode;
      eachNode.reserve(edgeNum[i]);
      glink[i] = eachNode;
    } else {}
  }

  // fill
  for (uword i = 0; i < m.n_rows; ++i) {
    auto eachf = m(i, 0);
    auto eacht = m(i, 1);

    gFillEach_(eacht, glink.at(eachf));
    gFillEach_(eachf, glink.at(eacht));
  }

  return glink;
}


//' @param m A \code{arma::umat} contains two columns. 1st column is index of "from" vertex. 2nd column is the index of "to" vertex.
//' @rdname initg
//' @keywords internal
// [[Rcpp::export]]
ln::vecu gNodeCount_(const arma::umat& m) {

  uvec mv = vectorise(m);

  // init count vector
  vecu countv(max(mv) + 1, 0);

  for (auto elem : mv) {
    ++countv[elem];
  }

  return countv;
}

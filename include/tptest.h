#ifndef _TPTEST_H_
#define _TPTEST_H_

#include <iostream>

#include "BS_thread_pool.hpp"

namespace chainreact {

BS::synced_stream sync_out;
BS::thread_pool   pool;

class chain {
public:
  chain(const int quick, const int slow) : quick{ quick }, slow{ slow } {}

  ~chain() { std::cout << "chain destroy.\n"; }

  int get_quick() const { return quick; }
  int get_slow() const { return slow; }

  chain next() const {
    chain elem{ quick / 2, slow };
    return elem;
  }

  chain update() const {
    chain elem{ (quick + slow) / 2, slow > 0 ? slow - 1 : 0 };
    return elem;
  }

  void react() const;

  void print() const {
    std::cout << "quick is: " << quick << "; slow is: " << slow << std::endl;
  }

private:
  const int quick, slow;
};


void chain::react() const {
  if (get_quick() == 0) {
    std::cout << "End reaction." << std::endl;
  } else {
    chain nchain = next();
    pool.push_task(&chain::react, nchain);

    chain uchain = update();
    pool.push_task(&chain::react, uchain);
  }
}

void ChainReact(const chain& start) {
  if (start.get_quick() == 0) {
    std::cout << "End reaction." << std::endl;
  } else {
    ChainReact(start.next());
    ChainReact(start.update());
  }
}


void ChainReactParallel(const chain& start) {
  if (start.get_quick() == 0) {
    std::cout << "End reaction." << std::endl;
  } else {
    pool.push_task(ChainReactParallel, start.next());
    pool.push_task(ChainReactParallel, start.update());
  }
}

} // namespace chainreact

namespace cr = chainreact;

#endif // _TPTEST_H_

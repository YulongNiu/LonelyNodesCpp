#include <algorithm> //std::stable_sort std::sort std::includes
#include <iostream>
#include <unordered_map>

#include "clique.h"
#include "init.h"
#include "util.h"

using namespace std;

namespace lonelynodes {
// init `Leaf` obj
Leaf::Leaf() : seeds{ {} }, branches{ {} }, stem{ {} } {}

Leaf::Leaf(vecu seeds, vecu branches, vecu stem)
    : seeds{ seeds }, branches{ branches }, stem{ stem } {}

} // namespace lonelynodes

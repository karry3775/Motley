#include "EnvironmentGeneration.h"

namespace pathfinding {

Environment::Environment() {
    // TODO
}

Environment::Environment(uint32_t size) : size_{size} {
    // Initiate the adjacency list to be of
    // size
    adj_.reserve(size_);
}

void Environment::addEdge(uint32_t v, uint32_t w) {
    adj_[v].push_back(w);
    adj_[w].push_back(v);
}

const uint32_t Environment::getSize() const { return size_; }

}  // namespace pathfinding

#pragma once
/**
 * Template class for all environments
 */
#include "DefaultTypes.h"

namespace pathfinding {

template <typename T>
class Environment {
   public:
    Environment(){};

    Environment(uint32_t size) : size_{size} {};

    // function to add edge to the Environment
    void addEdge(T* v, T* w) {
        adj_[v].push_back(w);
        adj_[w].push_back(v); // temp : Experimental
    }

    const uint32_t getSize() const { return size_; };

    AdjacencyList<T*> getAdjacencyList() const { return adj_; };

   private:
    AdjacencyList<T*> adj_;
    uint32_t size_;
};

}  // namespace pathfinding

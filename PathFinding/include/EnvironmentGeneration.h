#pragma once
/**
 * Design of this interface:
 * 1. This module should be responsible for returning
 *    an environment (the possible options could be a grid world, maze,
 *    grid world with obstacles, to name a few) and that environment object
 *    should be have a visualize function of its own to see what we are dealing
 *    with
 * 2. That environment should be in the format of an adjacency lists based graph
 *    data structure, so that it can be later be used as a test bed for various
 *    other path finding algorithms
 */
#include "DefaultTypes.h"

namespace pathfinding {

class Environment{
   public:
    Environment();

    Environment(uint32_t size);

    // function to add edge to the Environment
    void addEdge(uint32_t v, uint32_t w);

    const uint32_t getSize() const;    

   private:
    
    AdjacencyList adj_;
    uint32_t size_;


};

class Grid : public Environment {
    // TODO
};

}  // namespace pathfinding

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

    virtual ~Environment() {}

    // function to add edge to the Environment
    virtual void addEdge(T* v, T* w) {
        adj_[v].push_back(w);
        adj_[w].push_back(v);  // temp : Experimental
    }

    virtual const uint32_t getSize() const { return size_; }

    virtual AdjacencyList<T*> getAdjacencyList() const { return adj_; }

    virtual std::vector<std::vector<int>> getObstacles() const {}

    virtual void printAdjacencyList() const {
        LOG(INFO) << "The adjacency list is:";
        for (auto itr = adj_.begin(); itr != adj_.end(); ++itr) {
            LOG(INFO) << *(itr->first) << " --> ";
            for (auto x : itr->second) {
                LOG(INFO) << *x << " ";
            }
        }
    }

    /**
     * Get environment cell pointer from cell value
     * @param Cell cell object
     * @return Cell pointer from the environment
     */
    virtual Cell* at(const Cell&) = 0;

    /**
     * Get environment cell pointer from row and col
     * @param row row in the environment
     * @param col col in the environment
     * @return Cell pointer from the environment
     */
    virtual Cell* at(const uint32_t& row, const uint32_t& col) = 0;

    /**
     * Getter for number of rows in the environment
     * @return number of rows in the environment
     */
    virtual const uint32_t getRows() const = 0;

    /**
     * Getter for number of cols in the environment
     * @return number of cols in the environment
     */
    virtual const uint32_t getCols() const = 0;

    /**
     * Getter for cell size in pixels in the environment
     * @return Cell size in pixels
     */
    virtual const uint32_t getCellSize() const = 0;

    /**
     * Getter for walls in the environment
     * @return vector of Wall pointer
     */
    virtual const std::vector<Wall*> getWalls() const {}

    /**
     * Helper function to populate obstacles in the environment
     * @param row row for the obstacle
     * @param col col for the obstacle
     */
    virtual void pushObstacles(const uint32_t& row, const uint32_t& col) {}

   private:
    AdjacencyList<T*> adj_;
    uint32_t size_;
};

}  // namespace pathfinding

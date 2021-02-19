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
    virtual void addEdge(T* v, T* w) {
        adj_[v].push_back(w);
        adj_[w].push_back(v);  // temp : Experimental
    }

    virtual const uint32_t getSize() const { return size_; };

    virtual AdjacencyList<T*> getAdjacencyList() const { return adj_; };

    virtual void printAdjacencyList() const {
        LOG(INFO) << "The adjancency list is:";
        for (auto itr = adj_.begin(); itr != adj_.end(); ++itr) {
            LOG(INFO) << *(itr->first) << " --> ";
            for (auto x : itr->second) {
                LOG(INFO) << *x << " ";
            }
        }
    }

    /** Pure virtual functions **/
    // TODO: Add better description for this interface class

    virtual Cell* at(const Cell&) = 0;

    virtual Cell* at(const uint32_t& row, const uint32_t& col) = 0;

    virtual const uint32_t getRows() const = 0;

    virtual const uint32_t getCols() const = 0;

    virtual const uint32_t getCellSize() const = 0;

    virtual const std::vector<Wall*> getWalls() const {}

   private:
    AdjacencyList<T*> adj_;
    uint32_t size_;
};

}  // namespace pathfinding

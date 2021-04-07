#pragma once

#include <Ant.h>
#include <Defaults.h>
#include <Utils.h>

namespace ant_colony {

typedef std::vector<Ant*> Ants;

class AntColonySim {
   public:
    AntColonySim(const uint32_t num_ants);
    void show();

   private:
    // Helper functions for initializing various components
    void initAvailableDirections();
    bool initSDL();
    void initAnts();
    void initForage();

    // Helper functions for update operations
    void updateAnts(const int interval);

    void updateForagePositions(const int interval);

    bool updateDirectionIfNearFood(Ant* ant);

    bool hasSalvagedFood(const double x, const double y);

    bool reachedNest(const double x, const double y);

    // Helper functions for rendering
    void renderNest();
    void renderCurrentBuffer();
    void setTrailColor(const Ant& ant);

    void setAntColor(const Position& pos, const double radius, Uint8 red,
                     Uint8 green, Uint8 blue);
    void setForageColor();
    void setNestColor();

    // Function to destroy
    void destroy();

    // Function to set pixel value
    void setPixelValue(int posx, int posy, Uint8 red, Uint8 green, Uint8 blue);

    // Function to do box blur
    void boxBlur();

    // Function to decayPheromones over time
    void decayPheromones();

    // Function to get Quantized direction
    double getQuantizedDirection(const double theta);

    double wrapToPi(const double theta);

    Ants ants_;
    Nest nest_;
    Forage forage_;

    // Available directions
    std::vector<double> directions_;
    std::vector<double> rand_directions_;
    double randomization_prob_;

    // SDL Objects
    SDL_Window* window_;
    SDL_Renderer* renderer_;
    SDL_Texture* texture_;

    Uint32* buffer_;
    Uint32* blur_buffer_;
    Uint32* pheromone_buffer_;
};

}  // namespace ant_colony
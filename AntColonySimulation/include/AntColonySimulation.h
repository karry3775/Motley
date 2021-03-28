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
    bool initSDL();
    void initAnts();

    // Helper functions for update operations
    void updateAnts(const int interval);

    // Helper functions for rendering
    void renderNest();
    void renderAnts();
    void renderCurrentBuffer();
    void setTrailColor(const Ant& ant, Uint8 red, Uint8 green, Uint8 blue);
    void setAntColor(const Position& pos, const double radius, Uint8 red,
                     Uint8 green, Uint8 blue);

    // Function to destroy
    void destroy();

    // Function to set pixel value
    void setPixelValue(int posx, int posy, Uint8 red, Uint8 green, Uint8 blue);

    // Function to do box blur
    void boxBlur();

    Ants ants_;
    Nest nest_;

    // SDL Objects
    SDL_Window* window_;
    SDL_Renderer* renderer_;
    SDL_Texture* texture_;

    Uint32* buffer_;
    Uint32* blur_buffer_;
};

}  // namespace ant_colony
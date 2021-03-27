#include <Utils.h>

namespace ant_colony {

// Renders a outlined circle based on MidPoint Circle Algorithm
// Source :
// https://stackoverflow.com/questions/38334081/howto-draw-circles-arcs-and-vector-graphics-in-sdl

void Utils::renderDrawCircle(SDL_Renderer* renderer, const uint32_t cx,
                             const uint32_t cy, const uint32_t radius) {
    const uint32_t diameter = (2 * radius);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y) {
        // Each of the floowing renderes an octant of the circle
        SDL_RenderDrawPoint(renderer, cx + x, cy - y);
        SDL_RenderDrawPoint(renderer, cx + x, cy + y);
        SDL_RenderDrawPoint(renderer, cx - x, cy - y);
        SDL_RenderDrawPoint(renderer, cx - x, cy + y);
        SDL_RenderDrawPoint(renderer, cx + y, cy - x);
        SDL_RenderDrawPoint(renderer, cx + y, cy + x);
        SDL_RenderDrawPoint(renderer, cx - y, cy - x);
        SDL_RenderDrawPoint(renderer, cx - y, cy + x);

        if (error <= 0) {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0) {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

// Renders a Fill Circle
// Source:
// https://gist.github.com/Gumichan01/332c26f6197a432db91cc4327fcabb1c
void Utils::renderFillCircle(SDL_Renderer* renderer, const uint32_t cx,
                             const uint32_t cy, const uint32_t radius) {
    int offsetx, offsety, d;

    offsetx = 0;
    offsety = radius;
    d = radius - 1;

    while (offsety >= offsetx) {
        SDL_RenderDrawLine(renderer, cx - offsety, cy + offsetx, cx + offsety,
                           cy + offsetx);
        SDL_RenderDrawLine(renderer, cx - offsetx, cy + offsety, cx + offsetx,
                           cy + offsety);
        SDL_RenderDrawLine(renderer, cx - offsetx, cy - offsety, cx + offsetx,
                           cy - offsety);
        SDL_RenderDrawLine(renderer, cx - offsety, cy - offsetx, cx + offsety,
                           cy - offsetx);

        if (d >= 2 * offsetx) {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        } else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        } else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }
}

double Utils::wrapToPi(const double theta) {
    return std::atan2(std::sin(theta), std::cos(theta));
}

}  // namespace ant_colony
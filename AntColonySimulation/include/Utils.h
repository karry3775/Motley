#pragma once

#include <Core.h>

namespace ant_colony {

struct Utils {
    static void renderDrawCircle(SDL_Renderer* renderer, const uint32_t cx,
                                 const uint32_t cy, const uint32_t radius);
    static void renderFillCircle(SDL_Renderer* renderer, const uint32_t cx,
                                 const uint32_t cy, const uint32_t radius);

    static double wrapToPi(const double theta);
};

}  // namespace ant_colony
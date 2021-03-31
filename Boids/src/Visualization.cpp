#include <Visualization.h>

namespace boids {

Viz::Viz() {
    boid_color = {102, 179, 255, 255};
    width = 500;
    height = 500;
    title = "Boids";

    // Initialize the viz
    init();
}

void Viz::init() {
    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Initialize SDL: %s",
                     SDL_GetError());
        return;
    }

    // Create and window and renderer
    if (SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Create window and renderer: %s", SDL_GetError());
        return;
    }

    // Create a texture
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_STATIC, width, height);

    // check for null
    if (texture == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Create Texture: %s",
                     SDL_GetError());
        destroy();
        return;
    }

    // Initialize buffer
    buffer = new Uint32[width * height];
    blur_buffer = new Uint32[width * height];
    memset(buffer, 0, width * height * sizeof(Uint32));
    memset(blur_buffer, 0, width * height * sizeof(Uint32));

    // Set window title
    SDL_SetWindowTitle(window, title);
}

void Viz::destroy() {
    // free the buffer
    if (buffer != nullptr) delete[] buffer;
    // free the blur buffer
    if (blur_buffer != nullptr) delete[] blur_buffer;
    // destroy the texture if exists
    if (texture != nullptr) SDL_DestroyTexture(texture);
    // destroy renderer if exists
    if (renderer != nullptr) SDL_DestroyRenderer(renderer);
    // destroy the window if its exists
    if (window != nullptr) SDL_DestroyWindow(window);
    // finally Quit
    SDL_Quit();
}

void Viz::setPixelColor(int posx, int posy, Uint8 red, Uint8 green,
                        Uint8 blue) {
    if (posx <= 0 || posx >= width || posy <= 0 || posy >= height) return;
    Uint32 color = 0;

    color += red;
    color <<= 8;
    color += green;
    color <<= 8;
    color += blue;
    color <<= 8;
    color += 0xFF;  // this is for alpha value

    buffer[(posy * width) + posx] = color;
}
void Viz::boxBlur() {
    // Swap the buffers so that we do not mess up the original buffer
    Uint32* temp_buffer = buffer;
    buffer = blur_buffer;
    blur_buffer = temp_buffer;

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            int red_sum = 0;
            int green_sum = 0;
            int blue_sum = 0;

            // Now we need to blur with a kernel of 3x3
            // TODO: Make the kernel size a gflag later
            for (int row = -1; row <= 1; ++row) {
                for (int col = -1; col <= 1; ++col) {
                    int current_x = x + col;
                    int current_y = y + row;

                    if (current_x >= 0 && current_x < width && current_y >= 0 &&
                        current_y < height) {
                        Uint32 color =
                            blur_buffer[current_y * width + current_x];

                        Uint8 red = color >> 24;
                        Uint8 green = color >> 16;
                        Uint8 blue = color >> 8;

                        red_sum += red;
                        green_sum += green;
                        blue_sum += blue;
                    }
                }
            }

            // Take average of the kernel values
            Uint8 red = red_sum / 9;
            Uint8 green = green_sum / 9;
            Uint8 blue = blue_sum / 9;

            // set the pixel value
            setPixelColor(x, y, red, green, blue);
        }
    }
}

void Viz::renderCurrentBuffer() {
    SDL_UpdateTexture(texture, NULL, buffer, width * sizeof(Uint32));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

}  // namespace boids
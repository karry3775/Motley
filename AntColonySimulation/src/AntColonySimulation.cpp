#include <AntColonySimulation.h>

namespace ant_colony {

AntColonySim::AntColonySim(const uint32_t num_ants) {
    // Resize  the Ants vector
    ants_.resize(num_ants);

    // Initialize random positions for ants
    initAnts();

    // Initialize nest
    nest_ = Nest(Defaults::nest_pos, Defaults::nest_radius);

    // Initialize SDL
    initSDL();
}

void AntColonySim::show() {
    // Game loop
    SDL_bool quit = SDL_FALSE;

    int last_time = -1.0;

    while (!quit) {
        // Very important to get reliable update
        int time_elapsed = SDL_GetTicks();
        if (last_time == -1) last_time = time_elapsed;
        int interval = time_elapsed - last_time;
        last_time = time_elapsed;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = SDL_TRUE;
                break;
            }
        }

        // Set Pixel values for ants into the buffer
        updateAnts(interval);

        // renderBuffer
        renderCurrentBuffer();

        // box blur
        boxBlur();

        // Sleep
        // usleep(Defaults::sleep_duration_ms);
    }

    // Destroy
    destroy();
}

/*------------------ Initialization functions ---------------------*/

void AntColonySim::initAnts() {
    // Initialize seed
    srand(time(NULL));
    for (auto& ant : ants_) {
        // Initialize each ant with random params
        // For now let us just assign random positions
        double rand_x = rand() % (Defaults::window_width);
        double rand_y = rand() % (Defaults::window_height);
        double rand_dir = rand() % (int)M_PI;

        ant = new Ant(Position(rand_x, rand_y), rand_dir, 0, 0);
    }
}

bool AntColonySim::initSDL() {
    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Initialize SDL: %s",
                     SDL_GetError());
        return false;
    }

    // Create a window and renderer
    if (SDL_CreateWindowAndRenderer(Defaults::window_width,
                                    Defaults::window_height, 0, &window_,
                                    &renderer_) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Create window and renderer: %s", SDL_GetError());
        return false;
    }

    // Create a texture
    texture_ = SDL_CreateTexture(
        renderer_, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC,
        Defaults::window_width, Defaults::window_height);
    // check for null
    if (texture_ == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Create texture: %s",
                     SDL_GetError());
        // Destroy window and re
        destroy();
        return false;
    }

    // Initialize our buffer
    buffer_ = new Uint32[Defaults::window_width * Defaults::window_height];
    blur_buffer_ = new Uint32[Defaults::window_width * Defaults::window_height];
    memset(buffer_, 0,
           Defaults::window_width * Defaults::window_height * sizeof(Uint32));
    memset(blur_buffer_, 0,
           Defaults::window_width * Defaults::window_height * sizeof(Uint32));

    // Set Window Title
    SDL_SetWindowTitle(window_, Defaults::window_title);

    return true;
}

/*---------------------- Update functions ---------------------------*/
void AntColonySim::updateAnts(const int interval) {
    for (auto& ant : ants_) {
        // Set pixel value for the current ant
        setPixelValue(ant->pos.x, ant->pos.y, Defaults::food_color.r,
                      Defaults::food_color.g, Defaults::food_color.b);

        // Modify the position of the ant based on direction and move_speed
        ant->pos.x += std::cos(ant->direction) * ant->move_speed;
        ant->pos.y += std::sin(ant->direction) * ant->move_speed;

        if (ant->pos.x < 0 || ant->pos.x > Defaults::window_width) {
            ant->move_speed = -ant->move_speed;
        }
        if (ant->pos.y < 0 || ant->pos.y > Defaults::window_height) {
            ant->move_speed = -ant->move_speed;
        }

        ant->direction +=
            ((double)rand() / RAND_MAX) * 2 * Defaults::max_angle_window -
            Defaults::max_angle_window;
    }
}

/*---------------------- Rendering functions ------------------------*/
void AntColonySim::renderNest() {
    // Set render draw color
    SDL_SetRenderDrawColor(renderer_, Defaults::nest_color.r,
                           Defaults::nest_color.g, Defaults::nest_color.b,
                           Defaults::nest_color.a);
    // Draw the nest as a circle
    Utils::renderFillCircle(renderer_, Defaults::nest_pos.x,
                            Defaults::nest_pos.y, Defaults::nest_radius);
}

void AntColonySim::renderAnts() {
    // Set render draw color
    SDL_SetRenderDrawColor(renderer_, Defaults::ant_color.r,
                           Defaults::ant_color.g, Defaults::ant_color.b,
                           Defaults::ant_color.a);

    for (const auto& ant : ants_) {
        Utils::renderFillCircle(renderer_, ant->pos.x, ant->pos.y, ant->radius);
    }
}

void AntColonySim::renderCurrentBuffer() {
    SDL_UpdateTexture(texture_, NULL, buffer_,
                      Defaults::window_width * sizeof(Uint32));
    SDL_RenderClear(renderer_);
    SDL_RenderCopy(renderer_, texture_, NULL, NULL);
    SDL_RenderPresent(renderer_);
}

/*--------------------- Function to destroy -----------------------*/
void AntColonySim::destroy() {
    // free the buffer
    if (buffer_ != nullptr) delete[] buffer_;
    // free the blur buffer
    if (blur_buffer_ != nullptr) delete[] blur_buffer_;
    // destroy the texture if exists
    if (texture_ != nullptr) SDL_DestroyTexture(texture_);
    // destroy renderer if exists
    if (renderer_ != nullptr) SDL_DestroyRenderer(renderer_);
    // destroy the window if its exists
    if (window_ != nullptr) SDL_DestroyWindow(window_);
    // finally Quit
    SDL_Quit();
}

/*--------------------- Function to set pixel value------------------*/
void AntColonySim::setPixelValue(int posx, int posy, Uint8 red, Uint8 green,
                                 Uint8 blue) {
    Uint32 color = 0;

    color += red;
    color << 8;
    color += green;
    color <<= 8;
    color += blue;
    color <<= 8;
    color += 0xFF;  // this is for alpha value

    buffer_[(posy * Defaults::window_width) + posx] = color;
}

/*----------------Function to do box blur-----------------------------*/
void AntColonySim::boxBlur() {
    // Swap the buffers so that we do not mess up the original buffer
    Uint32* temp_buffer = buffer_;
    buffer_ = blur_buffer_;
    blur_buffer_ = temp_buffer;

    for (int x = 0; x < Defaults::window_width; ++x) {
        for (int y = 0; y < Defaults::window_height; ++y) {
            int red_sum = 0;
            int green_sum = 0;
            int blue_sum = 0;

            // Now we need to blur with a kernel of 3x3
            // TODO: Make the kernel size a gflag later
            for (int row = -1; row <= 1; ++row) {
                for (int col = -1; col <= 1; ++col) {
                    int current_x = x + col;
                    int current_y = y + row;

                    if (current_x >= 0 && current_x < Defaults::window_width &&
                        current_y >= 0 && current_y < Defaults::window_height) {
                        Uint32 color =
                            blur_buffer_[current_y * Defaults::window_width +
                                         current_x];

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
            setPixelValue(x, y, red, green, blue);
        }
    }
}

}  // namespace ant_colony
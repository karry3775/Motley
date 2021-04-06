#include <AntColonySimulation.h>

namespace ant_colony {

AntColonySim::AntColonySim(const uint32_t num_ants) {
    // Initialize seed
    srand(time(NULL));

    // Resize  the Ants vector
    ants_.resize(num_ants);

    // Initialize nest
    nest_ = Nest(Defaults::nest_pos, Defaults::nest_radius);

    // Initialize random positions for ants
    initAnts();

    // Initialize forage
    initForage();

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

        // decay pheromones
        decayPheromones();

        // Set Pixel values for ants into the buffer
        updateAnts(interval);

        // Experimental: Update forage locations
        // updateForagePositions(interval);

        // set Color for forage
        setForageColor();

        // set Nest color
        setNestColor();

        // renderBuffer
        renderCurrentBuffer();

        // box blur
        boxBlur();
    }

    // Destroy
    destroy();
}

/*------------------ Initialization functions ---------------------*/

void AntColonySim::initAnts() {
    for (auto& ant : ants_) {
        // Initialize each ant with random params
        // For now let us just assign random positions
        double rand_x = Defaults::window_width / 2;
        double rand_y = Defaults::window_height / 2;
        double rand_dir = (((double)rand()) / RAND_MAX) * 2 * M_PI - M_PI;

        ant = new Ant(Position(rand_x, rand_y), rand_dir, 50);
        ant->trail.emplace_back(ant->pos);
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
    pheromone_buffer_ =
        new Uint32[Defaults::window_width * Defaults::window_height];
    memset(buffer_, 0,
           Defaults::window_width * Defaults::window_height * sizeof(Uint32));
    memset(blur_buffer_, 0,
           Defaults::window_width * Defaults::window_height * sizeof(Uint32));
    memset(pheromone_buffer_, 0,
           Defaults::window_width * Defaults::window_height * sizeof(Uint32));

    // Set Window Title
    SDL_SetWindowTitle(window_, Defaults::window_title);

    return true;
}

void AntColonySim::initForage() {
    // Resize Forage
    forage_.food.resize(Defaults::forage_size);
    // Set radius
    forage_.radius = Defaults::forage_radius;

    // Set food in locations
    forage_.food[0].x = Defaults::window_width / 4;
    forage_.food[0].y = Defaults::window_height / 4;

    forage_.food[1].x = 3 * Defaults::window_width / 4;
    forage_.food[1].y = Defaults::window_height / 4;

    forage_.food[2].x = Defaults::window_width / 4;
    forage_.food[2].y = 3 * Defaults::window_height / 4;

    forage_.food[3].x = 3 * Defaults::window_width / 4;
    forage_.food[3].y = 3 * Defaults::window_width / 4;

    forage_.food[4].x = Defaults::window_width / 2;
    forage_.food[4].y = Defaults::window_height / 8;

    forage_.food[5].x = Defaults::window_width / 8;
    forage_.food[5].y = Defaults::window_height / 2;

    forage_.food[6].x = Defaults::window_width / 2;
    forage_.food[6].y = 7 * Defaults::window_height / 8;

    forage_.food[7].x = 7 * Defaults::window_width / 8;
    forage_.food[7].y = Defaults::window_width / 2;
}

/*---------------------- Update functions ---------------------------*/
void AntColonySim::updateAnts(const int interval) {
    for (auto& ant : ants_) {
        int time_elapsed = SDL_GetTicks();
        double green_factor = sin(time_elapsed * 0.0001);
        double red_factor = sin(time_elapsed * 0.0001 + M_PI / 4);
        double blue_factor = sin(time_elapsed * 0.0003 + M_PI / 8);
        // Set pixel value for the current ant
        // NOTE: Use this for changing colors
        // Uint8 red = 10 + Uint8(abs(255 * red_factor));
        // Uint8 green = 10 + Uint8(abs(255 * green_factor));
        // Uint8 blue = 10 + Uint8(abs(255 * blue_factor));

        Uint8 red, green, blue;

        if (ant->has_salvaged) {
            red = Defaults::trail_return_color.r;
            green = Defaults::trail_return_color.g;
            blue = Defaults::trail_return_color.b;

            // the position from now on should go to the return trail
            ant->return_trail.emplace_back(ant->pos);

            // Desposit the positions into the pheromone buffer
            pheromone_buffer_[int(ant->pos.y) * Defaults::window_width +
                              int(ant->pos.x)] += Defaults::pheromone_strength;

            // Size limiting
            // TODO: Make this param
            if (ant->return_trail.size() > 10) {
                ant->return_trail.pop_front();
            }

        } else {
            red = Defaults::trail_seek_color.r;
            green = Defaults::trail_seek_color.g;
            blue = Defaults::trail_seek_color.b;

            // the position from now on should go to the seek trail
            ant->seek_trail.emplace_back(ant->pos);
        }

        setTrailColor(*ant);

        // Modify the position of the ant based on direction and move_speed
        ant->pos.x += std::cos(ant->direction) * ant->move_speed;
        ant->pos.y += std::sin(ant->direction) * ant->move_speed;

        // If reached within a certain threshold of the food source
        // return to home
        if (hasSalvagedFood(ant->pos.x, ant->pos.y)) {
            ant->has_salvaged = true;
        }

        // reached back at home set the has salvaged flag to false
        if (reachedNest(ant->pos.x, ant->pos.y)) {
            ant->has_salvaged = false;
            // reset the trails
            ant->return_trail.clear();
            ant->seek_trail.clear();
        }

        if (ant->has_salvaged) {
            // Return home
            ant->direction =
                std::atan2(nest_.pos.y - ant->pos.y, nest_.pos.x - ant->pos.x);
            ant->direction +=
                ((double)rand() / RAND_MAX) * 2 * Defaults::max_angle_window -
                Defaults::max_angle_window;
        }

        // Update direction if near food when it is seeking for food
        if (!ant->has_salvaged && updateDirectionIfNearFood(ant)) {
            continue;
        }

        if (ant->pos.x < 0 || ant->pos.x > Defaults::window_width ||
            ant->pos.y < 0 || ant->pos.y > Defaults::window_height) {
            ant->direction += M_PI / 2;
        } else {
            ant->direction +=
                ((double)rand() / RAND_MAX) * 2 * Defaults::max_angle_window -
                Defaults::max_angle_window;
        }
    }
}

void AntColonySim::updateForagePositions(const int interval) {
    for (auto& food_pos : forage_.food) {
        // First get the angle from the nest
        double angle_from_nest =
            std::atan2(food_pos.y - nest_.pos.y, food_pos.x - nest_.pos.x);
        double angle_tangent = angle_from_nest + M_PI / 2;

        food_pos.x += std::cos(angle_tangent) * interval * 0.025;
        food_pos.y += std::sin(angle_tangent) * interval * 0.025;
    }
}

bool AntColonySim::updateDirectionIfNearFood(Ant* ant) {
    // TODO: Make 10 a gflags or default
    for (auto food_pos : forage_.food) {
        if ((ant->pos.x - food_pos.x) * (ant->pos.x - food_pos.x) +
                (ant->pos.y - food_pos.y) * (ant->pos.y - food_pos.y) <
            (forage_.radius + 100) * (forage_.radius + 100)) {
            // update direction
            ant->direction =
                std::atan2(food_pos.y - ant->pos.y, food_pos.x - ant->pos.x);
            ant->direction +=
                ((double)rand() / RAND_MAX) * 2 * Defaults::max_angle_window -
                Defaults::max_angle_window;

            return true;
        }
    }

    return false;
}

bool AntColonySim::hasSalvagedFood(const double x, const double y) {
    for (auto food_pos : forage_.food) {
        if ((x - food_pos.x) * (x - food_pos.x) +
                (y - food_pos.y) * (y - food_pos.y) <
            forage_.radius * forage_.radius) {
            return true;
        }
    }

    return false;
}

bool AntColonySim::reachedNest(const double x, const double y) {
    if ((x - Defaults::nest_pos.x) * (x - Defaults::nest_pos.x) +
            (y - Defaults::nest_pos.y) * (y - Defaults::nest_pos.y) <
        Defaults::food_salvation_thresh * Defaults::food_salvation_thresh) {
        return true;
    }
    return false;
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

void AntColonySim::renderCurrentBuffer() {
    SDL_UpdateTexture(texture_, NULL, buffer_,
                      Defaults::window_width * sizeof(Uint32));
    SDL_RenderClear(renderer_);
    SDL_RenderCopy(renderer_, texture_, NULL, NULL);
    SDL_RenderPresent(renderer_);
}

void AntColonySim::setTrailColor(const Ant& ant) {
    // for (auto trail_pos : ant.seek_trail) {
    //     setPixelValue(trail_pos.x, trail_pos.y, Defaults::trail_seek_color.r,
    //                   Defaults::trail_seek_color.g,
    //                   Defaults::trail_seek_color.b);
    // }

    for (auto trail_pos : ant.return_trail) {
        setPixelValue(trail_pos.x, trail_pos.y, Defaults::trail_return_color.r,
                      Defaults::trail_return_color.g,
                      Defaults::trail_return_color.b);
    }

    setAntColor(ant.pos, ant.radius, Defaults::ant_color.r,
                Defaults::ant_color.g, Defaults::ant_color.b);
}
void AntColonySim::setAntColor(const Position& pos, const double radius,
                               Uint8 red, Uint8 green, Uint8 blue) {
    for (int x = -radius; x < radius; ++x) {
        for (int y = -radius; y < radius; ++y) {
            if (x * x + y * y <= radius * radius) {
                setPixelValue(x + pos.x, y + pos.y, red, green, blue);
            }
        }
    }
}

void AntColonySim::setForageColor() {
    for (auto& food_pos : forage_.food) {
        for (int x = -forage_.radius; x < forage_.radius; ++x) {
            for (int y = -forage_.radius; y < forage_.radius; ++y) {
                if (x * x + y * y <= forage_.radius * forage_.radius) {
                    setPixelValue(x + food_pos.x, y + food_pos.y,
                                  Defaults::forage_color.r,
                                  Defaults::forage_color.g,
                                  Defaults::forage_color.b);
                }
            }
        }
    }
}

void AntColonySim::setNestColor() {
    for (int x = -nest_.radius; x < nest_.radius; ++x) {
        for (int y = -nest_.radius; y < nest_.radius; ++y) {
            if (x * x + y * y <= nest_.radius * nest_.radius) {
                setPixelValue(x + nest_.pos.x, y + nest_.pos.y,
                              Defaults::nest_color.r, Defaults::nest_color.g,
                              Defaults::nest_color.b);
            }
        }
    }
}

/*--------------------- Function to destroy -----------------------*/
void AntColonySim::destroy() {
    // free the buffer
    if (buffer_ != nullptr) delete[] buffer_;
    // free the blur buffer
    if (blur_buffer_ != nullptr) delete[] blur_buffer_;
    // free the pheromone buffer
    if (pheromone_buffer_ != nullptr) delete[] pheromone_buffer_;
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
    if (posx <= 0 || posx >= Defaults::window_width || posy <= 0 ||
        posy >= Defaults::window_height)
        return;
    Uint32 color = 0;

    color += red;
    color <<= 8;
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

/*------------------ Function to decay Pheromones -----------------------*/
void AntColonySim::decayPheromones() {
    // temp: Could lead in seg fault if not handled carefully
    for (int x = 0; x < Defaults::window_width; ++x) {
        for (int y = 0; y < Defaults::window_height; ++y) {
            if (pheromone_buffer_[y * Defaults::window_width + x] > 0) {
                // temp: also as we are on to it, lets also render the things
                Uint8 green = Uint8(
                    (double(pheromone_buffer_[y * Defaults::window_width + x]) *
                     255) /
                    100);
                Uint8 red = 0;
                Uint8 blue = 100;

                setPixelValue(x, y, red, green, blue);
                pheromone_buffer_[y * Defaults::window_width + x] -=
                    Defaults::decay_rate;
            }
        }
    }
}

}  // namespace ant_colony
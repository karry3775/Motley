#include <iostream>
#include <SDL2/SDL.h>

int main(int argc, char** argv) {


	SDL_Window *window; // pointer to window object

	// Create an application window with the following settings
	window = SDL_CreateWindow(
			"An SDL2 Window", 		// window title
			SDL_WINDOWPOS_CENTERED, // intitial x
			SDL_WINDOWPOS_CENTERED, // initial y
			640, 					// width in pixels
			480, 					// height in pixels
			SDL_WINDOW_OPENGL		// one of many flags
			);

	if (window == nullptr) {
		// window was not created and
		std::cout << "Could not create window \n " << SDL_GetError();
		SDL_Quit();
		return 1;
	}

	// Create a renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// check if the renderer is null
	if(renderer == nullptr) {
		std::cout << "Could not create renderer \n" << SDL_GetError();
		// Destroy window
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 2;
	}

	// source for the following code:
	// https://dev.to/noah11012/using-sdl2-drawing-rectangles-3hc2
	
	SDL_RenderClear(renderer);
	
	SDL_Rect rect;
	rect.x = 250;
	rect.y = 150;
	rect.w = 200;
	rect.h = 200;

	bool quit = false;
	while(!quit) {
		
		SDL_Event e;
		
		// render logic
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(renderer, &rect);

		SDL_RenderPresent(renderer);

		while(SDL_PollEvent(&e) > 0) {
			switch(e.type) {
				case SDL_QUIT:
					quit = true;
					break;
			}		
		}
	}

	return 0;
}

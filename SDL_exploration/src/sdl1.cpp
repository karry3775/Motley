#include <iostream>
#include <SDL2/SDL.h>

int main(int argc, char** argv) {


	SDL_Window *window; // pointer to window object

	// Create an application window with the following settings
	window = SDL_CreateWindow(
			"An SDL2 Window", 		// window title
			SDL_WINDOWPOS_CENTERED, // intitial x
			SDL_WINDOWPOS_CENTERED, // initial y
			1000, 					// width in pixels
			1000, 					// height in pixels
			SDL_WINDOW_OPENGL		// one of many flags
			);

	if (window == nullptr) {
		// window was not created and
		std::cout << "Could not create window \n " << SDL_GetError();
		SDL_Quit();
		return 1;
	}

	// Create a renderer to render our images
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// check if the renderer is null
	if(renderer == nullptr) {
		std::cout << "Could not create renderer \n" << SDL_GetError();
		// Destroy window
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 2;
	}

	// loads image to our graphics hardware memory
	SDL_Texture* texture = SDL_CreateTexture(renderer, 
											 SDL_PIXELFORMAT_RGBA8888,
											 SDL_TEXTUREACCESS_STATIC,
											 1000, 1000);
	
	if (texture == nullptr ) {
		std::cout << "Could not create texture \n" << SDL_GetError() <<  std::endl;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 3;
	}

	// lets us control our image position
	// so that we can move it with our keyboard
	SDL_Rect dest;

	// connnects our texture with dest to control position
	SDL_QueryTexture(texture, NULL, NULL, &dest.w , &dest.h);

	// adjust height and width of our image box
	dest.w /= 6;
	dest.h /= 6;

	// Sets initial x and y position of the object
	dest.x = (1000 - dest.w) / 2;
	dest.y = (1000 - dest.h) / 2;

	// controls animation loop
	bool quit = false;

	// speed of the box
	int speed = 300;

	// animation loop
	while (!quit) {
		SDL_Event event;

		// Events management
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					// handling close of the x button
					quit = true;	
					break;
				case SDL_KEYDOWN:
					// keyboard api for key pressed
					switch (event.key.keysym.scancode) {
						case SDL_SCANCODE_W:
						case SDL_SCANCODE_UP:
							dest.y -= speed / 30;
							break;
						case SDL_SCANCODE_A:
						case SDL_SCANCODE_LEFT:
							dest.x -= speed / 30;
							break;
						case SDL_SCANCODE_S:
						case SDL_SCANCODE_DOWN:
							dest.y += speed / 30;
							break;
						case SDL_SCANCODE_D:
						case SDL_SCANCODE_RIGHT:
							dest.x += speed / 30;
							break;
					}
			}
		}		
		
		// right boundary
		if (dest.x + dest.w > 1000) dest.x = 1000 - dest.w;
		
		// left boundary
		if (dest.x < 1000) dest.x = 0;

		// bottom boundary
		if(dest.y + dest.h > 1000) dest.y = 1000 - dest.h;

		// upper boundary
		if(dest.y < 0) dest.y = 0;


		// Clears the screen
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, &dest);

		// Triggers the double buffers for 
		// multiple rendering
		SDL_RenderPresent(renderer);

		// calculates to 60 FPS
		SDL_Delay(1000 / 60);
	}
	
	// destroy texture
	SDL_DestroyTexture(texture);

	// destroy renderer
	SDL_DestroyRenderer(renderer);

	// destroy window
	SDL_DestroyWindow(window);

	// quit
	SDL_Quit();

	return 0;
}

#include <SDL2/SDL.h>

class Grid{

public:
	Grid(int width, int height, int cell_size) {
		m_width = width;
		m_height = height;
		m_cell_size = cell_size;

	}

	void showGrid() {
		setGrid();	
		if(!initGrid()) return;
		gameLoop();
	}

	
private:
	int m_width;         // width of the grid in terms of number of cells
	int m_height;        // height of the grid in terms of number of cells
	int m_cell_size;     // size of the grid cell
	
	int m_pixel_width;   // width of the grid in pixels
	int m_pixel_height;  // height of the grid in pixels
	
	// SDL Colors
	SDL_Color m_background_color;
	SDL_Color m_line_color;
	SDL_Color m_cursor_color;
	SDL_Color m_ghost_cursor_color;
	
	// SDL objects
	SDL_Rect m_cursor; // rectangular object for cursor
	SDL_Rect m_ghost_cursor; // rectangular object for ghost cursor
	SDL_Window *m_window; // window object
	SDL_Renderer *m_renderer; // renderer object
		

	
	void setGrid() {
		// Set the grid window parameters
		m_window_width = m_width * m_cell_size;
		m_window_height = m_height * m_cell_size;

		// Set the color values
		m_background_color = {22, 22, 22, 255}; // Barley black
		m_line_color = {44, 44, 44, 255}; // Dark Grey
		m_cursor_color = {255, 255, 255, 255}; // White
		m_ghost_cursor_color = {44, 44, 44, 255}; // Dark Grey

		// Define default positions for cursor at the center of the screen
		m_cursor = {
			.x = (m_pixel_width / 2)
			.y = (m_pixel_height / 2)
			.w = m_cell_size;
			.h = m_cell_size;
		}

		// Define the default position of ghost cursor to be also at the center
		// but this will be updated to be one cell below the mouse cursor
		m_ghost_cursor = m_cursor;
	}

	bool initGrid() {
		// Init SDL
		if(SDL_Init(SDL_INIT_VIDEO) < 0 ){
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION , "Initialize SDL : %s",
						 SDL_GetError());
			return false;
		}

		// Create window and renderer
		if(SDL_CreateWindowAndRenderer(m_pixel_width, m_pixel_height, 
									   0, &m_window, &_m_renderer) < 0) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Create window and renderer: %s",
						 SDL_GetError());
			return false;

		}
		
		// Set window title
		SDL_SetWindowTitle(m_window, "Grid");

		return true;	

	}

	void gameLoop() {
		SDL_bool quit = SDL_FALSE;	
		SDL_bool mouse_active = SDL_FALSE;
		SDL_bool mouse_hover = SDL_FALSE;

		while(!quit){
			SDL_Event event;
			// Poll the events
			while(SDL_PollEvent(&event)) {
				switch(event.type){
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym) {
					case SDLK_w:
					case SDLK_UP:
						m_cursor.y -= m_cell_size;
						break;
					case SDLK_s:
					case SDLK_DOWN:
						m_cursor.y += m_cell_size;
						break;
					case SDLK_a:
					case SDLK_LEFT:
						m_cursor.x -= m_cell_size;
						break;
					case SDLK_d:
					case SDLK_RIGHT:
						m_cursor.x += m_cell_size;
						break;
					} // end of keydown switch
					break;
				case SDL_MOUSEBUTTONDOWN:
					// Set the cursor position to mouse position
					m_cursor.x = event.motion.x;
					m_cursor.y = event.motion.y;
					break; 
				case SDL_MOUSEMOTION:
					// Set the position of the ghost cursor, when you are not clicking
					m_ghost_cursor.x = event.motion.x;
					m_ghost_cursor.y = event.motion.y;

					if(!mouse_active) mouse_active = SDL_TRUE;
					break;
				case SDL_WINDOWEVENT:
					if(event.window.event == SDL_WINDOWEVENT_ETNER && !mouse_hover)
						mouse_hover = SDL_TRUE;
					else if(event.window.event == SDL_WINDOWEVENT_LEAVE && mouse_hover)
						mouse_hover = SDL_FALSE;
					break;
				case SDL_QUIT:
					quit = SDL_TRUE;
					break;
				} // end of event type switch
			} // end of poll event

			// Do the actual drawing here
			SDL_SetRenderDrawColor(m_renderer, m_background.r m_background.g,
								   m_background.b, m_background.a);
			SDL_RenderClear(renderer);	

			// Draw grid lines
			SDL_SetRenderDrawColor(m_renderer, m_line_color.r, m_line_color.g,
								   m_line_color.b, m_line_color.a);
			for(int x = 0; x <  m_pixel_width; x += m_cell_size) {
				SDL_RenderDrawLine(renderer, x, 0, x, m_pixel_height);
			}

			for(int y = 0; y < m_pixel_height; y += m_cell_size) {
				SDL_RenderDrawLine(renderer, 0, y, m_pixel_width, y);
			}


			// Draw ghost cursor
			if(mouse_active && mouse_hover) {
				CONTINUE;
			}
		} // end of game loop


	}


	


};

int main(int argc, char** argv) {

	// Initialize SDL environment
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Initialize SDL %s",
					 SDL_GetError());
		return EXIT_FAILURE;
	}

	
	return 0;
}

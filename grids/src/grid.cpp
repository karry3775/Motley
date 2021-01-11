#include <iostream>

/**
* The goal of this program is to take user input and generate a grid on
* the screen using like '*' 
**/

void generateGrid(const int& grid_size) {
	int rows = grid_size * 2 + 1;
	int cols = grid_size * 2 + 1;

	bool flag = false;

	for(int i = 0; i < rows; ++i) {
		flag = !flag;
		for(int j = 0; j < cols; ++j) {
			if(!flag && j%2 != 0) std::cout << "  ";
			else std::cout << "* ";			
		}	
		std::cout << std::endl;
	}

}


int main(int argc, char** argv) {

	// Get the user input
	int grid_size;
	std::cout << "Enter the size of the grid" << std::endl; 
	std::cin >> grid_size;
	std::cout << "You entered the size of the grid as: " << grid_size << std::endl;

	generateGrid(grid_size); 
	return 0;
}

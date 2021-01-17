#include <SDL2/SDL.h>
#include <iostream>

class Maze{

public:
	Maze();

	void display() {};
	//
	// Getters
	//
	int getWidth() const {};

	int getHeight() const {};

	int getResolution() const {};
	

private:
	int m_width;
	int m_height;
	int m_resolution;

	
	// 
	// Setters
	//
	void setWidth() {};

	void setHeight() {};

	void setResolution() {};
	 

};

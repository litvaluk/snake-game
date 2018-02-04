#ifndef SNAKE_H_
#define SNAKE_H_

#include "SDL2/SDL.h"

class Snake{
	
	public:
		Snake(int x, int y, int len, int direction);
		~Snake();
		
		void draw(SDL_Renderer* renderer);
		void move();
		void grow();
		void rotateLeft();
		void rotateRight();
		void setEyes();
		
		bool checkBorderCollision();
		bool checkSelfCollision();
		
		int x, y;
		int len, direction;
		SDL_Rect* snakeBlock;
		
	private:
		SDL_Rect leftEye;
		SDL_Rect rightEye;
		int size;
		int lastX, lastY;		
		
};

#endif

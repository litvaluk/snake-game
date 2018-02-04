#ifndef FOOD_H_
#define FOOD_H_

#include "SDL2/SDL.h"

class Food{
	
	public:
		Food(SDL_Rect* snakeBlock, int c);
		~Food();
		void draw(SDL_Renderer* renderer);
		void newPosition(SDL_Rect* snakeBlock, int c);
		
		int x;
		int y;
	private:
		SDL_Rect foodBlock;
		int xCoords[25] = {50, 95, 140, 185, 230,
				 				 275, 320, 365, 410, 455,
								 500, 545, 590, 635, 680,
								 725, 770, 815, 860, 905,
				  				 950, 995, 1040, 1085, 1130};

		int yCoords[15] = {50, 95, 140, 185, 230,
				  				 275, 320, 365, 410, 455,
				 				 500, 545, 590, 635, 680,};
		
};

#endif

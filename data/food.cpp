#include <cstdlib>
#include <ctime>
#include "SDL2/SDL.h"
#include "food.h"

Food::Food(SDL_Rect* snakeBlock, int c){
	newPosition(snakeBlock, c);
	foodBlock.w = 40;
	foodBlock.h = 40;
}

Food::~Food(){
	
}

void Food::draw(SDL_Renderer* renderer){
	
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);	
	SDL_RenderFillRect(renderer, &foodBlock);	
	
}

void Food::newPosition(SDL_Rect* snakeBlock, int c){
	
  	srand (time(NULL));
  	
  	bool same = false;
  	
  	int xIndex, yIndex;
  	
  	while(1){
  		
  		xIndex = rand() % 25;
		yIndex = rand() % 15;
		
		for(int i = 0; i < c; i++){
			if(xCoords[xIndex] == snakeBlock[i].x && yCoords[yIndex] == snakeBlock[i].y){
				same = true;
				break;
			}
			else{
				same = false;
			}
		}
		
		if(!same)
			break;
			
  	}
  	
	x = foodBlock.x = xCoords[xIndex];
	y = foodBlock.y = yCoords[yIndex]; 
	
}





#include "snake.h"
#include <iostream>
#include <cstdlib>
#include "SDL2/SDL.h"

Snake::Snake(int x, int y, int len, int direction){
	
	this->direction = direction;
	this->len = len;
	
	size = 20;
	
	snakeBlock = (SDL_Rect*)malloc(size*sizeof(*snakeBlock));
	
	for(int i = 0; i < len; i++){
		snakeBlock[i].x = x - i*45;
		snakeBlock[i].y = y;
		snakeBlock[i].w = 40;
		snakeBlock[i].h = 40;
	}
	
	leftEye.w = rightEye.w = 8;
	leftEye.h = rightEye.h = 8;
	
	setEyes();
	
}

Snake::~Snake(){
	free(snakeBlock);
}

void Snake::draw(SDL_Renderer* renderer){
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);	
	SDL_RenderFillRects(renderer, snakeBlock, len);
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &leftEye);
	SDL_RenderFillRect(renderer, &rightEye);
}

void Snake::move(){
	
	lastX = snakeBlock[len-1].x;
	lastY = snakeBlock[len-1].y;
	
	for(int i = len-1; i > 0; i--){
		snakeBlock[i].x = snakeBlock[i-1].x;
		snakeBlock[i].y = snakeBlock[i-1].y;
	}

	switch(direction){

		case 0:
			snakeBlock[0].y -= 45;
			break;
		case 1:
			snakeBlock[0].x += 45;
			break;
		case 2:
			snakeBlock[0].y += 45;
			break;
		case 3:
			snakeBlock[0].x -= 45;
			break;
	}
	
	setEyes();
	
	x = snakeBlock[0].x;
	y = snakeBlock[0].y;
	
}

void Snake::grow(){
	
	if(len == size){
		size *= 1.5;
		snakeBlock = (SDL_Rect*)realloc(snakeBlock, size*sizeof(*snakeBlock));
	}

	snakeBlock[len].x = lastX;
	snakeBlock[len].y = lastY;
	snakeBlock[len].w = 40;
	snakeBlock[len].h = 40;
	len++;
	std::cout << "LENGTH: " << len << std::endl;

}

void Snake::rotateLeft(){
	std::cout << "LEFT " << std::endl;
	direction--;
   if(direction == -1)
  		direction = 3;
}

void Snake::rotateRight(){
	std::cout << "RIGHT" << std::endl;
	direction++;
   if(direction == 4)
  		direction = 0;
}

void Snake::setEyes(){

	switch(direction){
		case 0:
			leftEye.x = snakeBlock[0].x + 8;
			leftEye.y = snakeBlock[0].y + 8;			
			rightEye.x = snakeBlock[0].x + 24;
			rightEye.y = snakeBlock[0].y + 8;
			break;
		case 1:
			leftEye.x = snakeBlock[0].x + 24;
			leftEye.y = snakeBlock[0].y + 8;
			rightEye.x = snakeBlock[0].x + 24;
			rightEye.y = snakeBlock[0].y + 24;
			break;
		case 2:
			leftEye.x = snakeBlock[0].x + 24;
			leftEye.y = snakeBlock[0].y + 24;
			rightEye.x = snakeBlock[0].x + 8;
			rightEye.y = snakeBlock[0].y + 24;
			break;
		case 3:
			leftEye.x = snakeBlock[0].x + 8;
			leftEye.y = snakeBlock[0].y + 24;
			rightEye.x = snakeBlock[0].x + 8;
			rightEye.y = snakeBlock[0].y + 8;
			break;
	}
	
}

bool Snake::checkSelfCollision(){
	for(int i = 1; i < len; i++){
		if(snakeBlock[0].x == snakeBlock[i].x &&
			snakeBlock[0].y == snakeBlock[i].y){
			return true;
		}
	}
	return false;
}
		
bool Snake::checkBorderCollision(){

	if(snakeBlock[0].x == 5 || snakeBlock[0].x == 1175 ||
		snakeBlock[0].y == 5 || snakeBlock[0].y == 725){
		return true;
	}
	else{
		return false;
	}
}

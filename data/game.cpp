#include "game.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "snake.h"
#include "food.h"

Game::Game(){
	
	state = 0;
	time = 0;
	speedModifier = 30;
	speed = 1;
	score = 0;
   isRunning = true;
 	window = NULL;
 	
 	snake = NULL;
 	food = NULL;
 	
 	init("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1220, 800, 0);
 	
 	titleTextRect.x = 444;
 	titleTextRect.y = 250;
 	underTitleTextRect.x = 423;
 	underTitleTextRect.y = 400;
 	authorTextRect.x = 1030;
 	authorTextRect.y = 763;
 	
 	scoreTextRect.x = 8;
 	scoreTextRect.y = 761;
 	speedTextRect.x = 1100;
 	speedTextRect.y = 761;
 	lengthTextRect.x = 550;
 	lengthTextRect.y = 761;
 	
 	gameOverRect.x = 300;
 	gameOverRect.y = 250;
 	gameOverScoreRect.x = 520;
 	gameOverScoreRect.y = 600;
 	underGameOverRect.x = 405;
 	underGameOverRect.y = 400;
 	
 	white.r = white.g = white.b = 255;
 	white.a = SDL_ALPHA_OPAQUE;
 	uiFont = TTF_OpenFont("data/coolvetica.ttf", 30);
 	titleFont = TTF_OpenFont("data/coolvetica.ttf", 120);
 	underTitleFont = TTF_OpenFont("data/coolvetica.ttf", 40);
 	authorFont = TTF_OpenFont("data/coolvetica.ttf", 24);
   
}

Game::~Game(){

	clean();
	
}


void Game::update(){
	
	unsigned int i = 0;
	unsigned int j = 0;
	
	while (1) {
		
		frameStart = SDL_GetTicks();
		
		////////////////////////////////////////////////
	
		handleEvents(&i, &j);
		
		if(!isRunning){
			return;
		}
		
		if(state == 1){
			if(snake->checkSelfCollision() || snake->checkBorderCollision()){
				SDL_Delay(500);
				state = 2;
			}
		}
		
		render(i);

   	////////////////////////////////////////////////

		i++;
		j++;
		
		if(i%60 == 0){
			time++;
		}
		
		
		if((j+1) % 1500 == 0 && speedModifier > 1 && state == 1){
			speedModifier /= 1.1;
			speed++;
			std::cout << "SPEED: " << speed << std::endl;
		}
		
   	frameTime = SDL_GetTicks() - frameStart;
   	
   	if(MAX_FRAME_TIME > frameTime)
   		SDL_Delay(MAX_FRAME_TIME - frameTime);
   	
	}

}

void Game::render(unsigned int frame){

	//clearing the rendering space
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	
	std::string tmpString;
	
	switch(state){
		case 0:
		
			//drawing the ui
			tmpString = "Snake";
			TTF_SizeText(titleFont, tmpString.c_str(), &titleTextRect.w, &titleTextRect.h);
			tmpSurface = TTF_RenderText_Blended(titleFont, tmpString.c_str(), white);
			tmpTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
			SDL_FreeSurface(tmpSurface);
			SDL_RenderCopy(renderer, tmpTexture, NULL, &titleTextRect);
			
			tmpString = "press space to start";
			TTF_SizeText(underTitleFont, tmpString.c_str(), &underTitleTextRect.w, &underTitleTextRect.h);
			tmpSurface = TTF_RenderText_Blended(underTitleFont, tmpString.c_str(), white);
			tmpTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
			SDL_FreeSurface(tmpSurface);
			SDL_RenderCopy(renderer, tmpTexture, NULL, &underTitleTextRect);
			
			tmpString = "Lukáš Litvan, 2018";
			TTF_SizeText(authorFont, "Lukas Litvan, 2018", &authorTextRect.w, &authorTextRect.h);
			tmpSurface = TTF_RenderUTF8_Blended(authorFont, tmpString.c_str(), white);
			tmpTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
			SDL_FreeSurface(tmpSurface);
			SDL_RenderCopy(renderer, tmpTexture, NULL, &authorTextRect);
			
			break;
		case 1:
		
			//drawing the food
			food->draw(renderer);
	
			//drawing the snake
			snake->draw(renderer);
	
			//drawing the ui
			tmpString = "Score: " + std::to_string(score);
			TTF_SizeText(uiFont, tmpString.c_str(), &scoreTextRect.w, &scoreTextRect.h);
			tmpSurface = TTF_RenderText_Blended(uiFont, tmpString.c_str(), white);
			tmpTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
			SDL_FreeSurface(tmpSurface);
			SDL_RenderCopy(renderer, tmpTexture, NULL, &scoreTextRect);
	
			tmpString = "Speed: " + std::to_string(speed);
			TTF_SizeText(uiFont, tmpString.c_str(), &speedTextRect.w, &speedTextRect.h);
			tmpSurface = TTF_RenderText_Blended(uiFont, tmpString.c_str(), white);
			tmpTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
			SDL_FreeSurface(tmpSurface);
			SDL_RenderCopy(renderer, tmpTexture, NULL, &speedTextRect);
	
			tmpString = "Length: " + std::to_string(snake->len);
			TTF_SizeText(uiFont, tmpString.c_str(), &lengthTextRect.w, &lengthTextRect.h);
			tmpSurface = TTF_RenderText_Blended(uiFont, tmpString.c_str(), white);
			tmpTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
			SDL_FreeSurface(tmpSurface);
			SDL_RenderCopy(renderer, tmpTexture, NULL, &lengthTextRect);
	
			//drawing the border
			SDL_SetRenderDrawColor(renderer, 150, 150, 150, SDL_ALPHA_OPAQUE);
			SDL_RenderFillRects(renderer, border, 84);
			
			break;
			
		case 2:
			
			//drawing the ui
			tmpString = "Game Over!";
			TTF_SizeText(titleFont, tmpString.c_str(), &gameOverRect.w, &gameOverRect.h);
			tmpSurface = TTF_RenderText_Blended(titleFont, tmpString.c_str(), white);
			tmpTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
			SDL_FreeSurface(tmpSurface);
			SDL_RenderCopy(renderer, tmpTexture, NULL, &gameOverRect);
			
			tmpString = "press space to restart";
			TTF_SizeText(underTitleFont, tmpString.c_str(), &underGameOverRect.w, &underGameOverRect.h);
			tmpSurface = TTF_RenderText_Blended(underTitleFont, tmpString.c_str(), white);
			tmpTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
			SDL_FreeSurface(tmpSurface);
			SDL_RenderCopy(renderer, tmpTexture, NULL, &underGameOverRect);
			
			tmpString = "Score: " + std::to_string(score);
			TTF_SizeText(underTitleFont, tmpString.c_str(), &gameOverScoreRect.w, &gameOverScoreRect.h);
			tmpSurface = TTF_RenderText_Blended(underTitleFont, tmpString.c_str(), white);
			tmpTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
			SDL_FreeSurface(tmpSurface);
			SDL_RenderCopy(renderer, tmpTexture, NULL, &gameOverScoreRect);
			
			
			break;
	}

	SDL_RenderPresent(renderer);
	
	if(state == 1){
		if((frame+1) % speedModifier == 0){
			snake->move();	
			if(snake->x == food->x && snake->y == food->y){
				food->newPosition(snake->snakeBlock, snake->len);
				snake->grow();
				score += (snake->len * speed);
				std::cout << "SCORE: " << score << std::endl;
			}
		}
	}

}

void Game::handleEvents(unsigned int* frame, unsigned int* framesFromStart){
	
	SDL_Event event;
	
			
		while(SDL_PollEvent(&event)){
			switch(event.type){
   			case SDL_QUIT:
   				isRunning = false;
   				return;
   			case SDL_KEYDOWN:
   				switch(event.key.keysym.sym){
   					case SDLK_ESCAPE:
   						isRunning = false;
   						return;
   						
   					case SDLK_SPACE:
   						if(state == 0){
   							state = 1;
   							if(snake != NULL){
   								delete snake;
   								snake = NULL;
   							}
   							if(food != NULL){
   								delete food;
   								food = NULL;
   							}	
   							snake = new Snake(590, 365, 4, 1);
 								food = new Food(snake->snakeBlock, snake->len);
 								score = 0;
 								speed = 1;
 								*frame = 0;
 								*framesFromStart = 0;
 							}
 							if(state == 2){
   							state = 1;
   							if(snake != NULL){
   								delete snake;
   								snake = NULL;
   							}
   							if(food != NULL){
   								delete food;
   								food = NULL;
   							}	
   							snake = new Snake(590, 365, 4, 1);
 								food = new Food(snake->snakeBlock, snake->len);
 								score = 0;
 								speed = 1;
 								*frame = 0;
 								*framesFromStart = 0;
 							}
 							
   						break;
   						
   					case SDLK_LEFT:
   						if(state == 1){
								snake->rotateLeft();
								snake->move();
								if(snake->x == food->x && snake->y == food->y){
									food->newPosition(snake->snakeBlock, snake->len);
									snake->grow();
									score += (snake->len * speed);
									std::cout << "SCORE: " << score << std::endl;
								}
							}
							*frame = 0;
   						break;
   					
   					case SDLK_RIGHT:
   						if(state == 1){
								snake->rotateRight();
								snake->move();
								if(snake->x == food->x && snake->y == food->y){
									food->newPosition(snake->snakeBlock, snake->len);
									snake->grow();
									score += (snake->len * speed);
									std::cout << "SCORE: " << score << std::endl;
								}
							}
							*frame = 0;
   						break;
   						
   					default:
   						break;
   					
   				}
   				break;
   			default:
   				break;
   		}	
		}
		
}

void Game::init(const char* title, int x, int y, int w, int h, Uint32 flags){
	
	window = SDL_CreateWindow(title, x, y, w, h, flags);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	createBorders(border);
	
}

void Game::createBorders(SDL_Rect* border){
	
	for(int i = 0; i < 84; i++){
		border[i].w = 40;
		border[i].h = 40;
	}
	for(int i = 0; i < 17; i++){
		border[i].x = 5;
		border[i].y = 5+(45*i);
	}
	for(int i = 17; i < 43; i++){
		border[i].x = 50+(45*(i-17));
		border[i].y = 725;
	}
	for(int i = 43; i < 59; i++){
		border[i].x = 1175;
		border[i].y = 680-(45*(i-43));
	}
	for(int i = 59; i < 84; i++){
		border[i].x = 1130-(45*(i-59));
		border[i].y = 5;
	}
	
}

void Game::clean(){
	
	if(food)
		delete food;
	if(snake)
		delete snake;
	TTF_CloseFont(uiFont);
	TTF_CloseFont(titleFont);
	TTF_CloseFont(underTitleFont);
	TTF_CloseFont(authorFont);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	
}


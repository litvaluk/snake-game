#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "data/game.h"

using namespace std;

int main (){
	
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
      exit(1);
   }
   
   if (TTF_Init() != 0){
		SDL_Log("Unable to initialize TTF: %s", TTF_GetError());
      exit(1);
   }
	
	Game* game = new Game();
	
	game->update();
	
	delete game;
	
	TTF_Quit();
	SDL_Quit();
			
	return 0;
}

#ifndef GAME_H_
#define GAME_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "snake.h"
#include "food.h"

class Game{
	public:
	
		Game();
		~Game();
		
		void update();
		
		int state;
		// 0 = start
		// 1 = game
		// 2 = restart
		
	private:
		
		const int TARGET_FPS = 60;
		const int MAX_FRAME_TIME = 1000 / TARGET_FPS;	
		Uint32 frameStart;
		int frameTime;
		
		int time;
		int speedModifier;
		int speed;
		int score;
		
		SDL_Window* window;
		SDL_Renderer* renderer;
		bool isRunning;
		int direction;
		
		SDL_Rect rect;
		SDL_Rect border[84];
		
		void init(const char* title, int x, int y, int w, int h, Uint32 flags);
		void clean();
		void handleEvents(unsigned int* frame, unsigned int* framesFromStart);
		void render(unsigned int frame);
		void createBorders(SDL_Rect* border);
		
		TTF_Font* uiFont;
		SDL_Color white;
		SDL_Surface* tmpSurface;
		SDL_Texture* tmpTexture;
		SDL_Rect scoreTextRect;
		SDL_Rect lengthTextRect;
		SDL_Rect speedTextRect;
		
		TTF_Font* titleFont;
		TTF_Font* underTitleFont;
		TTF_Font* authorFont;
		SDL_Rect titleTextRect;
		SDL_Rect underTitleTextRect;
		SDL_Rect authorTextRect;
		SDL_Rect gameOverRect;
		SDL_Rect gameOverScoreRect;
		SDL_Rect underGameOverRect;
		
		Snake* snake;
		Food* food;
		
};

#endif

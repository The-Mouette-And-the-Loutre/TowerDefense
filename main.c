#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "headers.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
Bool isRunning = TRUE;

const int SCREEN_WIDTH = 704, SCREEN_HEIGHT = 660;
int TILES_MAP = 400, TILES_CHOOSE = 10;

FPS fps = {60, 0, 0, 0, 0};

TileList tiles[400];
TileList tilesChoose[10];
EntityList entities[450];

int main(){
	srand(time(NULL));
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Tower Defense", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	if(window == NULL){
		printf("[ERREUR] La fenêtre ne peut pas être crée: %s\n", SDL_GetError());
		return 1;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(renderer == NULL){
		printf("[ERREUR] Le renderer n'a pas pu être créer\n");
		return 1;
	}
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	Start();
	SDL_RenderPresent(renderer);
	while(isRunning){
		fps.frameTime++;
		fps.currentTime = SDL_GetTicks();
		fps.deltaTime = fps.currentTime - fps.lastTime;
		Update();
		if(fps.currentTime > fps.lastTime + 1000){
			fps.lastTime = fps.currentTime;
		}
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
void Start(){
	int x = 0, y = 0, count_x = 0, count = 0;
	for(count_x = 0; count_x < TILES_MAP; count_x++){
		SDL_Rect collider = {x, y, 32, 32};
		Tile tile = {(Vector){collider.x, collider.y}, "ground", LoadTexture("textures/ground.bmp", renderer), (SDL_Rect){collider.x, collider.y, collider.w, collider.h}, collider, FALSE, FALSE, FALSE};
		tiles[count_x].tile = tile;
		if(count == (int)((SCREEN_WIDTH - 64) / 32 - 1)){
			y += 32;
			x = 0;
			count = 0;
		}else{
			x += 32;
			count++;
		}
	}
	tiles[133].tile.name = "place";
	entities[133].entity = (Entity){133, TRUE, tiles[133].tile.position, 0, 50, "tower", LoadTexture("textures/tower.bmp", renderer), (SDL_Rect){tiles[133].tile.position.x, tiles[133].tile.position.y, tiles[133].tile.collider.w, tiles[133].tile.collider.h}, 0, 0, 0, 1000, FALSE, 0, RIGHT};
	entities[400].entity = (Entity){400, TRUE, (Vector){0, 0}, 100, 0, "ennemy", LoadTexture("textures/sprite.bmp", renderer), (SDL_Rect){0, 0, 22.4, 33.6}, (Sprite){(SDL_Rect){0, 0, 32, 48}, 32, 0}, 0, 0, 0, FALSE, 0, RIGHT};
}
void Update(){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				isRunning = FALSE;
				break;
			case SDL_KEYDOWN:
				break;
			case SDL_MOUSEBUTTONUP:
				break;
		}
	}
	SDL_RenderClear(renderer);
	int x = 0;
	for(x = 0; x < 400; x++){
		SDL_RenderCopy(renderer, tiles[x].tile.texture, NULL, &tiles[x].tile.rect);
		if(tiles[x].tile.name == "place" && entities[x].entity.alive && entities[x].entity.name == "tower"){
			SDL_RenderCopy(renderer, entities[x].entity.texture, NULL, &entities[x].entity.collider);
		}
	}
	for(x = 400; x < 450; x++){
		if(entities[x].entity.alive){
			if(entities[x].entity.name == "ennemy"){
				int temp = entities[x].entity.sprite.spriteRect.x + 32;
				if(fps.fps / fps.frameTime == 5){
					fps.frameTime = 0;
					if(temp == 96){
						temp = 0;
					}
					entities[x].entity.sprite.spriteRect.x = temp;
				}
				SDL_RenderCopy(renderer, entities[x].entity.texture, &entities[x].entity.sprite.spriteRect, &entities[x].entity.collider);
			}
		}
	}
}
Bool InnerRect(float x, float y, SDL_Rect* rect){
	if(x >= rect->x && x < rect->x + rect->w && y >= rect->y && y < rect->y + rect->h){
		return TRUE;
	}else{
		return FALSE;
	}
}
Bool InnerRectCollider(SDL_Rect* a, SDL_Rect* b){
	if(a->x < b->x + b->w && a->x + a->w > b->x && a->y < b->y + b->h && a->y + a->h > b->y){
		return TRUE;
	}else{
		return FALSE;
	}
}
SDL_Texture *LoadTexture(char* file, SDL_Renderer *renderer){
	SDL_Texture *texture = NULL;
	SDL_Surface *surface = SDL_LoadBMP(file);
	if(surface == NULL){
		printf("[ERREUR] Le fichier %s ne peut pas être chargé\n", file);
	}else{
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if(texture == NULL)
			printf("[ERREUR] La texture ne peut pas être crée\n");
	}
	SDL_FreeSurface(surface);
	return texture;
}
Bool KeyPressed(SDL_Scancode code){
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if(state[code] == SDL_PRESSED){
		return 1;
	}
	return 0;
}
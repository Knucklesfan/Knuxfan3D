#include <SDL2/SDL.h>

class block {
    int height;
    SDL_Texture* texture;
    block(int heigh, SDL_Texture* txt) {height=heigh;texture=txt;}
};
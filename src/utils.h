#include <SDL2/SDL.h>
#include <vector>
#include <string>
#define TEXTUREWIDTH 512
#define TEXTUREHEIGHT 512
#define WIDTH 640
#define HEIGHT 480
#define MAPW 24
#define MAPH 24
#define SPRITECOUNT 1

namespace graphics {
    std::vector<SDL_Color> genTexture(std::string path);
    Uint32 getpixel(SDL_Surface *surface, int x, int y);
    std::vector<SDL_Color> genTexture(std::string path,int w, int h);

}
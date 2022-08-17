#include <SDL2/SDL.h>
#include <vector>
#include <string>
#define TEXTUREWIDTH 512
#define TEXTUREHEIGHT 512
#define WIDTH 640
#define HEIGHT 480
#define MAPW 24
#define MAPH 24
#define SPRITECOUNT 10

namespace graphics {
    std::vector<SDL_Color> genTexture(std::string path);
    Uint32 getpixel(SDL_Surface *surface, int x, int y);
    std::vector<SDL_Color> genTexture(std::string path,int w, int h);
    void drawTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, bool center, int srcx, int srcy, int srcw, int srch, int scalex, int scaley);
    double lerp(double a, double b, double t);

    SDL_Texture* getSDLTexture(std::string path, SDL_Renderer* renderer);
}
#include "utils.h"

std::vector<SDL_Color> graphics::genTexture(std::string path) {
    SDL_Surface* temp = SDL_LoadBMP(path.c_str());
    std::vector<SDL_Color> texture;
    texture.resize(TEXTUREWIDTH*TEXTUREHEIGHT);
    for(int x = 0; x < TEXTUREWIDTH; x++) {
        for(int y = 0; y < TEXTUREHEIGHT; y++) {
            Uint8 r=0,g=0,b = 0;
            SDL_GetRGB(getpixel(temp, x, y), temp->format, &r, &g, &b);
            SDL_Color c = {r,g,b};
            texture[(TEXTUREHEIGHT*y)+x] = c;
        }
    }
    SDL_FreeSurface(temp);
    return texture;
}
std::vector<SDL_Color> graphics::genTexture(std::string path,int w, int h) {
    SDL_Surface* temp = SDL_LoadBMP(path.c_str());
    std::vector<SDL_Color> texture;
    texture.resize(w*h);
    for(int x = 0; x < w; x++) {
        for(int y = 0; y < h; y++) {
            Uint8 r=0,g=0,b = 0;
            SDL_GetRGB(getpixel(temp, x, y), temp->format, &r, &g, &b);
            SDL_Color c = {r,g,b};
            texture[(h*y)+x] = c;
        }
    }
    SDL_FreeSurface(temp);
    return texture;
}

Uint32 graphics::getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

switch (bpp)
{
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            return p[0] << 16 | p[1] << 8 | p[2];
        }
        else {
            return p[0] | p[1] << 8 | p[2] << 16;
            break;
        }
        case 4:
            return *(Uint32 *)p;
            break;

        default:
            return 0;       /* shouldn't happen, but avoids warnings */
      }
}

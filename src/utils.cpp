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
SDL_Texture* graphics::getSDLTexture(std::string path, SDL_Renderer* renderer) {
        SDL_Surface* surf = SDL_LoadBMP(path.c_str());
        SDL_Texture* ret = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
        return ret;
}
void graphics::drawTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, bool center, int srcx, int srcy, int srcw, int srch, int scalex, int scaley) {
    SDL_Rect sprite;
    SDL_Rect srcrect = {srcx, srcy, srcw, srch};
    if(SDL_QueryTexture(texture, NULL, NULL, &sprite.w, &sprite.h) < 0) {
        printf("TEXTURE ISSUES!!! \n");
    };
    sprite.w = srcw;
    sprite.h = srch;
    if (center) {
        sprite.x = x - srcw / 2;
        sprite.y = y - srch / 2;
    }
    else {
        sprite.x = x;
        sprite.y = y;
    }
    SDL_RenderCopy(renderer, texture, &srcrect, &sprite);
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
double graphics::lerp(double a, double b, double t)    {
        if (t <= 0.5)
            return a+(b-a)*t;
        else
            return b-(b-a)*(1.0-t);
    }

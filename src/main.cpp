#include <iostream>
#include <SDL2/SDL.h>
#include <algorithm>
#include "player.h"
#include "utils.h"
#include "sprite.h"
#include "SDL_FontCache.h"
using namespace std;


int worldMap[MAPW][MAPH]= //TODO: actually make this load from a file. Should be ez
{
  {1,1,1,1,1,1,9,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,9,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,9,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,9,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,9,0,11,0,0,0,0,0,0,9,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,9,10,0,10,9,12,9,9,9,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
int floormap[MAPW][MAPH]= //TODO: actually make this load from a file. Should be ez
{
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
  };
int ceilingmap[MAPW][MAPH]= //TODO: actually make this load from a file. Should be ez
{
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {2,2,2,2,2,2,2,2,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {2,2,2,2,2,2,2,2,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {2,2,2,2,2,2,2,2,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {2,2,2,2,2,2,2,2,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {2,2,2,2,2,2,2,2,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {2,2,2,2,2,2,2,2,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {2,2,2,2,2,2,2,2,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {2,2,2,2,2,2,2,2,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {2,2,2,2,2,2,2,2,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
  };

std::vector<Sprite> sprite = {
	{8,8,ENEMY,5},
	{8,10,DECORATION,6},
	{0,0,UNDEFINED,0},
	{0,0,UNDEFINED,0},
	{0,0,UNDEFINED,0},
	{0,0,UNDEFINED,0},
	{0,0,UNDEFINED,0},
	{0,0,UNDEFINED,0},
	{0,0,UNDEFINED,0},
	{0,0,UNDEFINED,0}
};
double zbuf[WIDTH];
int spriteOrder[SPRITECOUNT];
double spriteDistance[SPRITECOUNT];
void sortSprites(int* order, double* dist, int amount);
double gunframe = 0;
bool fire = false;
Uint32 buffer[HEIGHT][WIDTH]; // y-coordinate first because it works per scanline

int main(int argc, char* argv[]) {
	int health = 100;
	double meth = 2.01;
	int ammo = 69;
	double planeX = 0;
    double planeY = 0.66;
	double time = 0; //time of current frame
	double oldTime = 0; //time of previous frame

	std::vector<SDL_Color> textures[24];

    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;

        return 1;
    }
	
    SDL_Window *window = SDL_CreateWindow("Breaking Castle Wolfenstein", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if(window == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;

        SDL_Quit();

        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == nullptr) {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;

        SDL_DestroyWindow(window);
        SDL_Quit();

        return 1;
    }
	SDL_Texture* hud = graphics::getSDLTexture("./textures/hud.bmp",renderer);
	SDL_Texture* gun = graphics::getSDLTexture("./textures/gun.bmp",renderer);

	textures[0] = graphics::genTexture("./textures/floor.bmp");
	textures[1] = graphics::genTexture("./textures/wall.bmp");
	textures[2] = graphics::genTexture("./textures/door.bmp");
	textures[3] = graphics::genTexture("./textures/warning.bmp");
	textures[4] = graphics::genTexture("./textures/weirdwall.bmp");
	textures[5] = graphics::genTexture("./textures/waltuh.bmp");
	textures[6] = graphics::genTexture("./textures/obama.bmp");
	textures[7] = graphics::genTexture("./textures/sadshinji.bmp");
	textures[8] = graphics::genTexture("./textures/polloswall.bmp");
	textures[9] = graphics::genTexture("./textures/pollosblankwall.bmp");
	textures[10] = graphics::genTexture("./textures/pollosdoor.bmp");
	textures[11] = graphics::genTexture("./textures/polloslogo.bmp");
	textures[12] = graphics::genTexture("./textures/floorbrighter.bmp");
	textures[13] = graphics::genTexture("./textures/waltuhcar.bmp");

    SDL_Texture* pixels = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBX8888, SDL_TEXTUREACCESS_STREAMING || SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT);
    SDL_Event event;
    bool quit = false;
	player p;
	FC_Font* font = FC_CreateFont();  
	FC_LoadFont(font, renderer, "fonts/FreeSans.ttf", 40, FC_MakeColor(255,0,0,255), TTF_STYLE_NORMAL);  

    while(!quit) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                quit = true;
            }
        }
		oldTime = time;
		time = SDL_GetTicks();
		double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
		//std::cout << (1.0 / frameTime) << "\n"; //FPS counter
		double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
		double rotSpeed = frameTime * 3.0; //the constant value is in radians/second

        SDL_RenderClear(renderer);
        // renderTextures
		void* data;
        int pitch;
        SDL_LockTexture(pixels, NULL, &data, &pitch);
        {
            // clear to black background
			SDL_memset(data, 0, pitch * HEIGHT);
			// for(int y = 0; y < HEIGHT; y++) { //floor code is here!!
			// 		double rayDirX0 = p.dirX - planeX;
			// 		double rayDirY0 = p.dirY - planeY;
			// 		double rayDirX1 = p.dirX + planeX;
			// 		double rayDirY1 = p.dirY + planeY;

			// 		int pos = y - HEIGHT / 2;

			// 		double posZ = 0.5*HEIGHT;

			// 		double rowDis = posZ/pos;

			// 		double floorStepX = rowDis * (rayDirX1 - rayDirX0) / WIDTH;
			// 		double floorStepY = rowDis * (rayDirY1 - rayDirY0) / WIDTH;

			// 		double floorX = p.x + rowDis * rayDirX0;
			// 		double floorY = p.y + rowDis * rayDirY0;

			// 		for(int x = 0; x < WIDTH; x++) {
			// 			int cellX = (int)(floorX);
			// 			int cellY = (int)(floorY);

			// 			int texNum = 1;

			// 			int tx = (int)(TEXTUREWIDTH * (floorX - cellX)) & (TEXTUREWIDTH - 1);
			// 			int ty = (int)(TEXTUREHEIGHT * (floorY - cellY)) & (TEXTUREHEIGHT - 1);

			// 			floorX += floorStepX;
			// 			floorY += floorStepY;

			// 			int r = textures[texNum][TEXTUREHEIGHT*ty+tx].r;
			// 			int g = textures[texNum][TEXTUREHEIGHT*ty+tx].g;
			// 			int b = textures[texNum][TEXTUREHEIGHT*ty+tx].b;

			// 			unsigned int* row = (unsigned int*)((char*)data + pitch * y);
			// 			row[x] = 0x00000000; // 0xRRGGBBAA
			// 			row[x] += r << 0x18; //
			// 			row[x] += g << 0x10; //
			// 			row[x] += b << 0x8;  //


			// 		}

			// 	}

			for(int x = 0; x < WIDTH; x++) {
				double camX = 2*x/double(WIDTH)-1; //the X coordinate on the camera plane.

				double raydirX = p.dirX + planeX * camX; //simple direction calculation to point the ray at the point.
				double raydirY = p.dirY + planeY * camX; //

				//pos of the player in terms of the map itself
				int mapX = int(p.x);
				int mapY = int(p.y);

				//handles the distance from the sides from the current position
				double sideDistX;
				double sideDistY;


				//length of ray from one x or y side to the next.
				double deltaDistX = (raydirX == 0 )?1e30: std::abs(1/raydirX);
				double deltaDistY = (raydirY == 0 )?1e30: std::abs(1/raydirY);
				double perpWallDist;

				int stepX = 0; //+1 for right, -1 for left.
				int stepY = 0; //+1 for down, -1 for up.

				int hit = 0; //equals the texture number if hit
				int side; // hit X wall side or Y wall side

				if (raydirX < 0) {
					stepX = -1;
					sideDistX = (p.x - mapX) * deltaDistX;
				}
				else {
					stepX = 1;
					sideDistX = (mapX + 1.0 - p.x) * deltaDistX;
				}
				if (raydirY < 0) {
					stepY = -1;
					sideDistY = (p.y - mapY) * deltaDistY;
				}
				else {
					stepY = 1;
					sideDistY = (mapY + 1.0 - p.y) * deltaDistY;
				}
				while(hit == 0) {
					if(sideDistX < sideDistY) {
						sideDistX+=deltaDistX;
						mapX+=stepX;
						side = 0;
					}
					else {
						sideDistY+=deltaDistY;
						mapY+=stepY;
						side = 1;

					}
					if(worldMap[mapX][mapY]) {
						hit = 1;
					}
					if(fire) {
						for(int i = 0; i < SPRITECOUNT; i++) {
							if((int)sprite[i].x == (int)mapX 
							&& (int)sprite[i].y == (int)mapY 
							&& x == (WIDTH/2)
							&& abs((int)sprite[i].x-p.x)<=10
							&& abs((int)sprite[i].y-p.y)<=10
							&& sprite[i].type == ENEMY
							) {
								sprite[i].hit();
							}
						}
					}



				}
				int texNum = worldMap[mapX][mapY] - 1;
				if(side == 0) {
					perpWallDist = (sideDistX - deltaDistX);
				} 	
				else{
					perpWallDist = (sideDistY - deltaDistY);
				}
				int lineHeight = (int)(HEIGHT / perpWallDist);
				int drawStart = -lineHeight / 2 + HEIGHT / 2;
				if(drawStart < 0)drawStart = 0;
				int drawEnd = lineHeight / 2 + HEIGHT / 2;
				if(drawEnd >= HEIGHT)drawEnd = HEIGHT - 1;



				//start of new texture code
				double wallx;
				if(side == 0) {
					wallx = p.y+perpWallDist*raydirY;
				}
				else {
					wallx = p.x+perpWallDist*raydirX;
				}
				wallx -= std::floor(wallx);

				int tX = int(wallx * double(TEXTUREWIDTH));
				if(side ==0 && raydirX > 0) {
					tX = TEXTUREWIDTH-tX-1;
				}
				if(side == 1 && raydirY < 0) {
					tX = TEXTUREWIDTH-tX-1;
				}

				double step = 1.0*TEXTUREHEIGHT/lineHeight;
				double tPos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;
				for(int y = drawStart; y < drawEnd; y++) {
					int tY = (int)tPos & (TEXTUREHEIGHT-1);
					tPos += step;
					int r = textures[texNum][TEXTUREHEIGHT*tY+tX].r;
					int g = textures[texNum][TEXTUREHEIGHT*tY+tX].g;
					int b = textures[texNum][TEXTUREHEIGHT*tY+tX].b;
					if(side == 1) {
						r/=2;
						g/=2;
						b/=2;
					}
					//SDL_SetRenderDrawColor(renderer,r,g,b,255);
					unsigned int* row = (unsigned int*)((char*)data + pitch * y);
                	row[x] = 0x00000000; // 0xRRGGBBAA
					row[x] += r << 0x18; //imagine explaining hex to a CS guy who knows literally nothing about hex lmao
					row[x] += g << 0x10; //"oh yeah dude, so 10 is greater than 8 by eight."
					row[x] += b << 0x8;  //"no, it's always been 10-8=8, what the hell kind of school did YOU go to?"
					//SDL_RenderDrawPoint(renderer,x,y);
				}
				      //FLOOR CASTING (vertical version, directly after drawing the vertical wall stripe for the current x)
				double floorXWall, floorYWall; //x, y position of the floor texel at the bottom of the wall

				//4 different wall directions possible
				if(side == 0 && raydirX > 0)
				{
					floorXWall = mapX;
					floorYWall = mapY + wallx;
				}
				else if(side == 0 && raydirX < 0)
				{
					floorXWall = mapX + 1.0;
					floorYWall = mapY + wallx;
				}
				else if(side == 1 && raydirY > 0)
				{
					floorXWall = mapX + wallx;
					floorYWall = mapY;
				}
				else
				{
					floorXWall = mapX + wallx;
					floorYWall = mapY + 1.0;
				}

				double distWall, distPlayer, currentDist;

				distWall = perpWallDist;
				distPlayer = 0.0;

				if (drawEnd < 0) drawEnd = HEIGHT; //becomes < 0 when the integer overflows

				//draw the floor from drawEnd to the bottom of the screen
				for(int y = drawEnd + 1; y < HEIGHT; y++)
				{
					currentDist = HEIGHT / (2.0 * y - HEIGHT); //you could make a small lookup table for this instead

					double weight = (currentDist - distPlayer) / (distWall - distPlayer);

					double currentFloorX = weight * floorXWall + (1.0 - weight) * p.x;
					double currentFloorY = weight * floorYWall + (1.0 - weight) * p.y;

					int floorTexX, floorTexY;
					floorTexX = int(currentFloorX * TEXTUREWIDTH) % TEXTUREWIDTH;
					floorTexY = int(currentFloorY * TEXTUREHEIGHT) % TEXTUREHEIGHT;

					int checkerBoardPattern = (int(currentFloorX) + int(currentFloorY)) % 2;
					int floorTexture = floormap[int(currentFloorX)][int(currentFloorY)];

					//floor
					Uint8 r,g,b;
					r = textures[floorTexture][TEXTUREHEIGHT*floorTexY+floorTexX].r;
					g = textures[floorTexture][TEXTUREHEIGHT*floorTexY+floorTexX].g;
					b = textures[floorTexture][TEXTUREHEIGHT*floorTexY+floorTexX].b;


					unsigned int* row = (unsigned int*)((char*)data + pitch * y);
					row[x] = 0x00000000; // 0xRRGGBBAA
					row[x] += r << 0x18; //
					row[x] += g << 0x10; //
					row[x] += b << 0x8;  //

					floorTexture = ceilingmap[int(currentFloorX)][int(currentFloorY)];
					if(floorTexture > -1) {
						r = textures[floorTexture][TEXTUREHEIGHT*floorTexY+floorTexX].r;
						g = textures[floorTexture][TEXTUREHEIGHT*floorTexY+floorTexX].g;
						b = textures[floorTexture][TEXTUREHEIGHT*floorTexY+floorTexX].b;


						unsigned int* rw = (unsigned int*)((char*)data + pitch * (HEIGHT-y));
						rw[x] = 0x00000000; // 0xRRGGBBAA
						rw[x] += r << 0x18; //
						rw[x] += g << 0x10; //
						rw[x] += b << 0x8;  //
					}

					//ceiling (symmetrical!)
					//buffer[h - y][x] = texture[6][texWidth * floorTexY + floorTexX];
				}
				zbuf[x] = perpWallDist; //perpendicular distance is used

				//old nasty textureless code be like:
				// int r;
				// int g;
				// int b;
				// switch(worldMap[mapX][mapY]) {
				// 	case 1:  r=255;g=0;b=0;  break; //red
				// 	case 2:  r=0;g=255;b=0;  break; //green
				// 	case 3:  r=0;g=0;b=255;   break; //blue
				// 	case 4:  r=255;g=255;b=255;  break; //white
				// 	default: r=255;g=255;b=0; break; //yellow

				// }
				// if(side == 1) {
				// 	r/=2;
				// 	g/=2;
				// 	b/=2;
				// }

			}

            // draw red diagonal line
        }
		for(int i = 0; i < sprite.size(); i++) {
			
			spriteOrder[i] = i;
			spriteDistance[i] = ((p.x - sprite[i].x) * (p.x - sprite[i].x) + (p.y - sprite[i].y) * (p.y - sprite[i].y));

		}
		sortSprites(spriteOrder,spriteDistance,sprite.size());
		for(int i = 0; i < sprite.size(); i++) { //SPRITE DRAWING
			sprite[spriteOrder[i]].logic(frameTime,p);
			if(sprite[spriteOrder[i]].texture > -1) {
				double spriteX = sprite[spriteOrder[i]].x - p.x;
				double spriteY = sprite[spriteOrder[i]].y - p.y;
				double invDet = 1.0 / (planeX * p.dirY - p.dirX * planeY); //required for correct matrix multiplication

				double transformX = invDet * (p.dirY * spriteX - p.dirX * spriteY);
				double transformY = invDet * (-planeY * spriteX + planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

				int spriteScreenX = int((WIDTH / 2) * (1 + transformX / transformY));

				//calculate height of the sprite on screen
				int spriteHeight = abs(int(HEIGHT / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
				//calculate lowest and highest pixel to fill in current stripe
				int drawStartY = -spriteHeight / 2 + HEIGHT / 2;
				if(drawStartY < 0) drawStartY = 0;
				int drawEndY = spriteHeight / 2 + HEIGHT / 2;
				if(drawEndY >= HEIGHT) drawEndY = HEIGHT - 1;

				//calculate width of the sprite
				int spriteWidth = abs( int (HEIGHT / (transformY)));
				int drawStartX = -spriteWidth / 2 + spriteScreenX;
				if(drawStartX < 0) drawStartX = 0;
				int drawEndX = spriteWidth / 2 + spriteScreenX;
				if(drawEndX >= WIDTH) drawEndX = WIDTH - 1;

				//loop through every vertical stripe of the sprite on screen
				for(int stripe = drawStartX; stripe < drawEndX; stripe++)
				{
					int texX = int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * TEXTUREWIDTH / spriteWidth) / 256;
					//the conditions in the if are:
					//1) it's in front of camera plane so you don't see things behind you
					//2) it's on the screen (left)
					//3) it's on the screen (right)
					//4) ZBuffer, with perpendicular distance
					if(transformY > 0 && stripe > 0 && stripe < WIDTH && transformY < zbuf[stripe])
					for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
					{
					int d = (y) * 256 - HEIGHT * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
					int texY = ((d * TEXTUREHEIGHT) / spriteHeight) / 256;

					Uint8 r=0,g=0,b=0;
					r = textures[sprite[spriteOrder[i]].texture][(TEXTUREHEIGHT*((TEXTUREHEIGHT - 1) - texY)+texX)].r;
					g = textures[sprite[spriteOrder[i]].texture][(TEXTUREHEIGHT*((TEXTUREHEIGHT - 1) - texY)+texX)].g;
					b = textures[sprite[spriteOrder[i]].texture][(TEXTUREHEIGHT*((TEXTUREHEIGHT - 1) - texY)+texX)].b;

					if(r != 0xff && g != 0 && b != 0xff) {
						unsigned int* rw = (unsigned int*)((char*)data + pitch * (HEIGHT-y));
						rw[stripe] = 0x00000000; // 0xRRGGBBAA
						rw[stripe] += r << 0x18; //
						rw[stripe] += g << 0x10; //
						rw[stripe] += b << 0x8;  //
					}


					//Uint32 color = texture[sprite[spriteOrder[i]].texture][TEXTUREWIDTH * texY + texX]; //get current color from the texture
					//if((color & 0x00FFFFFF) != 0) buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
					}
									
				}
			}

		}
        SDL_UnlockTexture(pixels);
        SDL_RenderCopy(renderer, pixels, NULL, NULL);

		graphics::drawTexture(renderer,gun,96,32,false,std::round(gunframe)*448,0,448,448,1,1);
        
		SDL_RenderCopy(renderer, hud, NULL, NULL);
		FC_Draw(font,renderer,46,424,std::to_string(health).c_str());
		FC_Draw(font,renderer,560,424,std::to_string(ammo).c_str());
		if(gunframe != 0 || fire) {
			gunframe += frameTime*20.0;
			fire = false;
		}
		if(gunframe >= 4) {
			gunframe = 0;
		}

		const Uint8* state = SDL_GetKeyboardState(nullptr);
		if(state[SDL_SCANCODE_UP]) {
			if(worldMap[int(p.x + p.dirX * moveSpeed)][int(p.y)] == 0) {
				p.x+=p.dirX*moveSpeed;
			}
			if(worldMap[int(p.x)][int(p.y+p.dirY*moveSpeed)] == 0) {
				p.y += p.dirY*moveSpeed;
			}
		}
		if(state[SDL_SCANCODE_DOWN]) {
			if(worldMap[int(p.x - p.dirX * moveSpeed)][int(p.y)] == 0) {
				p.x-=p.dirX*moveSpeed;
			}
			if(worldMap[int(p.x)][int(p.y-p.dirY*moveSpeed)] == 0) {
				p.y -= p.dirY*moveSpeed;
			}
		}
		if(state[SDL_SCANCODE_LCTRL]) {
			if(!fire && gunframe == 0) {
				gunframe = 0;
				fire = true;
				for(int i = 0; i < sprite.size(); i++) {
					if((int)p.x == (int)sprite[i].x && (int)p.y == (int)sprite[i].y	&& sprite[i].type == ENEMY) {
						sprite[i].hit();
					}
				}
			}
		}
		if(state[SDL_SCANCODE_RIGHT]) {
			double oldDirX = p.dirX;
			p.dirX = p.dirX*std::cos(-rotSpeed) - p.dirY*sin(-rotSpeed);
			p.dirY = oldDirX*std::sin(-rotSpeed) + p.dirY*cos(-rotSpeed);
			double oldPlaneX = planeX;
			planeX = planeX*std::cos(-rotSpeed) - planeY*sin(-rotSpeed);
			planeY = oldPlaneX*std::sin(-rotSpeed) + planeY*cos(-rotSpeed);
		}
		if(state[SDL_SCANCODE_LEFT]) {
			double oldDirX = p.dirX;
			p.dirX = p.dirX*std::cos(rotSpeed) - p.dirY*sin(rotSpeed);
			p.dirY = oldDirX*std::sin(rotSpeed) + p.dirY*cos(rotSpeed);
			double oldPlaneX = planeX;
			planeX = planeX*std::cos(rotSpeed) - planeY*sin(rotSpeed);
			planeY = oldPlaneX*std::sin(rotSpeed) + planeY*cos(rotSpeed);
		}

        SDL_RenderPresent(renderer);
    }

    return 0;
}
//sort algorithm
//sort the sprites based on distance
void sortSprites(int* order, double* dist, int amount)
{
  std::vector<std::pair<double, int>> sprites(amount);
  for(int i = 0; i < amount; i++) {
    sprites[i].first = dist[i];
    sprites[i].second = order[i];
  }
  std::sort(sprites.begin(), sprites.end());
  // restore in reverse order to go from farthest to nearest
  for(int i = 0; i < amount; i++) {
    dist[i] = sprites[amount - i - 1].first;
    order[i] = sprites[amount - i - 1].second;
  }
}


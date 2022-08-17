OBJS	= main.o utils.o SDL_FontCache.o sprite.o
SOURCE	= src/main.cpp src/utils.cpp src/SDL_FontCache.c src/sprite.cpp
HEADER	= 
OUT	= raycast
CC	 = g++
FLAGS	 = -g -c -Wall -Iinclude/
LFLAGS	 = -lSDL2 -lSDL2_ttf -lSDL2_mixer -fsanitize=address

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: src/main.cpp
	$(CC) $(FLAGS) src/main.cpp 
utils.o: src/utils.cpp
	$(CC) $(FLAGS) src/utils.cpp 
SDL_FontCache.o: src/SDL_FontCache.c
	$(CC) $(FLAGS) src/SDL_FontCache.c 
sprite.o: src/sprite.cpp
	$(CC) $(FLAGS) src/sprite.cpp 

clean:
	rm -f $(OBJS) $(OUT)

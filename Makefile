OBJS	= main.o utils.o
SOURCE	= src/main.cpp src/utils.cpp
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

clean:
	rm -f $(OBJS) $(OUT)
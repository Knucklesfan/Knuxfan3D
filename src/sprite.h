#include "player.h"
enum TYPE {
  ENEMY,DECORATION,UNDEFINED,EXPLOSION
};

class Sprite
{
  public:
    double x;
    double y;
    int type;
    int texture;
    double health = 10;
    bool active = true;
    bool targeted = false;
    void logic(double frameTime, player p);
    int hit();
};


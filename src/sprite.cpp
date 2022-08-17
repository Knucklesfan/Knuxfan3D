#include "sprite.h"
#include <cmath>
#include "utils.h"
void Sprite::logic(double frameTime, player p) {
    switch(type) {
        case ENEMY: {
            if(targeted && active) {
                x = graphics::lerp(x,p.x,frameTime);
                y = graphics::lerp(y,p.y,frameTime);
            }
        }
        case EXPLOSION: {
            
        }
        default: { //not really necessary, but im doing this to avoid errors.
            break;
        }
    }
}
int Sprite::hit() {
    if(targeted) {
        active= false;
    }
    else {
        targeted = true;
    }
    if(!active) {
        return 2;
    }
    return 0;
}

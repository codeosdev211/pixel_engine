#ifndef Collision_hpp
#define Collision_hpp

#include "SDL2/SDL.h"

class Collision {

public:
    static bool aa_bb(const SDL_Rect& rect_a, const SDL_Rect& rect_b);
};
 
#endif
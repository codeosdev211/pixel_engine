#ifndef Collision_hpp
#define Collision_hpp

#include "SDL2/SDL.h"

class ColliderComponent;

class Collision {

public:
    static bool aa_bb(const SDL_Rect& rect_a, const SDL_Rect& rect_b);
    static bool aa_bb(const ColliderComponent& collider_a, const ColliderComponent& collider_b);
};
 
#endif
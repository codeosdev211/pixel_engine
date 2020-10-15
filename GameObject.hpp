#ifndef GameObject_hpp
#define GameObject_hpp

#include "Game.hpp"

class GameObject {

public:
    GameObject(const char* texture_sheet, int x, int y);
    ~GameObject();

    void update();
    void render();

private:
    int x_pos, y_pos;
    SDL_Texture* object_texture;
    SDL_Rect src_rect, dest_rect; 

};


#endif
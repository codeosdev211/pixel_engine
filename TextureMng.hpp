#ifndef TextureMng_hpp
#define TextureMng_hpp

#include "Game.hpp"

class TextureMng {

public:
    static SDL_Texture* load_texture(const char* file_name);
    static void draw_tile(SDL_Texture* tile_texture, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
};
 
#endif

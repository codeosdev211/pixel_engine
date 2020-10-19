#ifndef TileComponent_hpp
#define TileComponent_hpp

#include "ECS.hpp"
#include "SDL2/SDL.h"

class TileComponent: public Component {

public:
    
    SDL_Texture* texture;
    SDL_Rect src_rect, dest_rect;

    TileComponent() = default;

    ~TileComponent() {
        SDL_DestroyTexture(texture);
    }

    TileComponent(int text_x, int text_y, int text_pos_x, int text_pos_y, const char* path) {
        texture = TextureMng::load_texture(path);

        src_rect.x = text_x;
        src_rect.y = text_y;
        src_rect.w = src_rect.h = 32;

        dest_rect.x = text_pos_x;
        dest_rect.y = text_pos_y;
        dest_rect.w = dest_rect.h = 32;
    }

    void draw() override {
        TextureMng::draw(texture, src_rect, dest_rect, SDL_FLIP_NONE);
    };
};

#endif

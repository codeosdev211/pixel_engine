#ifndef SpriteComponent_hpp
#define SpriteComponent_hpp

#include "Components.hpp"
#include "SDL2/SDL.h"

class SpriteComponent: public Component {

private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect src_rect, dest_rect;

public:
    SpriteComponent() = default;
    SpriteComponent(const char* path) {
        set_texture(path);
    }

    void set_texture(const char* path) {
        texture = TextureMng::load_texture(path);
    }

    void init() override {

        transform = &entity->get_component<TransformComponent>();

        src_rect.x = src_rect.y = 0;
        src_rect.w = src_rect.h = 32;
        dest_rect.w = dest_rect.h = 64;
    }

    void update() override {
        dest_rect.x = (int) transform->position.x;
        dest_rect.y = (int) transform->position.y;
 
    }

    void draw() override {
        TextureMng::draw_tile(texture, src_rect, dest_rect);
    }


};

#endif

#ifndef SpriteComponent_hpp
#define SpriteComponent_hpp

#include "Components.hpp"
#include "SDL2/SDL.h"
#include "../TextureMng.hpp"

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

    ~SpriteComponent() {
        SDL_DestroyTexture(texture);
    }

    void init() override {

        transform = &entity->get_component<TransformComponent>();

        src_rect.x = src_rect.y = 0;
        src_rect.w = transform->width;
        src_rect.h = transform->height;
    }

    void update() override {
        dest_rect.x = static_cast<int>(transform->position.x);
        dest_rect.y = static_cast<int>(transform->position.y);
        dest_rect.w = transform->width * transform->scale;
        dest_rect.h = transform->height * transform->scale;
 
    }

    void draw() override {
        TextureMng::draw_tile(texture, src_rect, dest_rect);
    }


};

#endif

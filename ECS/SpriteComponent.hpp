#ifndef SpriteComponent_hpp
#define SpriteComponent_hpp

#include "Components.hpp"
#include "SDL2/SDL.h"
#include "../TextureMng.hpp"
#include "Animation.hpp"
#include <map>

class SpriteComponent: public Component {

private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect src_rect, dest_rect;

    bool animated = false;
    int frames = 0;
    int speed = 100;

public:
    
    int anim_index = 0;

    std::map<const char*, Animation> animations;

    SDL_RendererFlip sprite_flip = SDL_FLIP_NONE;

    SpriteComponent() = default;
    SpriteComponent(const char* path) {
        set_texture(path);
    }

    SpriteComponent(const char* path, bool is_animated) {
        animated = true;

        Animation idle = Animation(0, 3, 100);
        Animation walk = Animation(1, 8, 100);

        animations.emplace("Idle", idle);
        animations.emplace("Walk", walk);
        
        play("Idle");
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
        if(animated) {
            src_rect.x = src_rect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
        }
        src_rect.y = anim_index * transform->height;

        dest_rect.x = static_cast<int>(transform->position.x);
        dest_rect.y = static_cast<int>(transform->position.y);
        dest_rect.w = transform->width * transform->scale;
        dest_rect.h = transform->height * transform->scale;
 
    }

    void draw() override {
        TextureMng::draw_tile(texture, src_rect, dest_rect, sprite_flip);
    }

    void play(const char* anim_name) {
        frames = animations[anim_name].frames;
        anim_index = animations[anim_name].index;
        speed = animations[anim_name].speed;
    }

};

#endif

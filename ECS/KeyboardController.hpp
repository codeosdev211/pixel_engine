#ifndef KeyboardController_hpp
#define KeyboardController_hpp

#include "../Game.hpp"
#include "ECS.hpp"
#include "Components.hpp"

class KeyboardController: public Component {

public:
    TransformComponent *transform;
    SpriteComponent *sprite;

    void init() override {
        transform = &entity->get_component<TransformComponent>();
        sprite = &entity->get_component<SpriteComponent>();
    }

    void update() override {
        if(Game::event.type == SDL_KEYDOWN) {
            switch(Game::event.key.keysym.sym) {
                case SDLK_w:
                    transform->velocity.y = -1;
                    sprite->play("Walk");
                    break;
                case SDLK_a:
                    transform->velocity.x = -1;
                    sprite->play("Walk");
                    sprite->sprite_flip = SDL_FLIP_HORIZONTAL;
                    break;
                case SDLK_d:
                    transform->velocity.x = 1;
                    sprite->play("Walk");
                    break;
                case SDLK_s:
                    transform->velocity.y = 1;
                    sprite->play("Walk");
                    break;
                default:
                    break;
            }  
        }

        if(Game::event.type == SDL_KEYUP) {
            switch(Game::event.key.keysym.sym) {
                case SDLK_w:
                    transform->velocity.y = 0;
                    sprite->play("Idle");
                    break;
                case SDLK_a:
                    transform->velocity.x = 0;
                    sprite->play("Idle");
                    sprite->sprite_flip = SDL_FLIP_NONE;
                    break;
                case SDLK_d:
                    transform->velocity.x = 0;
                    sprite->play("Idle");
                    break;
                case SDLK_s:
                    transform->velocity.y = 0;
                    sprite->play("Idle");
                    break;
                default:
                    break;
            }
        }
    }

};


#endif

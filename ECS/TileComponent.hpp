#ifndef TileComponent_hpp
#define TileComponent_hpp

#include "ECS.hpp"
#include "TransformComponent.hpp"
#include "SDL2/SDL.h"

class TileComponent: public Component {

public:
    TransformComponent *transform;
    SpriteComponent *sprite;
    char* path;

    SDL_Rect tile_rect;
    int tile_id;

    TileComponent() = default;

    TileComponent(int x, int y, int w, int h, int id) {
        tile_rect.x = x;
        tile_rect.y = y;
        tile_rect.w = w;
        tile_rect.h = h;
        tile_id = id;

        switch(tile_id) {
            case 0:
                path = "assets/dirt.png"; break;
            case 1:
                path = "assets/grass.png"; break;
            case 2:
                path = "assets/sky.png"; break;
            default: 
                break;
        }

    }

    void init() override { 
        entity->add_component<TransformComponent>((float) tile_rect.x, (float) tile_rect.y, tile_rect.w, tile_rect.h, 1);
        transform = &entity->get_component<TransformComponent>();

        entity->add_component<SpriteComponent>(path);
        sprite = &entity->get_component<SpriteComponent>();
    }
        

};

#endif
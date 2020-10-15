#include "GameObject.hpp"
#include "TextureMng.hpp"

GameObject::GameObject(const char* texture_sheet, int x, int y) {
    object_texture = TextureMng::load_texture(texture_sheet);
    x_pos = x;
    y_pos = y;
}

void GameObject::update() {

    x_pos++;
    y_pos++;

    src_rect.h = 32;
    src_rect.w = 32;
    src_rect.x = 0;
    src_rect.y = 0;

    dest_rect.w = src_rect.w * 2;
    dest_rect.h = src_rect.h * 2;
    dest_rect.x = x_pos;
    dest_rect.y = y_pos;
    
 
}

void GameObject::render() {
    SDL_RenderCopy(Game::renderer, object_texture, &src_rect, &dest_rect);
}


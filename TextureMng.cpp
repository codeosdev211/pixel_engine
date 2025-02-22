#include "TextureMng.hpp"

SDL_Texture* TextureMng::load_texture(const char* file_name) {

    SDL_Surface *temp_surface = IMG_Load(file_name);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, temp_surface);
    SDL_FreeSurface(temp_surface);

    return texture;
}

void TextureMng::draw(SDL_Texture *tile_texture, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(Game::renderer, tile_texture, &src, &dest, NULL, NULL, flip);
}

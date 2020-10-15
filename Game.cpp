#include "Game.hpp"
#include "TextureMng.hpp" 
#include "Map.hpp" 
#include "ECS/Components.hpp"
#include "Vector2D.hpp"

using namespace std; 
 
Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Manager manager;
auto& new_player(manager.add_entity());


Game::Game() {
}

Game::~Game() {
}

void Game::init(const char *title, int x_pos, int y_pos, int width, int height, bool full_screen) {
    int flags = 0;
    if(full_screen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        cout << "Subsystems initialized..." << endl;
        window = SDL_CreateWindow(title, x_pos, y_pos, width, height,  flags);

        if(window) {
            cout << "Window Created..." << endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);
            cout << "Renderer Created" << endl;
        }

        is_running = true;
    } 
 
    map = new Map();

    new_player.add_component<TransformComponent>();
    new_player.add_component<SpriteComponent>("assets/darkshin.png");
    new_player.add_component<KeyboardController>();

}

void Game::handle_events() {
    
    SDL_PollEvent(&event);
    switch(event.type) {
        case SDL_QUIT:
            is_running = false;
            break;
        default:
            break;
    }
 
}


void Game::update() { 
    manager.refresh();
    manager.update();   
}

void Game::render() {
    SDL_RenderClear(renderer);
    // this is where we would add stuff (background first images on it)
    map->draw_map(); 
    manager.draw();
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "Game Cleaned" << endl;
}



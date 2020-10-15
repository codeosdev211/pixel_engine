#include "Game.hpp"
#include "TextureMng.hpp" 
#include "Map.hpp" 
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"

using namespace std; 
 
Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Manager manager;
auto& new_player(manager.add_entity());
auto& wall(manager.add_entity());

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

    new_player.add_component<TransformComponent>(2);
    new_player.add_component<SpriteComponent>("assets/darkshin.png");
    new_player.add_component<KeyboardController>();
    new_player.add_component<ColliderComponent>("player");

    wall.add_component<TransformComponent>(300.0f, 300.f, 20, 300, 1);
    wall.add_component<SpriteComponent>("assets/dirt.png");
    wall.add_component<ColliderComponent>("wall");

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

    if(Collision::aa_bb(new_player.get_component<ColliderComponent>().collider,
        wall.get_component<ColliderComponent>().collider)) {
            
        // new_player.get_component<TransformComponent>().scale = 1;
        new_player.get_component<TransformComponent>().velocity * -1;
        cout << "wall Hit " << endl;
    } else {
        // new_player.get_component<TransformComponent>().scale = 2;
        cout << "wall missed " << endl;
    }

    

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



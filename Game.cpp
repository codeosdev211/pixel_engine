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

std::vector<ColliderComponent*> Game::colliders;

Manager manager;
auto& new_player(manager.add_entity());
auto& wall(manager.add_entity());

const char* map_file = "assets/text_temp.png";

 
enum group_labels: std::size_t {
    group_map,
    group_players,
    group_enemies,
    group_colliders
};

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
 
    //map = new Map();
    Map::load_map("assets/map1.txt", 25, 20);
    new_player.add_component<TransformComponent>(2);
    new_player.add_component<SpriteComponent>("assets/mario_anim.png", true);
    new_player.add_component<KeyboardController>();
    new_player.add_component<ColliderComponent>("player");
    new_player.add_group(group_players);


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

    for (auto collider: colliders) {
        Collision::aa_bb(new_player.get_component<ColliderComponent>(), *collider);
    }
 
}

auto& tiles(manager.get_group(group_map));
auto& players(manager.get_group(group_players));
auto& enemies(manager.get_group(group_enemies));


void Game::render() {
    SDL_RenderClear(renderer);
    for(auto& tile: tiles) {
        tile->draw();
    }
    for(auto& plyr: players) {
        plyr->draw();
    }
    for(auto& enemy: enemies) {
        enemy->draw();
    }

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "Game Cleaned" << endl;
}

void Game::add_tile(int src_x, int src_y, int x_pos, int y_pos) {
    auto& tile(manager.add_entity());
    tile.add_component<TileComponent>(src_x, src_y, x_pos, y_pos, map_file);
    tile.add_group(group_map);
}

#ifndef Game_hpp
#define Game_hpp

#include "SDL2/SDL.h" 
#include "SDL2/SDL_image.h"
#include <iostream>
#include <vector>

class ColliderComponent;

class Game {

public:
    Game();
    ~Game();

    void init(const char* title, int x_pos, int y_pos, int width, int height, bool full_screen);
    void update();
    void render();
    void clean();
    void handle_events();
 
    bool running() { return is_running; }

    static void add_tile(int src_x, int src_y, int pos_x, int pos_y);
    static SDL_Renderer *renderer;
    static SDL_Event event;
    static std::vector<ColliderComponent*> colliders;
private:
    int count;
    bool is_running;
    SDL_Window *window; 
};

#endif

#include "Game.hpp"

Game *game = nullptr;

int main(int argc, const char *argv[]) {

    const int target_fps = 60;
    const int frame_delay = 1000/ target_fps;

    Uint32 frame_start;
    int frame_time;

    game = new Game();
    game->init("PixelEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

    while(game->running()) {
        // milliseconds passed since SDL was initialized
        frame_start = SDL_GetTicks();
        
        game->handle_events();
        game->update();
        game->render();
        
        // in milliseconds time for the above 
        frame_time = SDL_GetTicks() - frame_start;

        // limiting framerate
        if(frame_delay > frame_time) {
            SDL_Delay(frame_delay - frame_time);
        }
    }

    game->clean();

    return 0;
}
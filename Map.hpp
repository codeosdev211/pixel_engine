#ifndef Map_hpp
#define Map_hpp

#include "Game.hpp"

class Map {

public:
    Map();
    ~Map();

    void load_map(int lvl[20][25]);
    void draw_map();

private:
    SDL_Rect src, dest;
    SDL_Texture *dirt, *grass, *sky;

    int map[20][25];


};

#endif
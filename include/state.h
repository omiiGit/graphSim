#ifndef STATE_H
#define STATE_H

#include <SDL2/SDL.h> 
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "graph.h"

typedef struct 
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    int w,h;

    Graph graph;

    TTF_Font* font;
}State; 

State createState(const char* title,int width,int height);
void initState(State* state,const char* path);
void drawStateBackground(State* state,int r,int g,int b);
void updateState(State* state);

void closeState(State* state);

#endif 

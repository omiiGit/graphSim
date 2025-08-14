#ifndef STATE_H
#define STATE_H

#include <SDL2/SDL.h> 
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "graph.h"

#define PANE_RIGHT \
do{\
state->graph.oX -= 10;\
state->graph.w += 20;\
}while(0)\


#define PANE_LEFT \
do{\
state->graph.oX += 10;\
state->graph.w += 20;\
}while(0)\

#define PANE_UP \
do{\
state->graph.oY += 10;\
state->graph.h += 20;\
}while(0)\

#define PANE_DOWN \
do{\
state->graph.oY -= 10;\
state->graph.h += 20;\
}while(0)\

typedef struct 
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    int w,h,dw,dh;

    Graph graph;

    TTF_Font* font;
}State; 

State createState(const char* title,int width,int height);
void initState(State* state,const char* path);
void drawStateBackground(State* state,int r,int g,int b);
void updateState(State* state);

void closeState(State* state);

#endif 

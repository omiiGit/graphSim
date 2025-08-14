#ifndef GRAPH_H
#define GRAPH_H 

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "font.h"
#include "utils.h"

typedef struct 
{
    int x,y;
    int w,h;
    int scale;

    int r,g,b;
}Grid;

typedef struct 
{
    int w,h;

    int scale;
    int oX;
    int oY;

    TTF_Font* font;
}Graph;

Graph createGraph(int width,int height,int scale);
void drawGrid(SDL_Renderer* renderer,Graph* graph);
void drawRuler(SDL_Renderer* renderer,Graph* graph);
void renderGraph(SDL_Renderer* renderer,Graph* graph);
static void drawAxis(SDL_Renderer* renderer,Graph* graph);

void drawGraph(SDL_Renderer* renderer,Graph* graph);

#endif 

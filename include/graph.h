#ifndef GRAPH_H
#define GRAPH_H 

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "font.h"
#include "utils.h"
#include "list.h"

typedef enum 
{
    NORMAL,
    DRAW,
    MOVE,
}MODE;

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
    List points; 

    TTF_Font* font;

    bool zoomOut;
    bool zoomIn;

    MODE mode;
}Graph;

typedef struct 
{   
    float x,y;
    char info[10];
}Point;

Graph createGraph(int width,int height,int scale);
void updateGraph(Graph* graph);
void drawGrid(SDL_Renderer* renderer,Graph* graph);
void drawRuler(SDL_Renderer* renderer,Graph* graph);
void renderGraph(SDL_Renderer* renderer,Graph* graph);
static void drawAxis(SDL_Renderer* renderer,Graph* graph);


void setPoint(Graph* graph,float x,float y);
void printPoints(Graph* graph);
void drawPoints(SDL_Renderer* renderer,Graph* graph);
void setMode(Graph* graph,MODE mode);


void drawGraph(SDL_Renderer* renderer,Graph* graph);


#endif 

#ifndef GRAPH_H
#define GRAPH_H 

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "font.h"
#include "utils.h"
#include "list.h"
#include "toolbar.h"


#define PANE_RIGHT \
do{\
graph->oX -= 10;\
graph->w += 20;\
}while(0)\


#define PANE_LEFT \
do{\
graph->oX += 10;\
graph->w += 20;\
}while(0)\

#define PANE_UP \
do{\
graph->oY += 10;\
graph->h += 20;\
}while(0)\

#define PANE_DOWN \
do{\
graph->oY -= 10;\
graph->h += 20;\
}while(0)\



typedef enum 
{
    NORMAL = 0x000001,
    DRAW = 0x000002,
    INFO = 0x000004,
    DELETE = 0x000008,
    MOVE = 0x000016,
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

    ToolBar toolbar;


    MODE mode;
}Graph;

typedef struct 
{   
    int mx,my;
    float x,y;
    char info[10];

    bool hover;
    bool clicked;
}Point;

Graph createGraph(int width,int height,int scale);
void initGraph(Graph* graph,MODE mode);
void updateGraph(Graph* graph);
void drawGrid(SDL_Renderer* renderer,Graph* graph);
void drawRuler(SDL_Renderer* renderer,Graph* graph);
void renderGraph(SDL_Renderer* renderer,Graph* graph);


void setPoint(Graph* graph,int mx,int my);
void deletePoint(Graph* graph,int mx,int my);
void printPoints(Graph* graph);
void drawPointSprite(SDL_Renderer* renderer,Graph* graph);
void drawPoints(SDL_Renderer* renderer,Graph* graph);
void setMode(Graph* graph,MODE mode);


void drawGraph(SDL_Renderer* renderer,Graph* graph);
void graphEvent(SDL_Event e,Graph* graph);


#endif 

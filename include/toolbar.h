#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "button.h"



typedef struct 
{

    int x,y;
    int w,h;

    Button draw;
    Button info;
    Button delete;

    bool hover;

}ToolBar;

ToolBar createToolBar(int x,int y,int w,int h);
void initToolBar(ToolBar* toolbar);
void drawToolBar(SDL_Renderer* renderer,ToolBar* toolbar);
void toolbarEvent(SDL_Event e,ToolBar* toolbar);





#endif 


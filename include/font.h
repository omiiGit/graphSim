#ifndef FONT_H 
#define FONT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h> 

void drawText(SDL_Renderer* renderer,TTF_Font* font,const char* text,int x,int y,int r,int g,int b);

#endif 

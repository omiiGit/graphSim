#ifndef BUTTON_H 
#define BUTTON_H 

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <stdbool.h>

typedef struct 
{
    int x,y;
    int w,h;

    SDL_Rect blit;
    SDL_Texture* texture;

    bool hover;
    bool clicked;
    bool selected;
}Button;


Button createButton(int x,int y,int w,int h);
void setButtonBlit(Button* button,int x,int y,int w,int h);
void drawButton(SDL_Renderer* renderer,Button* button,const char* path);

void buttonEvent(SDL_Event e,Button* button);

#endif

#include "font.h" 

void drawText(SDL_Renderer* renderer,TTF_Font* font,const char* text,int x,int y,int r,int g,int b)
{
    SDL_Color fontColor = {r,g,b,255};
    SDL_Surface* fontSurface = TTF_RenderText_Solid(font,text,fontColor);
    SDL_Texture* fontTexture = SDL_CreateTextureFromSurface(renderer,fontSurface);

    SDL_Rect vec = {x,y,fontSurface->w,fontSurface->h};

    SDL_RenderCopy(renderer,fontTexture,NULL,&vec);

    SDL_FreeSurface(fontSurface);
    SDL_DestroyTexture(fontTexture);
}

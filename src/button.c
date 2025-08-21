#include "button.h" 

Button createButton(int x,int y,int w,int h)
{
    return(Button)
    {
        .x = x,
        .y = y,
        .w = w,
        .h = h,
        .texture = NULL,
        .hover = false,
        .clicked = false,
        .selected = false,
    };
}

void setButtonBlit(Button* button,int x,int y,int w,int h)
{
   button->blit.x = x; 
   button->blit.y = y; 
   button->blit.w = w; 
   button->blit.h = h; 
}

void drawButton(SDL_Renderer* renderer,Button* button,const char* path)
{
    SDL_Texture* bTexture = IMG_LoadTexture(renderer,path);   

    if(bTexture == NULL) 
    {
        printf("Failed to load Button image! -%s\n",IMG_GetError());
    }
    
    SDL_Rect bRec = {button->x,button->y,button->w,button->h};



    if(button->hover && !button->selected)
    {
        setButtonBlit(button,button->blit.x,button->blit.y+40,40,40);
    }
    if(button->selected)
    {
        setButtonBlit(button,button->blit.x,button->blit.y+80,40,40);
    }
    if (!button->hover && !button->clicked) 
    {
        setButtonBlit(button,button->blit.x,button->blit.y,40,40);
    }

    SDL_RenderCopy(renderer,bTexture,&button->blit,&bRec);

    SDL_DestroyTexture(bTexture);
    
}

void buttonEvent(SDL_Event e,Button* button)
{
    int mouseX,mouseY;

    switch(e.type)
    {
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&mouseX,&mouseY);

            if(mouseX >= button->x && mouseX <= button->x + button->w && 
            mouseY >= button->y && mouseY <= button->y + button->h)
            {
                button->hover = true;
            }
            else 
            {
                button->hover = false;
            }
        break;
        case SDL_MOUSEBUTTONDOWN:
            if(button->hover)
            {
                button->clicked = true;
            }
            else 
            {
                button->clicked = false;
            }
        break;
    }
}

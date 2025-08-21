#include "toolbar.h" 


ToolBar createToolBar(int x,int y,int w,int h)
{
    return(ToolBar)
    {
        .x = x,
        .y = y, 
        .w = w, 
        .h = h,
        .hover = false,
        .draw = createButton(x+10,y+10,40,40),
        .info = createButton(x+10,y+50,40,40),
        .delete = createButton(x+10,y+90,40,40),
    };
}

void initToolBar(ToolBar* toolbar)
{
    int x = toolbar->x + 10;
    int y = toolbar->y + 10;

    toolbar->draw = createButton(x,y,50,50);
}

void drawToolBar(SDL_Renderer* renderer,ToolBar* toolbar)
{

    SDL_Rect rect = {toolbar->x,toolbar->y,toolbar->w,toolbar->h};

    SDL_Texture* image = IMG_LoadTexture(renderer,"res/toolbar.png");

    SDL_SetRenderTarget(renderer,NULL);
    SDL_RenderCopy(renderer,image,NULL,&rect);

    SDL_DestroyTexture(image);
    
    setButtonBlit(&toolbar->draw,0,0,40,40);
    drawButton(renderer,&toolbar->draw,"res/buttons.png");

    setButtonBlit(&toolbar->info,40,0,40,40);
    drawButton(renderer,&toolbar->info,"res/buttons.png");

    setButtonBlit(&toolbar->delete,80,0,40,40);
    drawButton(renderer,&toolbar->delete,"res/buttons.png");

}


void toolbarEvent(SDL_Event e,ToolBar* toolbar)
{
    int mouseX,mouseY;

    switch(e.type)
    {
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&mouseX,&mouseY);

            if(mouseX >= toolbar->x && mouseX <= toolbar->x + toolbar->w && 
            mouseY >= toolbar->y && mouseY <= toolbar->y + toolbar->h)
            {
                toolbar->hover = true;
            }
            else 
            {
                toolbar->hover = false;
            }

        break;
        case SDL_MOUSEBUTTONDOWN:
            
        break;
    }
    buttonEvent(e,&toolbar->draw);
    buttonEvent(e,&toolbar->info);
    buttonEvent(e,&toolbar->delete);
}

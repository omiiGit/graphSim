#include "graph.h" 


Graph createGraph(int width,int height,int scale)
{
    return(Graph)
    {
        .w = width,
        .h = height,
        .scale = scale,
        .oX = width/2,
        .oY = height/2,
        .font = NULL,
    };
}

static void drawAxis(SDL_Renderer* renderer,Graph* graph)
{
    SDL_SetRenderDrawColor(renderer,255,0,0,255);

    SDL_Rect xLine = {0,graph->oY,graph->w,2};
    SDL_RenderFillRect(renderer,&xLine);

    SDL_Rect yLine = {graph->oX,0,2,graph->h};
    SDL_RenderFillRect(renderer,&yLine);

}

void drawGrid(SDL_Renderer* renderer,Graph* graph)
{
    SDL_SetRenderDrawColor(renderer,211,211,211,255);
    
    //horizontal
    for(int i = 0;i < graph->h/2;i += 5)
    {
        SDL_Rect uline;
        SDL_Rect dline;
        if(i % graph->scale == 0)
        {
            uline = (SDL_Rect){.x=0,.y=graph->oY - i,.w=graph->w,.h=2};
            dline = (SDL_Rect){.x=0,.y=graph->oY + i,.w=graph->w,.h=2};
        }
        else
        {
            uline = (SDL_Rect){.x=0,.y=graph->oY - i,.w=graph->w,.h=1};
            dline = (SDL_Rect){.x=0,.y=graph->oY + i,.w=graph->w,.h=1};
        }

        SDL_RenderFillRect(renderer,&uline);
        SDL_RenderFillRect(renderer,&dline);
    }
    
    //vertical
    for(int i = 0;i < graph->w/2;i += 5)
    {
        SDL_Rect lline;
        SDL_Rect rline;
        if(i % graph->scale == 0)
        {
            lline = (SDL_Rect){.x=graph->oX - i,.y=0,.w=2,.h=graph->h};
            rline = (SDL_Rect){.x=graph->oX + i,.y=0,.w=2,.h=graph->h};
        }
        else
        {
            lline = (SDL_Rect){.x=graph->oX - i,.y=0,.w=1,.h=graph->h};
            rline = (SDL_Rect){.x=graph->oX + i,.y=0,.w=1,.h=graph->h};
        }

        SDL_RenderFillRect(renderer,&lline);
        SDL_RenderFillRect(renderer,&rline);
    }

}

void drawRuler(SDL_Renderer* renderer,Graph* graph)
{
    SDL_SetRenderDrawColor(renderer,0,0,0,255);

    int meterN = 1; 
    int meterP = -1;

    for(int i = graph->scale,x = graph->oX;i < graph->h/2-1;i += graph->scale)
    {
        SDL_Rect uline;
        SDL_Rect dline;

        uline = (SDL_Rect){.x=x,.y=graph->oY - i,.w=5,.h=2};
        dline = (SDL_Rect){.x=x,.y=graph->oY + i,.w=5,.h=2};

        char textValueP[5]; i_toa(meterP,textValueP);
        char textValueN[5]; i_toa(meterN,textValueN);

        SDL_RenderFillRect(renderer,&uline);
        SDL_RenderFillRect(renderer,&dline);

        drawText(renderer,graph->font,textValueP,x+8,graph->oY + i,85,23,23);
        drawText(renderer,graph->font,textValueN,x+8,graph->oY - i,85,23,23);
        
        meterP--;
        meterN++;

    }

    meterN = -1; 
    meterP = 1;

    for(int i = graph->scale,y = graph->oY;i < graph->w/2-1;i += graph->scale)
    {
        SDL_Rect lline;
        SDL_Rect rline;

        lline = (SDL_Rect){.x=graph->oX - i,.y=y,.w=2,.h=5};
        rline = (SDL_Rect){.x=graph->oX + i,.y=y,.w=2,.h=5};

        char textValueP[5]; i_toa(meterP,textValueP);
        char textValueN[5]; i_toa(meterN,textValueN);

        SDL_RenderFillRect(renderer,&lline);
        SDL_RenderFillRect(renderer,&rline);

        drawText(renderer,graph->font,textValueP,graph->oX + i,y+8,85,23,23);
        drawText(renderer,graph->font,textValueN,graph->oX - i,y+8,85,23,23);
        
        meterP++;
        meterN--;
    }
}

void renderGraph(SDL_Renderer* renderer,Graph* graph)
{
    drawGrid(renderer,graph);
    drawAxis(renderer,graph);
    drawRuler(renderer,graph);

    drawText(renderer,graph->font,"graphSim",10,10,0,0,255);

    char* textScale = NULL;
    char sScale[4]; i_toa(graph->scale,sScale);

    appendStr(&textScale,"SCALE: ");
    appendStr(&textScale,sScale);

    drawText(renderer,graph->font,textScale,10,25,0,0,255);
    free(textScale);
}

void drawGraph(SDL_Renderer* renderer,Graph* graph)
{
    renderGraph(renderer,graph);
}


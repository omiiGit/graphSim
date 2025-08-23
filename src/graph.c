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
        .zoomIn = false,
        .zoomOut = false,
        .mode = NORMAL,
        .toolbar = createToolBar(10,100,60,300),
    };
}

void updateGraph(Graph* graph)
{
    if(graph->zoomOut && graph->scale > 10) 
            graph->scale -= 5;
    if(graph->zoomIn)
        graph->scale += 5;
    graph->zoomOut = graph->zoomIn = false;


    if(graph->toolbar.hover == false && (graph->mode & DELETE))
    {
        int mx,my;

        SDL_GetMouseState(&mx,&my);

        for(int i = 0;i < graph->points.count;i++)
        {
            Point* point = LIST_GET_WHOLE(Point,&graph->points,i);

            if(mx+1 >= point->mx && mx+1 <= point->mx + 4 && my+2 >= point->my && my+2 <= point->my + 4)
            {
                point->hover = true;
            }
            else 
            {
                point->hover = false;
            }
        }
    }

    if(graph->toolbar.draw.clicked)
    {
        printf("draw is clicked\n");
        graph->mode &= ~DELETE;

        if(!graph->toolbar.draw.selected)
        {
            graph->toolbar.draw.selected = true;
            graph->mode |= DRAW;
        }
        else 
        {
            graph->toolbar.draw.selected = false;
            graph->mode &= ~DRAW;

        }

        graph->toolbar.draw.clicked = false;
    }

    if(graph->toolbar.info.clicked)
    {
        printf("info is clicked\n");
        
        if(!graph->toolbar.info.selected)
        {
            graph->toolbar.info.selected = true;
            graph->mode |= INFO;
        }
        else 
        {
            graph->toolbar.info.selected = false;
            graph->mode &= ~INFO;
        }


        graph->toolbar.info.clicked = false;
    }

    if(graph->toolbar.delete.clicked)
    {
        printf("delete is clicked\n");
        graph->mode &= ~DRAW;

        if(graph->toolbar.draw.selected)
            graph->toolbar.draw.selected = false;

        if(!graph->toolbar.delete.selected)
        {
            graph->toolbar.delete.selected = true;
            graph->mode |= DELETE;
        }
        else 
        {
            graph->toolbar.delete.selected = false;
            graph->mode &= ~DELETE;

        }


        graph->toolbar.delete.clicked = false;
    }

}

void initGraph(Graph* graph,MODE mode)
{
    graph->mode = mode;
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
    drawPoints(renderer,graph);
    if(graph->mode & DRAW)
        drawPointSprite(renderer,graph);

    drawToolBar(renderer,&graph->toolbar);

    drawText(renderer,graph->font,"graphSim",10,10,0,0,255);
    char* textScale = NULL;
    char sScale[4]; i_toa(graph->scale,sScale);
    appendStr(&textScale,"SCALE: ");
    appendStr(&textScale,sScale);
    appendStr(&textScale,"px");
    drawText(renderer,graph->font,textScale,10,25,0,0,255);
    free(textScale);

}



void setPoint(Graph* graph,int mx,int my)
{

    float x = (float)(mx - graph->oX) / graph->scale;
    float y = (float)(my - graph->oY) / -graph->scale; 

    Point point = {mx,my,x,y};
    point.hover = false;
    char sx[10]; snprintf(sx,10,"%.1f",point.x);
    char sy[10]; snprintf(sy,10,"%.1f",point.y);

    char* info = NULL;
    appendStr(&info,sx);
    appendStr(&info,",");
    appendStr(&info,sy);

    strcpy(point.info,info);

    free(info);

    LIST_ADD(Point,&graph->points,point); 
    printPoints(graph);
}

void deletePoint(Graph* graph,int mx,int my)
{
    float x = (float)(mx - graph->oX) / graph->scale;
    float y = (float)(my - graph->oY) / -graph->scale; 

}

void printPoints(Graph* graph)
{

    for(int i = 0;i < graph->points.count;i++)
    {
        Point point = LIST_GET(Point,&graph->points,i);

        printf("Point %d = %g , %g \"%s\" %d\n",i,point.x,point.y,point.info,point.hover);
    }
}

void drawPointSprite(SDL_Renderer* renderer,Graph* graph)
{
    int mx,my;

    SDL_GetMouseState(&mx,&my);

    SDL_Rect sprite = {mx-1,my-2,4,4};
    SDL_SetRenderTarget(renderer,NULL);

    SDL_SetRenderDrawColor(renderer,172,216,230,255);
    SDL_RenderFillRect(renderer,&sprite);

    SDL_SetRenderTarget(renderer,NULL);
}

void drawPoints(SDL_Renderer* renderer,Graph* graph)
{

    for(int i = 0;i < graph->points.count;i++)
    {
        Point point = LIST_GET(Point,&graph->points,i);

        int sx = graph->oX + (graph->scale * point.x);
        int sy = graph->oY - (graph->scale * point.y);
        
        if(point.hover == true)
            SDL_SetRenderDrawColor(renderer,255,0,0,255);
        else 
            SDL_SetRenderDrawColor(renderer,0,0,255,255);


        SDL_Rect p = {sx-1,sy-2,4,4};

        SDL_RenderFillRect(renderer,&p);
        
        if(graph->mode & INFO)
            drawText(renderer,graph->font,point.info,sx-25,sy-15,1,50,32);
    }
}


void drawGraph(SDL_Renderer* renderer,Graph* graph)
{
    renderGraph(renderer,graph);
}


void graphEvent(SDL_Event e,Graph* graph)
{

    int mouseX,mouseY;

    switch(e.type)
    {
        case SDL_KEYDOWN:
            switch(e.key.keysym.sym)
            {
                case SDLK_d:
                    PANE_RIGHT;
                break;
                case SDLK_a:
                    PANE_LEFT; 
                break;
                case SDLK_w:
                    PANE_UP;
                break;
                case SDLK_s:
                    PANE_DOWN;
                break;
            }
            break;
            case SDL_MOUSEWHEEL:

                if(e.wheel.y < 0)
                {
                    graph->zoomOut = true;
                }
                else 
                {
                    graph->zoomIn = true;
                }
            break;
            case SDL_MOUSEMOTION:

            break;
            case SDL_MOUSEBUTTONDOWN:
                if(graph->toolbar.hover == false && (graph->mode & DRAW))
                {
                    SDL_GetMouseState(&mouseX,&mouseY);
                    setPoint(graph,mouseX,mouseY);
                }
                if(graph->toolbar.hover == false && (graph->mode & DELETE))
                {
                           int mx,my;

                    SDL_GetMouseState(&mx,&my);

                    for(int i = 0;i < graph->points.count;i++)
                    {
                        Point* point = LIST_GET_WHOLE(Point,&graph->points,i);
    
                        if(point->hover)
                        {
                            LIST_DEL(Point,&graph->points,i);
                        }
                    } 
                }
            break;
    }

    toolbarEvent(e,&graph->toolbar);
}

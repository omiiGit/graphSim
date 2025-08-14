#include "state.h" 


State createState(const char* title,int width,int height)
{
    return(State)
    {
        .w = width,
        .h = height,
        .window = SDL_CreateWindow(title,
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                width,
                height,
                SDL_WINDOW_SHOWN),
        .font = NULL,
        .renderer = NULL,
    };
}

void initState(State* state,const char* path)
{
    state->renderer = SDL_CreateRenderer(state->window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    state->font = TTF_OpenFont(path,15);

    state->dw = state->w;
    state->dh = state->h;

    state->graph = createGraph(state->w,state->h,20);

    state->graph.font = state->font;
}

void drawStateBackground(State* state,int r,int g,int b)
{
    SDL_SetRenderDrawColor(state->renderer,r,g,b,255);
    SDL_RenderClear(state->renderer);
}

void updateState(State* state)
{
    bool quit = false;
    SDL_Event e;
    int mouseX,mouseY;

    setPoint(&state->graph,1,1);

    while(!quit)
    {

        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
                case SDL_QUIT: quit = true; break;
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym)
                    {
                        case SDLK_RIGHT:
                            PANE_RIGHT;
                        break;
                        case SDLK_LEFT:
                            PANE_LEFT; 
                        break;
                        case SDLK_UP:
                            PANE_UP; 
                        break;
                        case SDLK_DOWN:
                            PANE_DOWN;
                        break;
                    }
                break;
                case SDL_MOUSEWHEEL:

                    if(e.wheel.y < 0)
                    {
                        state->graph.zoomOut = true;
                    }
                    else 
                    {
                        state->graph.zoomIn = true;
                    }
                break;
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&mouseX,&mouseY);

                    float x = (float)(mouseX - state->graph.oX) / state->graph.scale;

                    float y = (float)(mouseY - state->graph.oY) / -state->graph.scale; 

                    setPoint(&state->graph,x,y);
                    //printPoints(&state->graph);
                break;
              
            }
        }

        updateGraph(&state->graph);


        drawStateBackground(state,255,255,255);
        drawGraph(state->renderer,&state->graph);

        SDL_RenderPresent(state->renderer);
    }

}

void closeState(State* state)
{
    SDL_DestroyRenderer(state->renderer);
    TTF_CloseFont(state->font);
    SDL_DestroyWindow(state->window);
}


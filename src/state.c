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

    initGraph(&state->graph,NORMAL);

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
    //int mouseX,mouseY;


    while(!quit)
    {

        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
                case SDL_QUIT: quit = true; break;
            }
            graphEvent(e,&state->graph);
        }

        updateGraph(&state->graph);

        drawStateBackground(state,255,255,255);
        drawGraph(state->renderer,&state->graph);

        SDL_RenderPresent(state->renderer);
        SDL_Delay(16);
    }

}

void closeState(State* state)
{
    SDL_DestroyRenderer(state->renderer);
    TTF_CloseFont(state->font);
    SDL_DestroyWindow(state->window);
}


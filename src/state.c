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
    
    state->font = TTF_OpenFont(path,12);

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
                        case SDLK_UP:
                            printf("Up key Pressed\n");
                            state->graph.scale += 5;
                        break;
                        case SDLK_DOWN:
                            printf("Down key Pressed\n");
                            state->graph.scale -= 5;
                        break;
                    }
                break;
            }
        }

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


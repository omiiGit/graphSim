#include <stdio.h>
#include "state.h" 
#include "Macro.h"

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    State window = createState("graphSim",WIDTH,HEIGHT);

    initState(&window,"res/dina10px.ttf");
    updateState(&window);

    closeState(&window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

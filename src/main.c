#include <stdio.h>
#include "state.h" 
#include "Macro.h"

#define DEBUG 1



int main()
{
#if DEBUG == 1
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    State window = createState("graphSim",WIDTH,HEIGHT);

    initState(&window,"res/dina10px.ttf");
    updateState(&window);

    closeState(&window);
    TTF_Quit();
    SDL_Quit();
#endif 

#if DEBUG == 0
    List list = createList();


    LIST_ADD(int,&list,1);
    LIST_ADD(int,&list,2);
    LIST_ADD(int,&list,3);
    LIST_ADD(int,&list,4);
    LIST_ADD(int,&list,29);

    PRINT_LIST(int,&list);

    LIST_DEL(int,&list,0);
    LIST_ADD(int,&list,10);
    LIST_DEL(int,&list,1);

    printf("\n");
    PRINT_LIST(int,&list);
#endif

    return 0;
}

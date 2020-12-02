// ### SDL2-C ###

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <windows.h>
#include "circle.c"
// have to put 'SDL2.dll' in bin file and setup build settings

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 360

typedef struct renderer{
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;
}renderer;

typedef struct rendererObject{
    SDL_Surface *pSurface;
    SDL_Texture *pTexture;
}rendererObject;

renderer sRenderer;

int main(int argc, char *argv[])
{
    sRenderer.pWindow = NULL;
    sRenderer.pRenderer = NULL;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        SDL_Log("Unable to initialize SDL : %s", SDL_GetError());
        return 1; // return error
    }else{
        SDL_Point wSize = {WINDOW_WIDTH, WINDOW_HEIGHT}; // Vector2()
        SDL_Point wPos = {(GetSystemMetrics(SM_CXSCREEN) / 2) - (wSize.x / 2), (GetSystemMetrics(SM_CYSCREEN) / 2) - (wSize.y / 2)}; // center window on the screen
        SDL_Rect wRect = {wPos.x, wPos.y, wSize.x, wSize.y}; // use rectangle structure to qualify the window dimensions
        sRenderer.pWindow = SDL_CreateWindow("An SDL2 window", wRect.x, wRect.y, wRect.w, wRect.h, SDL_WINDOW_SHOWN);

        if (sRenderer.pWindow){
            sRenderer.pRenderer = SDL_CreateRenderer(sRenderer.pWindow, -1, SDL_RENDERER_PRESENTVSYNC);
        }

        int flags = IMG_INIT_JPG|IMG_INIT_PNG;
        int initted = IMG_Init(flags);
        if ((initted & flags) != flags){
            SDL_Log("IMG_Init : Failed to init required .jpg and .png support !\n");
            SDL_Log("IMG_Init : %s\n", IMG_GetError());
        }

        if (sRenderer.pRenderer){
            // set color
            SDL_SetRenderDrawColor(sRenderer.pRenderer, 42, 42, 42, SDL_ALPHA_OPAQUE);
            // clear renderer
            SDL_RenderClear(sRenderer.pRenderer);
        }

        SDL_Point rectPos = {50, 50};
        SDL_Point rectSize = {84, 75};
        SDL_Rect rect0 = {rectPos.x, rectPos.y, rectSize.x, rectSize.y};

        SDL_Rect rect1;
        rect1.x = wSize.x - (rectPos.x + rectSize.x);
        rect1.y = rectPos.y;
        rect1.w = rectSize.x;
        rect1.h = rectSize.y;

        SDL_SetRenderDrawColor(sRenderer.pRenderer, 100, 100, 100, SDL_ALPHA_OPAQUE);

        // draw rectangles
        SDL_RenderDrawRect(sRenderer.pRenderer, &rect0);
        SDL_RenderFillRect(sRenderer.pRenderer, &rect1);
        printf("Rectangles OK\n");

        // draw circles
        DrawCircle(sRenderer.pRenderer, rect0.x + rect0.w / 2, rect0.y + rect0.h / 2 + 100, rect0.w / 2, 0);
        DrawCircle(sRenderer.pRenderer, rect1.x + rect1.w / 2, rect1.y + rect1.h / 2 + 100, rect1.w / 2, 1);
        printf("Circle OK\n");

        // draw surface
        rendererObject isaacHead;
        isaacHead.pSurface = SDL_LoadBMP("./assets/image/isaac.bmp");
        if (!isaacHead.pSurface)
            printf("isaac.bmp --- LOAD ERROR !\n");
        isaacHead.pTexture = SDL_CreateTextureFromSurface(sRenderer.pRenderer, isaacHead.pSurface);

        rendererObject darkHead;
        darkHead.pSurface = IMG_Load("./assets/image/dark.png");
        if (!darkHead.pSurface)
            printf("dark.png --- LOAD ERROR !\n");
        darkHead.pTexture = SDL_CreateTextureFromSurface(sRenderer.pRenderer, darkHead.pSurface);


        SDL_RenderCopy(sRenderer.pRenderer, isaacHead.pTexture, NULL, &rect0); // render texture on rect1
        SDL_RenderCopy(sRenderer.pRenderer, darkHead.pTexture, NULL, &rect1); // render texture on rect0
        SDL_FreeSurface(isaacHead.pSurface); // we need to deallocate
        SDL_FreeSurface(darkHead.pSurface); // we need to deallocate

        SDL_RenderPresent(sRenderer.pRenderer);
        printf("Surfaces & Texture OK\n");

        SDL_Delay(2000); // wait n ms
        SDL_Quit(); // destroy SDL
    }
    return 0;
}

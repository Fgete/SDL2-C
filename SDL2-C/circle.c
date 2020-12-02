#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>

#define RESOLUTION 1024
#define PI 3.1415927

void DrawCircle(SDL_Renderer *renderer, int x, int y, int rayon, int filled);

void DrawCircle(SDL_Renderer *renderer, int x, int y, int r, int f){
    int xA = x + r*cos(0);
    int yA = y + r*sin(0);

    if (!f){
        for (int i = 0; i <= RESOLUTION; i++){
            float theta = (float)i / RESOLUTION;
            int xB = x + r*cos(theta * 2 * PI);
            int yB = y + r*sin(theta * 2 * PI);
            SDL_RenderDrawLine(renderer, xA, yA, xB, yB);
            xA = xB;
            yA = yB;
        }
    }else{
        for (int j = 0; j <= r; j++){
            for (int i = 0; i <= RESOLUTION; i++){
                float theta = (float)i / RESOLUTION;
                int xB = x + j*cos(theta * 2 * PI);
                int yB = y + j*sin(theta * 2 * PI);
                SDL_RenderDrawLine(renderer, x, y, xB, yB);
                xA = xB;
                yA = yB;
            }
        }
    }
}

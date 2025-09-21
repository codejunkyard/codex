#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    int WIDTH = 400, HEIGHT = 300;
    SDL_Window *win = SDL_CreateWindow("SDL2 Bouncing Ball",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WIDTH, HEIGHT, 0);
    if (!win) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (!ren) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    int x = 50, y = 50;
    int dx = 3, dy = 2;
    int radius = 20;
    SDL_Event e;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = 0;
        }

        // Move ball
        x += dx;
        y += dy;

        // Bounce off walls
        if (x - radius <= 0 || x + radius >= WIDTH) dx = -dx;
        if (y - radius <= 0 || y + radius >= HEIGHT) dy = -dy;

        // Draw
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255); // black background
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 255, 0, 0, 255); // red ball
        for (int w = 0; w < radius * 2; w++)
            for (int h = 0; h < radius * 2; h++)
                if ((w - radius)*(w - radius) + (h - radius)*(h - radius) <= radius*radius)
                    SDL_RenderDrawPoint(ren, x + w - radius, y + h - radius);

        SDL_RenderPresent(ren);
        SDL_Delay(16); // ~60 FPS
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

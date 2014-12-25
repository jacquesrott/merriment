#include <SDL2/SDL.h>
#include <stdio.h>


int main() {
    int width = 1440;
    int height = 900;

    SDL_Window* window = NULL;
    if (-1 == SDL_Init(SDL_INIT_EVERYTHING)) {
        printf("Failed to initialize SDL error=%s\n", SDL_GetError());
        exit(1);
    }

    atexit(SDL_Quit);

    return 0;
}

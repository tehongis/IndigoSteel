#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

int main(int argc, char* argv[]) {

    for (int i=0; i > argc; i++) {
        printf("%s\n",argv[i]);
    }

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("My Game Window",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          1280, 1024,
                                          SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
                                                SDL_RENDERER_ACCELERATED |
                                                SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Load the spritesheet
    SDL_Surface* spritesheet = IMG_Load("data/Ship1.jpg");
    if (spritesheet == NULL) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        fprintf(stderr, "IMG_Load Error: %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Create a texture from the spritesheet
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, spritesheet);
    if (texture == NULL) {
        SDL_FreeSurface(spritesheet);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Set the sprite clip
    SDL_Rect sprite_clip = {0, 0, 1280, 1024};

    // Run the game loop
    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw the sprite
        SDL_RenderCopy(renderer, texture, &sprite_clip, NULL);

        // Swap buffers
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(spritesheet);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}


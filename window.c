#include "maze.h"

/**
 * init_window - Initialize SDL and create window and renderer
 * @game: Pointer to GameState struct
 *
 * Return: true if successful, false otherwise
 */
bool init_window(GameState *game)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return (false);
    }
    
    game->window = SDL_CreateWindow("Maze", SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                    SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (game->window == NULL)
    {
        SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return (false);
    }
    
    game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);
    if (game->renderer == NULL)
    {
        SDL_Log("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return (false);
    }
    
    return (true);
}

/**
 * close_window - Clean up SDL resources
 * @game: Pointer to GameState struct
 */
void close_window(GameState *game)
{
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    SDL_Quit();
}

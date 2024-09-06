#include "maze.h"

#include <math.h>

bool load_textures(GameState *game)
{
    const char *texture_files[NUM_TEXTURES] = {
        "textures/wall1.jpeg",
        "textures/wall1.jpeg",
        "textures/wall1.jpeg",
        "textures/wall1.jpeg"
    };

    for (int i = 0; i < NUM_TEXTURES; i++)
    {
        SDL_Surface *surface = IMG_Load(texture_files[i]);
        if (!surface)
        {
            SDL_Log("Failed to load texture: %s", IMG_GetError());
            return false;
        }

        game->textures[i].texture = SDL_CreateTextureFromSurface(game->renderer, surface);
        game->textures[i].width = surface->w;
        game->textures[i].height = surface->h;

        SDL_FreeSurface(surface);

        if (!game->textures[i].texture)
        {
            SDL_Log("Failed to create texture: %s", SDL_GetError());
            return false;
        }
    }

    return true;
}

void unload_textures(GameState *game)
{
    for (int i = 0; i < NUM_TEXTURES; i++)
    {
        if (game->textures[i].texture)
        {
            SDL_DestroyTexture(game->textures[i].texture);
            game->textures[i].texture = NULL;
        }
    }
}


#include "maze.h"
#include <math.h>

/**
 * handle_keys - Handle keyboard input
 * @game: Pointer to GameState struct
 * @keyboard_state: Pointer to SDL keyboard state
 */
void handle_keys(GameState *game, const Uint8 *keyboard_state)
{
    double move_speed = 0.05;
    double rot_speed = 0.03;

    if (keyboard_state[SDL_SCANCODE_UP] || keyboard_state[SDL_SCANCODE_W])
        move_player(game, move_speed, 0);
    if (keyboard_state[SDL_SCANCODE_DOWN] || keyboard_state[SDL_SCANCODE_S])
        move_player(game, -move_speed, 0);
    if (keyboard_state[SDL_SCANCODE_RIGHT] || keyboard_state[SDL_SCANCODE_D])
        move_player(game, 0, rot_speed);
    if (keyboard_state[SDL_SCANCODE_LEFT] || keyboard_state[SDL_SCANCODE_A])
        move_player(game, 0, -rot_speed);
}

/**
 * move_player - Move the player based on input
 * @game: Pointer to GameState struct
 * @move_speed: Speed of movement
 * @rot_speed: Speed of rotation
 */
void move_player(GameState *game, double move_speed, double rot_speed)
{
    if (move_speed != 0)
    {
        double new_x = game->pos_x + game->dir_x * move_speed;
        double new_y = game->pos_y + game->dir_y * move_speed;

        if (worldMap[(int)new_x][(int)game->pos_y] == 0)
            game->pos_x = new_x;
        if (worldMap[(int)game->pos_x][(int)new_y] == 0)
            game->pos_y = new_y;
    }

    if (rot_speed != 0)
    {
        double old_dir_x = game->dir_x;
        game->dir_x = game->dir_x * cos(rot_speed) - game->dir_y * sin(rot_speed);
        game->dir_y = old_dir_x * sin(rot_speed) + game->dir_y * cos(rot_speed);
        double old_plane_x = game->plane_x;
        game->plane_x = game->plane_x * cos(rot_speed) - game->plane_y * sin(rot_speed);
        game->plane_y = old_plane_x * sin(rot_speed) + game->plane_y * cos(rot_speed);
    }
}

/**
 * main - Entry point of the program
 *
 * Return: 0 on success, 1 on failure
 */

int main(void)
{
    GameState game = {0};
    
    if (!init_window(&game))
        return (1);
    
    if (!load_textures(&game))
    {
        close_window(&game);
        return (1);
    }
    
    init_map();
    
    game.pos_x = 22;
    game.pos_y = 12;
    game.dir_x = -1;
    game.dir_y = 0;
    game.plane_x = 0;
    game.plane_y = 0.66;
    
    game.is_running = true;
    while (game.is_running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                game.is_running = false;
        }
        
        const Uint8 *keyboard_state = SDL_GetKeyboardState(NULL);
        handle_keys(&game, keyboard_state);
        
        SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, 255);
        SDL_RenderClear(game.renderer);
        
        cast_rays(&game);
        
        SDL_RenderPresent(game.renderer);
    }
    
    unload_textures(&game);
    close_window(&game);
    return (0);
}

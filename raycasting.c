#include "maze.h"
#include <math.h>

/**
 * cast_rays - Cast rays and render the 3D view
 * @game: Pointer to GameState struct
 */
void cast_rays(GameState *game)
{
    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        double camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
        double ray_dir_x = game->dir_x + game->plane_x * camera_x;
        double ray_dir_y = game->dir_y + game->plane_y * camera_x;

        int map_x = (int)game->pos_x;
        int map_y = (int)game->pos_y;

        double side_dist_x, side_dist_y;

        double delta_dist_x = fabs(1 / ray_dir_x);
        double delta_dist_y = fabs(1 / ray_dir_y);
        double perp_wall_dist;

        int step_x, step_y;

        int hit = 0;
        int side;

        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (game->pos_x - map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - game->pos_x) * delta_dist_x;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (game->pos_y - map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - game->pos_y) * delta_dist_y;
        }

        while (hit == 0)
        {
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            if (worldMap[map_x][map_y] > 0)
                hit = 1;
        }

        if (side == 0)
            perp_wall_dist = (map_x - game->pos_x + (1 - step_x) / 2) / ray_dir_x;
        else
            perp_wall_dist = (map_y - game->pos_y + (1 - step_y) / 2) / ray_dir_y;

        int line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);

        int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
        if (draw_start < 0)
            draw_start = 0;
        int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
        if (draw_end >= SCREEN_HEIGHT)
            draw_end = SCREEN_HEIGHT - 1;

        // Texture calculations
        int tex_num = worldMap[map_x][map_y] - 1;
        double wall_x;
        if (side == 0)
            wall_x = game->pos_y + perp_wall_dist * ray_dir_y;
        else
            wall_x = game->pos_x + perp_wall_dist * ray_dir_x;
        wall_x -= floor(wall_x);

        int tex_x = (int)(wall_x * TEX_WIDTH);
        if (side == 0 && ray_dir_x > 0)
            tex_x = TEX_WIDTH - tex_x - 1;
        if (side == 1 && ray_dir_y < 0)
            tex_x = TEX_WIDTH - tex_x - 1;

        double step = 1.0 * TEX_HEIGHT / line_height;
        double tex_pos = (draw_start - SCREEN_HEIGHT / 2 + line_height / 2) * step;

        for (int y = draw_start; y < draw_end; y++)
        {
            int tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
            tex_pos += step;

            SDL_Rect src_rect = {tex_x, tex_y, 1, 1};
            SDL_Rect dst_rect = {x, y, 1, 1};

            SDL_RenderCopy(game->renderer, game->textures[tex_num].texture, &src_rect, &dst_rect);
        }
    }
}


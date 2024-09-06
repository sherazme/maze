#ifndef MAZE_H
#define MAZE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define NUM_TEXTURES 4
#define TEX_WIDTH 64
#define TEX_HEIGHT 64

typedef struct {
    SDL_Texture *texture;
    int width;
    int height;
} Texture;

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool is_running;
    double pos_x;
    double pos_y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
    Texture textures[NUM_TEXTURES];
} GameState;

extern int worldMap[MAP_WIDTH][MAP_HEIGHT];

/* window.c */
bool init_window(GameState *game);
void close_window(GameState *game);

/* raycasting.c */
void cast_rays(GameState *game);

/* map.c */
void init_map(void);

/* main.c */
void handle_keys(GameState *game, const Uint8 *keyboard_state);
void move_player(GameState *game, double move_speed, double rot_speed);

/* textures.c */
bool load_textures(GameState *game);
void unload_textures(GameState *game);

#endif

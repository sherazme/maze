#include "maze.h"

int worldMap[MAP_WIDTH][MAP_HEIGHT];

/**
 * init_map - Initialize the world map
 */
void init_map(void)
{
    for (int x = 0; x < MAP_WIDTH; x++)
    {
        for (int y = 0; y < MAP_HEIGHT; y++)
{
            if (x == 0 || x == MAP_WIDTH - 1 || y == 0 || y == MAP_HEIGHT - 1)
                worldMap[x][y] = 1;
            else
                worldMap[x][y] = 0;
        }
    }

    // Add some walls to the map
    worldMap[6][6] = 1;
    worldMap[6][7] = 1;
    worldMap[6][8] = 1;
    worldMap[7][8] = 1;
    worldMap[8][8] = 1;
    worldMap[8][7] = 1;
    worldMap[8][6] = 1;
}

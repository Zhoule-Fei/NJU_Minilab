#ifndef LABYRINTH_H
#define LABYRINTH_H

/**
 * Labyrinth Game Backend
 * 
 * This header defines the core structures and shared function prototypes
 * for the stateless command-line game backend.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>

/* Constants based on lab requirements */
#define MAX_DIM 100
#define PLAYER_COUNT 10

/* Game state structure representing the maze */
typedef struct {
    char data[MAX_DIM][MAX_DIM]; // 2D grid for the map
    int rows;                    // Current height of the map
    int cols;                    // Current width of the map
} Map;

/* Directions for player movement */
typedef enum {
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_NONE
} Direction;

// map.c: File I/O and searching
bool load_map(const char *filename, Map *map);      // Reads map from disk
bool save_map(const char *filename, const Map *map); // Writes map back to disk
void find_player(const Map *map, char player_id, int *r, int *c); // Locates a player
bool find_first_empty(const Map *map, int *r, int *c);           // Finds the first '.'
void print_map(const Map *map);                                  // Outputs map to stdout

// logic.c: Core game rules and connectivity
bool is_connected(const Map *map);                        // BFS/DFS for traversability
bool apply_move(Map *map, char player_id, Direction dir); // Moves player in memory
bool place_player_if_missing(Map *map, char player_id);   // Spawns missing player

#endif // LABYRINTH_H

#include "labyrinth.h"

/**
 * Recursive helper for connectivity check.
 * Marks reachable non-wall cells starting from (r, c).
 */
static void flood_fill(const Map *map, bool visited[MAX_DIM][MAX_DIM], int r, int c) {
    // Bounds check and wall/visited check
    if (r < 0 || r >= map->rows || c < 0 || c >= map->cols) return;
    if (visited[r][c] || map->data[r][c] == '#') return;

    visited[r][c] = true;

    // Recurse in 4 directions
    flood_fill(map, visited, r + 1, c);
    flood_fill(map, visited, r - 1, c);
    flood_fill(map, visited, r, c + 1);
    flood_fill(map, visited, r, c - 1);
}

/**
 * Validates that all '.' and player positions '0-9' are connected.
 * Uses a simple flood fill algorithm.
 */
bool is_connected(const Map *map) {
    int start_r = -1, start_c = -1;
    int total_to_visit = 0;

    // Count non-wall cells and pick a starting point
    for (int i = 0; i < map->rows; i++) {
        for (int j = 0; j < map->cols; j++) {
            if (map->data[i][j] != '#') {
                total_to_visit++;
                if (start_r == -1) {
                    start_r = i;
                    start_c = j;
                }
            }
        }
    }

    // A map with no traversable spaces is technically connected
    if (total_to_visit == 0) return true;

    bool visited[MAX_DIM][MAX_DIM] = {0};
    flood_fill(map, visited, start_r, start_c);

    // Verify all traversable cells were reached
    int visited_count = 0;
    for (int i = 0; i < map->rows; i++) {
        for (int j = 0; j < map->cols; j++) {
            if (visited[i][j]) visited_count++;
        }
    }

    return visited_count == total_to_visit;
}

/**
 * Updates the Map by moving a player in the specified direction.
 * Movement is only allowed into '.' (empty space).
 */
bool apply_move(Map *map, char player_id, Direction dir) {
    int r, c;
    find_player(map, player_id, &r, &c);
    if (r == -1) return false; // Player must exist before moving

    int nr = r, nc = c;
    switch (dir) {
        case MOVE_UP:    nr--; break;
        case MOVE_DOWN:  nr++; break;
        case MOVE_LEFT:  nc--; break;
        case MOVE_RIGHT: nc++; break;
        default: return true; // No movement requested
    }

    // Collision and bounds detection
    if (nr < 0 || nr >= map->rows || nc < 0 || nc >= map->cols) return false;
    if (map->data[nr][nc] != '.') return false; // Can only move to empty space

    // Perform the swap
    map->data[r][c] = '.';
    map->data[nr][nc] = player_id;
    return true;
}

/**
 * Ensures a player is present on the map.
 * If not found, places them on the first available '.' cell.
 */
bool place_player_if_missing(Map *map, char player_id) {
    int r, c;
    find_player(map, player_id, &r, &c);
    if (r != -1) return true; // Already on map

    // Attempt to spawn on first '.'
    if (find_first_empty(map, &r, &c)) {
        map->data[r][c] = player_id;
        return true;
    }

    return false; // No space found to place the player
}

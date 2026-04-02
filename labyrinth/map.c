#include "labyrinth.h"

/**
 * Loads a maze from a text file into the Map structure.
 * Validates characters and dimensions (max 100x100).
 */
bool load_map(const char *filename, Map *map) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return false;

    map->rows = 0;
    map->cols = 0;
    char line[MAX_DIM + 5]; // Buffer allowing for newline

    while (fgets(line, sizeof(line), fp)) {
        size_t len = strlen(line);
        // Strip trailing newline character
        if (len > 0 && line[len - 1] == '\n') {
            line[--len] = '\0';
        }
        if (len == 0) continue; // Skip truly empty lines

        // Validate dimensions
        if (len > MAX_DIM || map->rows >= MAX_DIM) {
            fclose(fp);
            return false;
        }

        // Establish column count based on first non-empty line
        if (map->rows == 0) {
            map->cols = (int)len;
        } else if ((int)len != map->cols) {
            // All rows must have the same length for the connectivity check
            fclose(fp);
            return false;
        }

        // Validate and store map characters
        for (int j = 0; j < map->cols; j++) {
            char c = line[j];
            // Only wall, empty, or player ID are allowed
            if (c != '#' && c != '.' && !(c >= '0' && c <= '9')) {
                fclose(fp);
                return false;
            }
            map->data[map->rows][j] = c;
        }
        map->rows++;
    }

    fclose(fp);
    return map->rows > 0;
}

/**
 * Saves the current Map state back to a text file.
 */
bool save_map(const char *filename, const Map *map) {
    FILE *fp = fopen(filename, "w");
    if (!fp) return false;

    for (int i = 0; i < map->rows; i++) {
        for (int j = 0; j < map->cols; j++) {
            fputc(map->data[i][j], fp);
        }
        fputc('\n', fp);
    }

    fclose(fp);
    return true;
}

/**
 * Locates the row and column of a specific player ID.
 */
void find_player(const Map *map, char player_id, int *r, int *c) {
    *r = -1;
    *c = -1;
    for (int i = 0; i < map->rows; i++) {
        for (int j = 0; j < map->cols; j++) {
            if (map->data[i][j] == player_id) {
                *r = i;
                *c = j;
                return;
            }
        }
    }
}

/**
 * Searches the map from top-to-bottom, left-to-right for the first empty cell ('.').
 */
bool find_first_empty(const Map *map, int *r, int *c) {
    for (int i = 0; i < map->rows; i++) {
        for (int j = 0; j < map->cols; j++) {
            if (map->data[i][j] == '.') {
                *r = i;
                *c = j;
                return true;
            }
        }
    }
    return false;
}

/**
 * Outputs the map exactly as it should appear in the state file.
 */
void print_map(const Map *map) {
    for (int i = 0; i < map->rows; i++) {
        for (int j = 0; j < map->cols; j++) {
            putchar(map->data[i][j]);
        }
        putchar('\n');
    }
}

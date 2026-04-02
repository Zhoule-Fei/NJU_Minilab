#include "labyrinth.h"

/**
 * Displays the required version string for the lab.
 */
static void show_version() {
    printf("Labyrinth Game v1.0\n");
}

/**
 * Main entry point: Handles argument parsing and orchestrates the backend action.
 */
int main(int argc, char *argv[]) {
    // Define command line options
    static struct option long_options[] = {
        {"map",     required_argument, 0, 'm'},
        {"player",  required_argument, 0, 'p'},
        {"move",    required_argument, 0, 1001},
        {"version", no_argument,       0, 1002},
        {0, 0, 0, 0}
    };

    char *map_file = NULL;
    char player_id = -1;
    Direction dir = MOVE_NONE;
    bool version_flag = false;
    bool other_flags = false;

    // Parse arguments using getopt_long
    int opt;
    while ((opt = getopt_long(argc, argv, "m:p:", long_options, NULL)) != -1) {
        switch (opt) {
            case 'm': // --map
                map_file = optarg;
                other_flags = true;
                break;
            case 'p': // --player
                if (strlen(optarg) != 1 || optarg[0] < '0' || optarg[0] > '9') {
                    return EXIT_FAILURE; // Invalid player ID
                }
                player_id = optarg[0];
                other_flags = true;
                break;
            case 1001: // --move
                if (strcmp(optarg, "up") == 0) dir = MOVE_UP;
                else if (strcmp(optarg, "down") == 0) dir = MOVE_DOWN;
                else if (strcmp(optarg, "left") == 0) dir = MOVE_LEFT;
                else if (strcmp(optarg, "right") == 0) dir = MOVE_RIGHT;
                else return EXIT_FAILURE; // Invalid direction
                other_flags = true;
                break;
            case 1002: // --version
                version_flag = true;
                break;
            default:
                return EXIT_FAILURE;
        }
    }

    // Handle --version flag (cannot be mixed with other flags)
    if (version_flag) {
        if (other_flags) return EXIT_FAILURE;
        show_version();
        return EXIT_SUCCESS;
    }

    // Map file is mandatory for all other operations
    if (!map_file) return EXIT_FAILURE;

    Map map;
    // 1. Load the map state
    if (!load_map(map_file, &map)) return EXIT_FAILURE;

    // 2. Validate map connectivity before any action
    if (!is_connected(&map)) return EXIT_FAILURE;

    // 3. Handle player actions if a player ID is provided
    if (player_id != -1) {
        // Automatically place player on first empty space if not present
        if (!place_player_if_missing(&map, player_id)) {
            return EXIT_FAILURE; // No room for the player
        }

        if (dir != MOVE_NONE) {
            // Attempt to move player
            if (!apply_move(&map, player_id, dir)) {
                return EXIT_FAILURE; // Move blocked or invalid
            }
            // Save updated state after successful movement
            if (!save_map(map_file, &map)) return EXIT_FAILURE;
        } else {
            // VIEW ONLY: Save placement (if any) and print current map
            if (!save_map(map_file, &map)) return EXIT_FAILURE;
            print_map(&map);
        }
    } else {
        // Viewing without specified player: ensure no movement was attempted
        if (dir != MOVE_NONE) return EXIT_FAILURE;
        print_map(&map);
    }

    return EXIT_SUCCESS;
}

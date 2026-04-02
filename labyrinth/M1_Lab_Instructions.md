# M1: Labyrinth - Lab Instructions

## 1. Lab Goals and Background
*   **Goal:** Build a command-line "game backend" for a Rogue-like maze game.
*   **Objective:** Familiarize students with **UNIX command-line argument parsing**, basic file I/O, and standard tool conventions (like return codes).
*   **Background:** Inspired by the 1980 game *Rogue*. The system uses a **stateless backend** design: the program runs for a single action, updates the game state stored in a file, and then exits.

## 2. Specific Requirements for 'labyrinth'
*   **Map Loading:** Load a maze from a text file (max 100x100).
*   **Connectivity Check:** All empty spaces (`.`) and player positions (`0-9`) must be connected (reachable from one another).
*   **Player Management:** Identify players by ID (0-9).
*   **Movement Logic:** 
    *   Support directions: `up`, `down`, `left`, `right`.
    *   Players can only move to empty spaces (`.`), not walls (`#`) or positions occupied by other players.
    *   If a player ID is specified but not found on the map, the program must place them at the **first available empty space** (searching top-to-bottom, left-to-right).
*   **Version Info:** Display a version string containing "Labyrinth Game".

## 3. Vital Constraints
*   **Command-Line Arguments:**
    *   `-m` or `--map FILE`: Path to the map file.
    *   `-p` or `--player ID`: Player ID (0-9).
    *   `--move DIRECTION`: Movement direction.
    *   `--version`: Show version info.
*   **Return Codes (Crucial):**
    *   `0` (EXIT_SUCCESS): Successful execution.
    *   `1` (EXIT_FAILURE): Any error (invalid map, invalid ID, missing arguments, failed move, non-connected map, map too large, or mixing `--version` with other flags).
*   **Map Format:**
    *   `#`: Wall.
    *   `.`: Empty space.
    *   `0-9`: Player positions.
*   **Output:**
    *   When just viewing (`--map` and `--player`), print the map exactly as it appears in the file.
    *   `--version` must output a string containing "Labyrinth Game".

## 4. Testing and Submission Guidelines
*   **Soft Deadline:** March 23, 2025, 23:59:59.
*   **Code Acquisition:** Use `git pull origin M1` to get the framework.
*   **Submission:** Results are determined by the **Online Judge**.
*   **Testing:** A `testkit` is provided in the framework to help verify implementation before submission.
*   **AIGC Policy:** Use of AI for single API usage is allowed, but translating full natural language requirements into code is prohibited.

## 5. Tips and Hints
*   **Argument Parsing:** Use the `getopt_long()` function from `<getopt.h>` to handle both short (`-m`) and long (`--map`) options.
*   **Error Handling:** Major focus of the lab. Ensure the program handles missing files, incorrect formats, and invalid logic (like moving into a wall) by returning the correct error code (`1`).
*   **Connectivity:** Implement a check (e.g., BFS or DFS) to ensure the maze is fully traversable.
*   **Statelessness:** The program does not stay running; it performs one action and exits.

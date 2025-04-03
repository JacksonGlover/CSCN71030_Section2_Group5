#include "io.h"

/**
 * @brief The main function file, most logic is handled in the gameloop
 * @return the status code of the entire program
 */
int main(int argc, char**argv) {
    process_command_line_inputs(argc, argv);
    printf("Welcome to the Adventure Game!\n");
    srand(time(NULL));
    // Start game loop
    game_loop();

    return 0;
}
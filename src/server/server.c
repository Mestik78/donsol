#include "server.h"
#include "../game/game.h"

#include <stdio.h>
#include <stdlib.h>

int run_server() {
    printf("server running!\n");
    
    // create game
    struct GameState state;
    create_game(&state);
    print_state(&state);

    // while (game not finished)
    while (!state.finished) {
        //  game loop()
        game_loop(&state);
    }
    return 0;
}

#include "render.h"

#include <stdio.h>

void render_game(struct ClientGameState *state) {
    printf("\n---\n");
    printf("HP: %d\tRound: %d\n\n", state->health, state->round);

    for (int i = 0;i < MAX_ROOM_SIZE;i++) {
        if (state->room_state[i])
            print_card(&state->room[i]);
        else
            printf("-- ");
    }
    printf("\n\n");

    printf("> \n");
}

#include "render.h"

#include <stdio.h>

void render_game(struct ClientGameState *state) {
    printf("\033[2J\033[H"); // clear

    printf("\n---\n");
    printf("HP: %d\tRound: %d ", state->health, state->round);

    printf("Shield: ");
    if (state->shield_equipped)
        printf("%d", ShieldValues[state->shield.value]);
    else
        printf("none");

    printf("\n\n");

    for (int i = 0;i < MAX_ROOM_SIZE;i++) {
        if (state->room_state[i])
            print_card(&state->room[i]);
        else
            printf("-- ");
    }
    printf("\n");
    for (int i = 0;i < MAX_ROOM_SIZE;i++) {
        if (state->selected_card == i)
            printf("^  ");
        else
            printf("   ");
    }
    printf("\n\n");

    fflush(stdout);
}

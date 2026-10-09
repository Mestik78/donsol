#include "game.h"

#include <stdio.h>

void print_card(struct Card *card) {
    printf("%s%s", SuitIcons[card->suit], ValueNames[card->value]);
}
void print_client_state(struct ClientGameState *state) {
    printf("Discard Deck:\n");
    for (int i = 0;i < state->discard_deck_size;i++) {
        print_card(&state->discard_deck[i]);
        printf(" ");
    }
    printf("\n");

    printf("Finished: %d\n", state->finished);
    printf("Round: %d\n", state->round);
    printf("HP: %d\n", state->health);
    printf("Skip Token: %d\n", state->skip_token);
    printf("Shield: ");
    if (state->shield_equipped) {
        print_card(&state->shield);
        printf("\n");
    } else
        printf("none\n");

    printf("Room:\n");
    for (int i = 0;i < MAX_ROOM_SIZE;i++) {
        if (state->room_state[i])
            print_card(&state->room[i]);
        else
            printf("--");
        printf(" ");
    }
    printf("\n");
}

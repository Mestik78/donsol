#include "game.h"

#include <stdio.h>

void print_card(struct Card *card) {
    printf("%s%s", SuitIcons[card->suit], ValueNames[card->value]);
}

void print_state(struct GameState *state) {
    printf("Deck:\n");
    for (int i = 0;i < state->deck_size;i++) {
        print_card(&state->deck[i]);
        printf(" ");
    }
    printf("\n");

    printf("Discard Deck:\n");
    for (int i = 0;i < state->discard_deck_size;i++) {
        print_card(&state->discard_deck[i]);
        printf(" ");
    }
    printf("\n");

    printf("HP: %d\n", state->health);
    printf("Skip Token: %d\n", state->skip_token);

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

void create_deck(struct Card *deck) {
    for (enum Suit suit = 0; suit < 4; suit++) {
        for (int i = 0;i < 13;i++) {
            deck[suit*13+i].suit = suit;
            deck[suit*13+i].value = i;
        }
    }
    deck[52].suit = HEARTS;
    deck[52].value = 13;
    deck[53].suit = SPADES;
    deck[53].value = 13;
}
struct Card shuffle_deck(struct Card deck, int deck_size);

void create_game(struct GameState *state) {
    state->finished = false;
    state->health = 21;
    state->skip_token = true;
    state->shield = NULL;
    for (int i = 0;i < MAX_ROOM_SIZE;i++) {
        state->room_state[i] = false;
    }

    create_deck(state->deck);
    state->deck_size = DECK_SIZE;
}

void game_loop(struct GameState *state) {
    (void)state;
}


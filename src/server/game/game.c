#include "game.h"
#include "../../common/game/game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_server_state(struct ServerGameState *state) {
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
void shuffle_deck(struct Card *deck, int deck_size) {
    for (int i = deck_size - 1; i > 0; i--) {
        int j = rand() % (i + 1);

        struct Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

void init_server_game(struct ServerGameState *state) {
    init_common_game((struct CommonGameState *)state);
    create_deck(state->deck);
    shuffle_deck(state->deck, state->deck_size);
}

void server_to_common_game_state(struct ServerGameState *server, struct CommonGameState *message) {
    memcpy(message, server, sizeof(struct CommonGameState));
}

void enter_room(struct ServerGameState *state) {
    for (int i = 0;i < MAX_ROOM_SIZE;i++) {
        state->deck_size--;
        state->room[i] = state->deck[state->deck_size];
        state->room_state[i] = true;
    }
    state->active_cards = MAX_ROOM_SIZE;
}

void play_interaction(struct ServerGameState *state, struct PlayerInteraction *interaction) {
    state->room_state[interaction->selected_card] = false;
    state->active_cards--;
    if (!state->active_cards)
        enter_room(state);
}

#include "game.h"
#include "../../common/game/game.h"

#include <stdio.h>
#include <stdlib.h>

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

void create_game(struct ServerGameState *state) {
    state->finished = false;
    state->round = 0;
    state->health = 21;
    state->skip_token = true;
    state->shield_equipped = false;
    state->discard_deck_size = 0;
    for (int i = 0;i < MAX_ROOM_SIZE;i++) {
        state->room_state[i] = false;
    }

    create_deck(state->deck);
    state->deck_size = DECK_SIZE;
    
    shuffle_deck(state->deck, state->deck_size);
}

void server_to_client_game_state(struct ServerGameState *server, struct ClientGameState *client) {
    client->finished = server->finished;
    client->round = server->round;
    client->health = server->health;
    client->skip_token = server->skip_token;
    client->shield_equipped = server->shield_equipped;
    for (int i = 0;i < MAX_ROOM_SIZE;i++) {
        client->room_state[i] = server->room_state[i];
        client->room[i] = server->room[i];
    }
    client->deck_size = server->deck_size;
    client->discard_deck_size = server->discard_deck_size;
    for (int i = 0; i < server->discard_deck_size; i++) {
        client->discard_deck[i] = server->discard_deck[i];
    }
}

void enter_room(struct ServerGameState *state) {
    for (int i = 0;i < MAX_ROOM_SIZE;i++) {
        state->deck_size--;
        state->room[i] = state->deck[state->deck_size];
        state->room_state[i] = true;
    }
}

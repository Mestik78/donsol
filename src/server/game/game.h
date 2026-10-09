#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "../../common/game/game.h"

struct ServerGameState {
    bool finished;
    int round;

    struct Card deck[DECK_SIZE];
    int deck_size;
    
    struct Card room[MAX_ROOM_SIZE];
    bool room_state[MAX_ROOM_SIZE];
    
    struct Card discard_deck[DECK_SIZE];
    int discard_deck_size;

    int health;
    bool skip_token;
    bool shield_equipped;
    struct Card shield;
};

void create_game(struct ServerGameState *state);

void print_server_state(struct ServerGameState *state);

void server_to_client_game_state(struct ServerGameState *server, struct ClientGameState *client);

#endif

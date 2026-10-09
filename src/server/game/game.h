#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "../../common/game/game.h"

typedef struct ServerGameState {
    struct MessageGameState;

    struct Card deck[DECK_SIZE];
} ServerGameState;

void init_server_game(struct ServerGameState *state);
void enter_room(struct ServerGameState *state);

void print_server_state(struct ServerGameState *state);

void server_to_message_game_state(struct ServerGameState *server, struct MessageGameState *message);

void play_interaction(struct ServerGameState *state, struct PlayerInteraction *interaction);

#endif

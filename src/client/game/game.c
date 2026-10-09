#include "game.h"

#include <string.h>

void message_to_client_game_state(struct MessageGameState *message, struct ClientGameState *client) {
    memcpy(client, message, sizeof(struct MessageGameState));
}

void init_client_game(struct ClientGameState *state) {
    init_message_game((struct MessageGameState *)state);
    state->selected_card = 0;
}

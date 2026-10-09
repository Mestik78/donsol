#ifndef CLIENT_GAME_H
#define CLIENT_GAME_H

#include "../../common/game/game.h"

struct ClientGameState {
    struct MessageGameState;
    
    int selected_card;
};

void init_client_game(struct ClientGameState *state);
void message_to_client_game_state(struct MessageGameState *message, struct ClientGameState *client);

#endif

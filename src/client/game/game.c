#include "game.h"
#include "../io/io.h"
#include "../render/render.h"

#include <string.h>

void move(struct ClientGameState *state, int mov) {
    state->selected_card = (state->selected_card + mov) % MAX_ROOM_SIZE;
}


void message_to_client_game_state(struct CommonGameState *message, struct ClientGameState *client) {
    memcpy(client, message, sizeof(struct CommonGameState));
}

void init_client_game(struct ClientGameState *state) {
    init_common_game((struct CommonGameState *)state);
    state->selected_card = 0;
}

void play_round(struct ClientGameState *state, struct PlayerInteraction *interaction) {
    enum Key key;

    do {
        render_game(state);
        key = read_input();

        if (key == KEY_LEFT)
            move(state, -1);
        else if (key == KEY_RIGHT)
            move(state, 1);
        
    } while (key != KEY_ENTER);

    interaction->selected_card = state->selected_card;
}

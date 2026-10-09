#ifndef COMMON_GAME_H
#define COMMON_GAME_H

#define DECK_SIZE       54
#define MAX_ROOM_SIZE   4

enum Suit {
    CLUBS, DIAMONDS, HEARTS, SPADES
};
static const char *SuitIcons[] = {"♣", "♦", "♥", "♠"};
static const char *ValueNames[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "Joker"};

struct Card {
    enum Suit suit;
    int value;
};

struct ClientGameState {
    bool finished;
    int round;

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

void print_card(struct Card *card);
void print_client_state(struct ClientGameState *state);

#endif

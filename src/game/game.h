#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

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

struct GameState {
    bool finished;

    struct Card deck[DECK_SIZE];
    int deck_size;
    
    struct Card room[MAX_ROOM_SIZE];
    bool room_state[MAX_ROOM_SIZE];
    
    struct Card discard_deck[DECK_SIZE];
    int discard_deck_size;

    bool skip_token;
    
    int health;
    struct Card shield;
};

void create_game(struct GameState *state);

void print_state(struct GameState *state);

void game_loop(struct GameState *state);

#endif

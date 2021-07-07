#pragma once

#include "team.h"
#include "mine.h"
#include "lobby.h"
#include "qdebug.h"

class Game {
public:
    unsigned long long id;
    int day;
    int team_number;
    Team teams[MAX_TEAM_OF_GAME];
    Mine mines[MAX_MINE_OF_GAME];
    Castle castles[MAX_CASTLE_OF_GAME];

    Game();
    Game(unsigned long long id, int team_number, Player* players, int player_size);
    void init_game(unsigned long long id, int team_number, Player* players, int player_number);
    void update_timely_response(char* payload);
    void update_game_response(char * payload, Lobby& lobby, Player& player);

    bool rank_sort(int t1, int t2 );
};

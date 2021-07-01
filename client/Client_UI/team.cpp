#include "team.h"

Team::Team() {

}
Team::Team(int id) :id{ id } {
    this->castle_number = 0;
    player_number = 0;
    this->wood = 0;
    this->stone = 0;
    this->iron = 0;
    this->gold = 0;
}

Team::Team(int id, Player* players, int player_size) : id{ id }, player_number{ player_size } {
    player_number = 0;
    for (int i = 0; i < player_size; i++) {
        this->players[i] = players[i];
    }
}

void Team::add_player(Player player) {
    players[this->player_number] = player;
    this->player_number++;
}

void Team::add_castle(Castle castle) {
    castles[this->castle_number] = castle;
    this->castle_number++;
}

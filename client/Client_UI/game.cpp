#include "game.h"
#include "response.h"
#include "util.h"
#include <algorithm>
#include "uitranslate.h"

Game::Game(){

}

Game::Game(unsigned long long id, int team_number, Player* players, int player_number){
    init_game(id, team_number, players, player_number);
}

void Game::init_game(unsigned long long id, int team_number, Player* players, int player_number) {
    this->id = id;
    this->team_number = team_number;
    this->day = 0;
    for (int i = 0; i < this->team_number; i++) {
        teams[i] = Team(i);
    }

    for (int i = 0; i < player_number; i++) {
        int team_id = players[i].team_id;
        teams[team_id].add_player(players[i]);
    }

    for (int i = 0; i < MAX_MINE_OF_GAME; i++) {
        int type = i / 2;
        mines[i] = Mine(i, type);
    }

    for (int i = 0; i < MAX_CASTLE_OF_GAME; i++) {
        castles[i] = Castle(i);
    }
}


void Game::update_timely_response(char* payload) {
    Update_timely response = update_timely_data(payload);
    for (int i = 0; i < MAX_CASTLE_OF_GAME; i++) {
        this->castles[i].occupied_by = response.occupied[i];
        this->castles[i].wall = get_wall(response.wall_type[i]);
        this->castles[i].wall.defense = response.wall_def[i];
    }

    for (int i = 0; i < MAX_MINE_OF_GAME; i++) {
        this->mines[i].wood = response.wood_mine[i];
        this->mines[i].stone = response.stone_mine[i];
        this->mines[i].iron = response.iron_mine[i];
    }

    for (int i = 0; i < team_number; i++) {
        this->teams[i].weapon = get_weapon(response.weapon_type[i]);
        this->teams[i].weapon.attack = response.weapon_atk[i];
        this->teams[i].gold = response.gold_team[i];
        this->teams[i].wood = response.wood_team[i];
        this->teams[i].stone = response.stone_team[i];
        this->teams[i].iron = response.iron_team[i];
    }

}

void Game::update_game_response(char* payload, Lobby& lobby, Player& player) {
    //Update_game response = update_game_data(payload);
    char result_code[RESULT_CODE_SIZE+1];
    strncpy_s(result_code,payload, RESULT_CODE_SIZE);
    //if (!strcmp(response.result_code, UPDATE_GAME_START)) {
    if (!strcmp(result_code, UPDATE_GAME_START)) {
        this->init_game(lobby.id, lobby.team_number, lobby.players, lobby.player_number);
        qDebug() << "Initialized game" ;
    }
    else if (!strcmp(result_code, UPDATE_GAME_CSTQUEST)) {
        Update_castle_ques res = update_castle_ques_data(payload);
        this->castles[res.castle_id].question = Question(res.question_id, res.question, res.answer1, res.answer2, res.answer3, res.answer4);
        //qDebug() << "Update_castle_ques result: (res.id) " << res.castle_id ;
        //qDebug() << "Update_castle_ques result: (res.question) " << res.question ;
    }
    else if (!strcmp(result_code, UPDATE_GAME_MINEQUEST)) {
        Update_mine_ques res = update_mine_ques_data(payload);
        this->mines[res.mine_id].question[res.type] = Question(res.question_id, res.question, res.answer1, res.answer2, res.answer3, res.answer4);
        //qDebug() << "Update_mine_ques result: (res.id) " << res.mine_id ;
        //qDebug() << "Update_mine_ques result: (res.question id ) " << res.question_id ;
    }
    else if (!strcmp(result_code, UPDATE_GAME_ATK_CST_W) || !strcmp(result_code, UPDATE_GAME_ATK_CST_R)) {
        Update_castle_attack res = update_castle_attack_data(payload);
        int castle_id = res.castle_id;
        int player_id = res.player_id;
        int team_id = res.team_id;
        Castle& castle = this->castles[castle_id];
        Team& team = this->teams[team_id];

        // answer wrong
        if (!strcmp(result_code, UPDATE_GAME_ATK_CST_W)) {
            if (player_id != player.id) {
                QMessageBox::information(nullptr,"Game Notice","Player ID " + QString::number(player_id) +
                                        + " of TEAM " +  QString::number(team_id+1) + " attacked castle "
                                        + QString::number(castle_id+1) + " with a wrong answer !" ,0);
            } else {
                QMessageBox::information(nullptr,"Attack Result","Wrong answer! Failed to attack this castle!",0);
            }
        }
        // answer right
        else {
            // Announce to players in game
            //Logic handle
            if (castle.occupied_by != team_id){
                // Somebody take over the castle
                if (player_id != player.id) {
                    QMessageBox::information(nullptr,"Notice","Player ID " + QString::number(player_id) +
                                            + " of TEAM " +  QString::number(team_id+1) + " attacked castle ["
                                            + QString::number(castle_id+1) + "] successfully! Congratulations!" ,0);
                }
                else {
                    QMessageBox::information(nullptr,"Notice","Attacked successfully ! Welcome to castle ["
                                            + QString::number(castle_id+1) + "]" ,0);
                }
            } else {
                // Nothing changes
                if (player_id != player.id) {
                    QMessageBox::information(nullptr,"Notice","Player ID " + QString::number(player_id) +
                                            + " of TEAM " +  QString::number(team_id+1) + " attacked castle ["
                                            + QString::number(castle_id+1) + "] success but cant take down the castle" ,0);
                }
                else {
                    QMessageBox::information(nullptr,"Notice","Attacked success but you cant take down the castle ["
                                            + QString::number(castle_id+1) + "]",0);
                }
            }
            castle.occupied_by = team_id;
            castle.wall = get_wall(res.wall_type_id);
            castle.wall.defense = res.wall_def;

            team.add_castle(castle);
            team.weapon = get_weapon(res.weapon_type_id);
            team.weapon.attack = res.weapon_atk;
        }

        castle.question = Question(res.question_id, res.question, res.answer1, res.answer2, res.answer3, res.answer4);
    }
    else if (!strcmp(result_code, UPDATE_GAME_ATK_MINE_W) || !strcmp(result_code, UPDATE_GAME_ATK_MINE_R)) {
        Update_mine_attack res = update_mine_attack_data(payload);
        int mine_id = res.mine_id;
        int player_id = res.player_id;
        int team_id = res.team_id;
        Mine& mine = this->mines[mine_id];
        Team& team = this->teams[team_id];
        if (!strcmp(result_code, UPDATE_GAME_ATK_MINE_R)) {
            QMessageBox::information(nullptr,"Game Notice","Player ID " + QString::number(player_id) +
                                    + " of TEAM " +  QString::number(team_id+1) + " attacked castle "
                                    + QString::number(mine_id+1) + " successfully!" ,0);
            //Add resource
            switch (res.type) {
                case WOOD:
                    team.wood += mine.wood;
                    mine.wood = 0;
                    break;
                case STONE:
                    team.stone += mine.stone;
                    mine.stone = 0;
                    break;
                case IRON:
                    team.iron += mine.iron;
                    mine.iron = 0;
                    break;
            }
        } else {
            QMessageBox::information(nullptr,"Game Notice","Player ID " + QString::number(player_id) +
                                    + " of TEAM " +  QString::number(team_id+1) + " attacked castle "
                                    + QString::number(mine_id+1) + " but failed!" ,0);
        }

        mine.question[res.type] = Question(res.question_id, res.question, res.answer1, res.answer2, res.answer3, res.answer4);
    }
    else if (!strcmp(result_code, UPDATE_GAME_BUY_WPN)) {
        Update_buy_weapon res = update_buy_weapon_data(payload);
        if (player.id != res.player_id) {
            QMessageBox::information(nullptr,"Notice","Player ID " + QString::number(res.player_id)
                          + " of Team" + QString::number(res.team_id + 1) + " has bought "
                          + getWeaponName(res.weapon_type_id) + " successfully!",0);
        } else {
            QMessageBox::information(nullptr,"Congratulations", getWeaponName(res.weapon_type_id) + " bought successfully!");
        }
        Team& team = this->teams[res.team_id];
        team.weapon = get_weapon(res.weapon_type_id);
        team.wood -= team.weapon.wood;
        team.stone -= team.weapon.stone;
        team.iron -= team.weapon.iron;
    }
    else if (!strcmp(result_code, UPDATE_GAME_BUY_WALL)) {
        Update_buy_wall res = update_buy_wall_data(payload);
        if (player.id != res.player_id) {
            QMessageBox::information(nullptr,"Notice","Player ID " + QString::number(res.player_id)
                          + " of Team" + QString::number(res.team_id + 1) + " has build a " + getWallName(res.wall_type_id)
                          + " successfully for castle #" + QString::number(res.castle_id+1),0);
        } else {
            QMessageBox::information(nullptr,"Congratulations","Built " + getWallName(res.wall_type_id)
                                    + "for Castle " + QString::number(res.castle_id+1) + " successfully!",0);
        }

        Team& team = this->teams[res.team_id];
        Castle& castle = this->castles[res.castle_id];
        team.wall = get_wall(res.wall_type_id);
        castle.wall = get_wall(res.wall_type_id);
        team.wood -= team.wall.wood;
        team.stone -= team.wall.stone;
        team.iron -= team.wall.iron;
    }
    else if (!strcmp(result_code, UPDATE_GAME_CHEAT)) {
        Update_cheat res = update_cheat_data(payload);

        if (player.id == res.request_player_id){
            QMessageBox::information(nullptr,"Congratulations","You have cheated successfully",0);
        } else {
            QMessageBox::information(nullptr,"Notice","Player ID " + QString::number(res.request_player_id)
                          + " of Team" + QString::number(res.team_id + 1) + " has cheated successfully!",0);
        }
        this->teams[res.team_id].wood += CHEAT_AMOUNT;
        this->teams[res.team_id].stone += CHEAT_AMOUNT;
        this->teams[res.team_id].iron += CHEAT_AMOUNT;
    }
    /*
    else if (!strcmp(result_code, UPDATE_GAME_OVER)) {
        printf("It's over baby");	// Show end game UI
        std::sort(this->teams, this->teams + this->team_number, rank_sort);		// Rank each team, the first team is the best, last team is the worst
        // Switch to lobby view
    }
    */
}

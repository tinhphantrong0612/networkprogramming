#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "stream.h"
#include "util.h"

Player::Player() : id{ MAX_NUM_PLAYER}, team_id{ 0 }, state{ UNREADY } {
    strcpy_s(username, USERNAME_LEN, DEFAULT_USRNAME);
};

Player::Player(int id, char* username, int team_id, int state) : id{ id }, team_id{ team_id }, state{ state } {
    strcpy_s(this->username, USERNAME_LEN, username);
}

Player::~Player() {

}

void Player::ready_request(Socket& socket) {
    socket.tcp_send((char*)READY_PLAY, (char*)"");
}

void Player::ready_response(char* payload) {
    Ready response = ready_data(payload);
    if (!strcmp(response.result_code, READY_SUCCESS)) {
        this->state = READY;
    }
    else if (!strcmp(response.result_code, READY_E_ALREADY)) {
        QMessageBox::information(nullptr,"Error","You are ready already!",0);
    }
    else if (!strcmp(response.result_code, READY_E_HOST)) {
        QMessageBox::information(nullptr,"Error","You're host!",0);
    }
    else {
        QMessageBox::information(nullptr,"Error","Invalid operation !",0);
    }

}

void Player::unready_request(Socket& socket) {
    socket.tcp_send((char*)UNREADY_PLAY, (char*)"");
}

void Player::unready_response(char* payload) {
    Unready response = unready_data(payload);
    if (!strcmp(response.result_code, UNREADY_SUCCESS)) {
        this->state = UNREADY;
    }
    else if (!strcmp(response.result_code, UNREADY_E_ALREADY)) {
        QMessageBox::information(nullptr,"Error","You are unready already!",0);
    }
    else if (!strcmp(response.result_code, UNREADY_E_HOST)) {
        QMessageBox::information(nullptr,"Error","You're host!",0);
    }
    else {
        QMessageBox::information(nullptr,"Error","Invalid operation !",0);
    }
}

void Player::change_team_request(Socket& socket, int team_id) {
    // Send team id
    char team_id_str[2];
    _itoa_s(team_id, team_id_str, 2, 10);
    socket.tcp_send((char*)CHANGE_TEAM, team_id_str);
}

// Input param: payload, team_id
void Player::change_team_response(char* payload, int decisionTeamChange) {
    //Player player;
    Change_team response = change_team_data(payload);
    if (!strcmp(response.result_code, UPDATE_LOBBY_CHANGETEAM)) {
        qDebug() << "Somebody change_team";
        this->team_id = decisionTeamChange;
    }
    else if (!strcmp(response.result_code, CHANGE_E_CURRENTTEAM)) {
        QMessageBox::information(nullptr,"Error","Already in this team!",0);
    }
    else if (!strcmp(response.result_code, CHANGE_E_FULL)) {
        QMessageBox::information(nullptr,"Error","This team is full!",0);
    }
    else if (!strcmp(response.result_code, CHANGE_E_READY)) {
        QMessageBox::information(nullptr,"Error","Unready to change team!",0);
    }
    else if (!strcmp(response.result_code, CHANGE_E_UNKNOWNTEAM)) {
        QMessageBox::information(nullptr,"Error","Invalid decision team",0);
    }
    else {
        QMessageBox::information(nullptr,"Error","Invalid operation",0);
    }
}

void Player::attack_castle_request(Socket& socket, int castle_id, int question_id, int answer_id) {
    // Cast int to string
    char payload[PAYLOAD_SIZE + 1] = "";
    char castle_id_str[CASTLE_ID_SIZE + 1];
    char question_id_str[QUESTION_ID_SIZE + 1];
    char answer_id_str[ANSWER_ID_SIZE + 1];
    _itoa_s(castle_id, castle_id_str, CASTLE_ID_SIZE + 1, 10);
    _itoa_s(question_id, question_id_str, QUESTION_ID_SIZE + 1, 10);
    _itoa_s(answer_id, answer_id_str, ANSWER_ID_SIZE + 1, 10);

    attack_castle_payload(castle_id_str, question_id_str, answer_id_str, payload);

    socket.tcp_send((char*)ATTACK_CASTLE, payload);
}

void Player::attack_castle_response(char* payload) {
    Attack_castle response = attack_castle_data(payload);
    if (!strcmp(response.result_code, ATK_CST_SUCCESS)) {
        // Do nothing cause this won't happen
    }
    else if (!strcmp(response.result_code, ATK_CST_E_TOOLATE)) {
        QMessageBox::information(nullptr,"Error","Attack castle too late! Question has changed",0);
    }
    else if (!strcmp(response.result_code, ATK_CST_E_WRONG)) {
        QMessageBox::information(nullptr,"Error","Your answer was wrong, now get the punishment, hahaha!",0);
    }
    else if (!strcmp(response.result_code, ATK_CST_E_TOOWEAK)) {
        QMessageBox::information(nullptr,"Error","Enermy has a stronger wall, go farm and get a stronger weapon you fool",0);
    }
    else if (!strcmp(response.result_code, ATK_CST_E_YOURS)) {
        QMessageBox::information(nullptr,"Error","This castle is already yours",0);
    }
    else {
        QMessageBox::information(nullptr,"Error","Invalid Operation!",0);
    }
}

void Player::attack_mine_request(Socket& socket, int mine_id, int type, int question_id, int answer_id) {
    // Cast int to string
    char payload[PAYLOAD_SIZE + 1] = "";
    char mine_id_str[MINE_ID_SIZE + 1];
    char type_str[TYPE_SIZE + 1];
    char question_id_str[QUESTION_ID_SIZE + 1];
    char answer_id_str[ANSWER_ID_SIZE + 1];
    _itoa_s(mine_id, mine_id_str, MINE_ID_SIZE + 1, 10);
    _itoa_s(type, type_str, TYPE_SIZE + 1, 10);
    _itoa_s(question_id, question_id_str, QUESTION_ID_SIZE + 1, 10);
    _itoa_s(answer_id, answer_id_str, ANSWER_ID_SIZE + 1, 10);

    attack_mine_payload(mine_id_str, type_str, question_id_str, answer_id_str, payload);

    socket.tcp_send((char*)ATTACK_MINE, payload);
}

void Player::attack_mine_response(char* payload) {
    Attack_mine response = attack_mine_data(payload);
    if (!strcmp(response.result_code, ATK_MINE_SUCCESS)) {
        // Do nothing cause this won't happen
    }
    else if (!strcmp(response.result_code, ATK_MINE_E_TOOLATE)) {
        QMessageBox::information(nullptr,"Error","Attack mine too late! Question has changed",0);	// This line replace by UI notification
    }
    else if (!strcmp(response.result_code, ATK_CST_E_WRONG)) {
        QMessageBox::information(nullptr,"Error","Your answer was wrong, go with empty hand, hahaha",0);
    }
    else {
        QMessageBox::information(nullptr,"Error","Invalid Operation",0);
    }
}

void Player::buy_weapon_request(Socket& socket, int weapon_id) {
    char payload[PAYLOAD_SIZE + 1] = "";
    char weapon_id_str[WEAPON_ID_SIZE + 1];
    _itoa_s(weapon_id, weapon_id_str, WEAPON_ID_SIZE + 1, 10);
    strcpy_s(payload, PAYLOAD_SIZE + 1, weapon_id_str);
    socket.tcp_send((char*)BUY_WEAPON, payload);
}

void Player::buy_weapon_response(char* payload) {
    Buy_weapon response = buy_weapon_data(payload);
    if (!strcmp(response.result_code, BUY_WEAPON_SUCCESS)) {
        // Do nothing cause this won't happen
    }
    else if (!strcmp(response.result_code, BUY_WEAPON_E_NOTENOUGH)) {
        QMessageBox::information(nullptr,"Error","Dont have enough resource, go farming",0);
    }
    else if (!strcmp(response.result_code, BUY_WEAPON_E_WEAKER)) {
        QMessageBox::information(nullptr,"Error","You already have a stronger weapon! What's wrong with you?",0);
    }
    else {
        QMessageBox::information(nullptr,"Error","Invalid Operation " + QString::fromLocal8Bit(payload),0);
    }
}

void Player::buy_wall_request(Socket& socket, int wall_id, int castle_id) {
    char payload[PAYLOAD_SIZE + 1] = "";
    char wall_id_str[WALL_ID_SIZE + 1], castle_id_str[CASTLE_ID_SIZE + 1];
    _itoa_s(castle_id, castle_id_str, WALL_ID_SIZE + 1, 10);
    _itoa_s(wall_id, wall_id_str, WALL_ID_SIZE + 1, 10);
    strcat_s(payload, PAYLOAD_SIZE + 1, castle_id_str);
    strcat_s(payload, PAYLOAD_SIZE + 1, DELIM_REQ_RES);
    strcat_s(payload, PAYLOAD_SIZE + 1, wall_id_str);
    socket.tcp_send((char*)BUY_WALL, payload);
}

void Player::buy_wall_response(char* payload) {
    Buy_wall response = buy_wall_data(payload);
    if (!strcmp(response.result_code, BUY_WALL_SUCCESS)) {
        // Do nothing
    }
    else if (!strcmp(response.result_code, BUY_WALL_E_NOTENOUGH)) {
        QMessageBox::information(nullptr,"Error","Not enough resource to buy this wall",0);
    }
    else if (!strcmp(response.result_code, BUY_WALL_E_WEAKER)) {
        QMessageBox::information(nullptr,"Error","You're already have a stronger wall, use it",0);
    }
    else if (!strcmp(response.result_code, BUY_WALL_E_GONE)) {
        QMessageBox::information(nullptr,"Error","Your team haven't occupied any castle",0);
    }
    else {
        QMessageBox::information(nullptr,"Error","Invalid Operation",0);
    }
}

void Player::cheat_request(Socket& socket){
    socket.tcp_send((char*)CHEAT, (char*)"");
}

void Player::cheat_response(char* payload) {
    Cheat response = cheat_data(payload);
    if (!strcmp(response.result_code, CHEAT_SUCCESS)) {
    }
    else {
        QMessageBox::information(nullptr,"Error","Cheat failed!",0);
    }
}

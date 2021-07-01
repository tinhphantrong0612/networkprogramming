#include "lobby.h"
#include "response.h"
#include "util.h"

Lobby::Lobby() :id{ 0 }, host{ 0 }, team_number{ 0 }, player_number{ 0 }, state{EMPTY} {
    for (int i = 0; i < MAX_NUM_PLAYER; i++) {
        team_players[i] = MAX_TEAM_OF_GAME;
    }
    for (int i = 0; i < MAX_NUM_PLAYER; i++) {
        players[i] = Player();
    }
}

Lobby::Lobby(unsigned long long id, int team_number) : id{ id }, team_number{ team_number } {

}

Lobby::Lobby(unsigned long long id) : id{ id } {

}

Lobby::~Lobby() {

}

// All request param is input

void Lobby::create_lobby_request(Socket& socket, int team_number) {
    // Send create lobby request
    char teamnum_str[TEAM_NUM_SIZE + 1];
    _itoa_s(team_number, teamnum_str, TEAM_NUM_SIZE + 1, 10);
    socket.tcp_send((char*)CREATE_LOBBY, teamnum_str);
}
// Input param: payload, username
Player Lobby::create_lobby_response(char* payload, char* username) {
    Create_lobby response = create_lobby_data(payload);
    if (!strcmp(response.result_code, CREATE_SUCCESS)){
        QMessageBox::information(nullptr,"Success","Create successful!",0);
        this->id = response.id;
        this->team_number = team_number;
        this->state = WAITING;
        return Player(0, username, 0, UNREADY);
    }
    else if (!strcmp(response.result_code, CREATE_E_INVALIDTEAM)) {
        QMessageBox::information(nullptr,"Error","Number of teams exceed",0);
    }
    else {
        QMessageBox::information(nullptr,"Error","Invalid operation!",0);
    }
    return Player();
}

void Lobby::get_lobby_request(Socket& socket) {
    socket.tcp_send((char*)GET_LOBBY, (char*)"");
}

// Input is payload
// Output is lobbies and size of the lobby
void Lobby::get_lobby_response(char* payload, Lobby* lobbies, int& size) {
    //Receive lobby request
    Get_lobby response = get_lobby_data(payload);
    if (!strcmp(response.result_code, LOBBY_SUCCESS)) {
        size = response.size;
        for (int i = 0; i < response.size; i++) {
            lobbies[i] = response.lobbies[i];
        }
    }
    else {
        QMessageBox::information(nullptr,"Error","Error occured while getting room list!",0);
    }
}

void Lobby::join_lobby_request(Socket& socket, unsigned long long game_id, int team_id) {
    char game_id_str[GAME_ID_SIZE + 1];
    char team_id_str[TEAM_ID_SIZE + 1];
    _i64toa_s(game_id, game_id_str, GAME_ID_SIZE + 1, 10);
    _itoa_s(team_id, team_id_str, TEAM_ID_SIZE + 1, 10);

    char payload[PAYLOAD_SIZE + 1] = "";
    join_lobby_payload(game_id_str, team_id_str, payload);
    socket.tcp_send((char*)JOIN_LOBBY, payload);
    this->id = game_id;
}

// Input param: payload, username, team_id and team_number from the lobby list
Player Lobby::join_lobby_response(char* payload, char* username, int& team_id, int& team_number) {
    //Receive lobby request
    Join_lobby response = join_lobby_data(payload);
    if (!strcmp(response.result_code, JOIN_SUCCESS)) {
        QMessageBox::information(nullptr,"Success","Joined! Your ID: " + QString::number(response.player_id),0);
        this->team_number = team_number;
        return Player(response.player_id, username, team_id, UNREADY);
    }
    else if (!strcmp(response.result_code, JOIN_E_FORMAT)
        || !strcmp(response.result_code, JOIN_E_NOGAME)
        || !strcmp(response.result_code, JOIN_E_NOTEAM)) {
        QMessageBox::information(nullptr,"Error","Error occured while joining lobby!",0);
    }
    else if (!strcmp(response.result_code, JOIN_E_PLAYING) || !strcmp(response.result_code, JOIN_E_FULLTEAM)) {
        QMessageBox::information(nullptr,"Error","Error occured while joining lobby!",0);
    }
    else {
        QMessageBox::information(nullptr,"Error","Invalid operation",0);
    }
    return Player();
}

void Lobby::start_game_request(Socket& socket) {
    socket.tcp_send((char*)START_GAME, (char*)"");
}

void Lobby::start_game_response(char* payload) {
    Start_game response = start_game_data(payload);

    if (!strcmp(response.result_code, UPDATE_GAME_START)) {
        this->state = INGAME;
    }
    else if (!strcmp(response.result_code, START_E_NOTHOST)) {
        QMessageBox::information(nullptr,"Error","Only host can start the game! ",0);
    }
    else if (!strcmp(response.result_code, START_E_ONETEAM)) {
        QMessageBox::information(nullptr,"Error","Only one team can't play the game! ",0);
    }
    else if (!strcmp(response.result_code, START_E_NOTALLREADY)) {
        QMessageBox::information(nullptr,"Error","All player must ready before the game starts!",0);
    }
    else {
        QMessageBox::information(nullptr,"Error","Error when start the game !",0);
    }
}

void Lobby::quit_lobby_request(Socket& socket) {
    socket.tcp_send((char*)QUIT_LOBBY, (char*)"");
}

int Lobby::quit_lobby_response(char* payload) {
    Quit_lobby response = quit_lobby_data(payload);
    if (!strcmp(response.result_code, QUIT_SUCCESS)) {
        return 1;
    }
    else if (!strcmp(response.result_code, QUIT_E_READY)) {
       QMessageBox::information(nullptr,"Error","Unready before quitting room!",0);
    }
    else {
        QMessageBox::information(nullptr,"Error","Invalid Operation!",0);
    }
    return 0;
}

void Lobby::kick_request(Socket& socket, int player_id) {
    char payload[PAYLOAD_SIZE + 1] = "";
    char player_id_str[PLAYER_ID_SIZE + 1];
    _itoa_s(player_id, player_id_str, PLAYER_ID_SIZE + 1, 10);
    strcat_s(payload, PAYLOAD_SIZE, player_id_str);
    socket.tcp_send((char*)KICK, payload);
}

void Lobby::kick_response(char* payload, int player_id) {
    Kick response = kick_data(payload);
    if (!strcmp(response.result_code, KICK_E_NOTHOST)) {
        QMessageBox::information(nullptr,"Error","Only host can kick!",0);
    }
    else if (!strcmp(response.result_code, KICK_E_YOURSELF)) {
        QMessageBox::information(nullptr,"Error","You can't kick yourself :D",0);
    }
    else {
        QMessageBox::information(nullptr,"Error","Invalid Operation!",0);
    }
}

void Lobby::update_lobby_response(char* payload) {
    Update_lobby response = update_lobby_data(payload);
    this->team_number = response.team_number;
    this->player_number = response.player_number;
    this->host = response.host;

    for (int i = 0; i < response.player_number; i++) {
        this->players[i] = response.players[i];
    }
}

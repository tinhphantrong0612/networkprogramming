#pragma once

//Buffer size
#define PAYLOAD_SIZE 2048
#define BUFF_SIZE 32000
#define PAYLOAD_LEN_SIZE 3
#define CODE_SIZE 3

#define TEAM_NUMBER_SIZE 2
#define USERNAME_LEN 256
#define ERROR_MESS_LEN 1024
#define NAME_LENGTH 256
#define QUESTION_LENGTH 256
#define ANSWER_LENGTH 256

// Boundery
#define MAX_NUM_PLAYER 13	// for lobby play size
#define MAX_LOBBY 100		// for get lobbies arr
#define TEAM_PLAYER_NUM_STR 13	// for decode get lobby str

// default value
#define DEFAULT_PORT 5500
#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_USRNAME ""
#define DELIM_RESPONSE " "


// RESPONSE CODE

// Login
#define LOGIN_SUCCESS "010"
#define LOGIN_E_ALREADY "011"
#define LOGIN_E_ELSEWHERE "012"
#define LOGIN_E_PASSWORD "013"
#define LOGIN_E_NOTEXIST "014"

// Signup
#define SIGNUP_SUCCESS "020"
#define SIGNUP_E_LOGGEDIN "021"
#define SIGNUP_E_FORMAT "022"
#define SIGNUP_E_EXIST "023"

// Create lobby
#define CREATE_SUCCESS "030"
#define CREATE_E_NOTAUTH "031"
#define CREATE_E_INGAME "032"
#define CREATE_E_FULLGAME "033"
#define CREATE_E_INVALIDTEAM "034"

// Get lobby
#define LOBBY_SUCCESS "040"
#define LOBBY_E_NOTAUTH "041

// Join Lobby
#define JOIN_SUCCESS "050"
#define JOIN_E_NOTAUTH "051"
#define JOIN_E_FULL "052"
#define JOIN_E_ALREADY "053"

// Change team
#define CHANGE_SUCCESS "060"
#define CHANGE_E_NOTAUTH "061"
#define CHANGE_E_NOTINGAME "062"
#define CHANGE_E_FULL "063"
#define CHANGE_E_READY "064"
#define CHANGE_E_PLAYING "065"

// Ready for game
#define READY_SUCCESS "070"
#define READY_E_NOTAUTH "071"
#define READY_E_NOTINGAME "072"
#define READY_E_ALREADY "073"
#define READY_E_PLAYING "074"
#define READY_E_HOST "075"

// Unready for game
#define UNREADY_SUCCESS "080"
#define UNREADY_E_NOTAUTH "081"
#define UNREADY_E_NOTINGAME "082"
#define UNREADY_E_ALREADY "083"
#define UNREADY_E_PLAYING "084"
#define UNREADY_E_HOST "085"

// Quit lobby
#define QUIT_SUCCESS "090"
#define QUIT_E_NOTAUTH "091"
#define QUIT_E_NOTINGAME "092"
#define QUIT_E_READY "093"

// Start game
#define START_SUCCESS "100"
#define START_E_NOTAUTH "101"
#define START_E_NOTINGAME "102"
#define START_E_NOTALLREADY "103"
#define START_E_PLAYING "104"
#define START_E_NOTHOST "105"

// Logout
#define LOGOUT_SUCCESS "110"
#define LOGOUT_E_NOTAUTH "111"
#define LOGOUT_E_INGAME "112"

// Attack castle
#define ATK_CST_SUCCESS "120"
#define ATK_CST_E_TOOLATE "121" // Answer the question too late
#define ATK_CST_E_TOOWEAK "122" // Enemy build a better wall
#define ATK_CST_E_YOURS "123"	// Your castle
#define ATK_CST_E_NOTPLAYING "124"

// Attack mine
#define ATK_MINE_SUCCESS "130"
#define ATK_MINE_E_TOOLATE "131"	// Answer the question too late
#define ATK_MINE_E_NOTPLAYING "132"

// Buy weapon
#define BUY_WEAPON_SUCCESS "140"
#define BUY_WEAPON_E_NOTENOUGH "141"	// Not enough resources
#define BUY_WEAPON_E_WEAKER "142"		// Can't buy a weaker weapon
#define BUY_WEAPON_E_NOTPLAYING "143"

// Buy wall
#define BUY_WALL_SUCCESS "150"
#define BUY_WALL_E_NOTENOUGH "151"
#define BUY_WALL_E_WEAKER "152"		// Can't by weaker wall
#define BUY_WALL_E_GONE "153"		// Your castle is gone
#define BUY_WALL_E_NOTPLAYING "154"


// REQUEST CODE
#define LOGIN "01"
#define SIGNUP "02"
#define CREATE_LOBBY "03"
#define GET_LOBBY "04"
#define JOIN_GAME "05"
#define CHANGE_TEAM "06"
#define READY_PLAY "07"
#define UNREADY_PLAY "08"
#define QUIT_GAME "09"
#define START_GAME "10"
#define LOGOUT "11"
#define ATTACK_CASTLE "12"
#define ATTACK_MINE "13"
#define BUY_WEAPON "14"
#define BUY_WALL "15"
#define UPDATE_CASTLE_QUESTION "16"
#define UPDATE_MINE_QUESTION "17"
#define TIMELY_UPDATE
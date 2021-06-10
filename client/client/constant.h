#pragma once

//Buffer size
#define PAYLOAD_SIZE 16384
#define BUFF_SIZE 32000
#define PAYLOAD_LEN_SIZE 2
#define CODE_SIZE 4

#define USERNAME_LEN 256
#define ERROR_MESS_LEN 1024
#define NAME_LENGTH 256
#define QUESTION_LENGTH 256
#define ANSWER_LENGTH 256

// Boundery
#define MAX_PLAYER_OF_TEAM 3
#define MAX_NUM_PLAYER 12	// for lobby play size
#define MAX_TEAM_OF_GAME 4
#define MAX_CASTLE_OF_GAME 3
#define MAX_MINE_OF_GAME 6

#define MAX_LOBBY 100		// for get lobbies arr
#define MAX_QUESTION 200
#define TEAM_PLAYER_NUM_STR 13	// for decode get lobby str

#define GAME_ID_SIZE 13	// for game id str
#define TEAM_ID_SIZE 1	// for team id str
#define CASTLE_ID_SIZE 1	// for castle id str
#define MINE_ID_SIZE 1	// for mine id str
#define QUESTION_ID_SIZE 3 // for question id str
#define ANSWER_ID_SIZE 3 // for question id str

// default value
#define DEFAULT_PORT 5500
#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_USRNAME ""
#define DELIM_RESPONSE " "

// State
// User state
#define USER_NONAUTH 0	// Khi chua dang nhap
#define USER_AUTH 1		// Khi da dang nhap
#define USER_WATING 2	// Khi dang trong phong
#define USER_INGAME 3	// Khi dang choi game

// Player state
#define UNREADY 0
#define READY 1

// Lobby state
#define WAITING 0
#define INGAME 1


// Type
#define WOOD 0
#define STONE 1
#define IRON 2

// Castle wall
#define NO_WALL 0
#define FENCE 1
#define WOOD_WALL 2
#define STONE_WALL 3
#define LEGEND_WALL 4

// Wall defense
#define NO_WALL_DEF 0
#define FENCE_DEF 200
#define WOOD_WALL_DEF 1000
#define STONE_WALL_DEF 3000
#define LEGEND_WALL_DEF 8000

// Wall's wood price
#define NO_WALL_WOOD 0
#define FENCE_WOOD 200
#define WOOD_WALL_WOOD 1000
#define STONE_WALL_WOOD 200
#define LEGEND_WALL_WOOD 1000

// Wall's stone price
#define NO_WALL_STONE 5
#define FENCE_STONE 50
#define WOOD_WALL_STONE 100
#define STONE_WALL_STONE 1000
#define LEGEND_WALL_STONE 2000

// Wall's iron price
#define NO_WALL_IRON 0
#define FENCE_IRON 50
#define WOOD_WALL_IRON 100
#define STONE_WALL_IRON 1000
#define LEGEND_WALL_IRON 2000

#define NO_WEAPON 0
#define BALLISTA 1
#define CATAPULT 2
#define CANNON 3

// Weapon attack
#define NO_WEAPON_ATK 0
#define BALLISTA_ATK 1000
#define CATAPULT_ATK 3000
#define CANNON_ATK 8000

// Weapon's wood price
#define NO_WEAPON_WOOD 0
#define BALLISTA_WOOD 1500
#define CATAPULT_WOOD 400
#define CANNON_WOOD 500

// Weapon's stone price
#define NO_WEAPON_STONE 0
#define BALLISTA_STONE 0
#define CATAPULT_STONE 1500
#define CANNON_STONE 2500

// Weapon's iron price
#define NO_WEAPON_IRON 0
#define BALLISTA_IRON 200
#define CATAPULT_IRON 300
#define CANNON_IRON 1800

// RESPONSE CODE
// Login
#define LOGIN_SUCCESS "10000"
#define LOGIN_E_ALREADY "10001"
#define LOGIN_E_ELSEWHERE "10002"
#define LOGIN_E_PASSWORD "10003"
#define LOGIN_E_NOTEXIST "10004"

// Signup
#define SIGNUP_SUCCESS "10100"
#define SIGNUP_E_LOGGEDIN "10101"
#define SIGNUP_E_FORMAT "10102"
#define SIGNUP_E_EXIST "10103"

// Logout
#define LOGOUT_SUCCESS "10200"
#define LOGOUT_E_NOTAUTH "10201"
#define LOGOUT_E_INGAME "10202"

// Create lobby
#define CREATE_SUCCESS "10300"
#define CREATE_E_NOTAUTH "10301"
#define CREATE_E_INGAME "10302"
#define CREATE_E_FULLGAME "10303"
#define CREATE_E_INVALIDTEAM "10304"

// Get lobby
#define LOBBY_SUCCESS "10400"
#define LOBBY_E_NOTAUTH "10401"

// Join Lobby
#define JOIN_SUCCESS "10501"
#define JOIN_E_NOTAUTH "10501"
#define JOIN_E_FORMAT "10503"
#define JOIN_E_FULLGAME "10504"
#define JOIN_E_FULLTEAM "10505"
#define JOIN_E_NOGAME "10506"
#define JOIN_E_NOTEAM "10507"
#define JOIN_E_PLAYING "10508"

// Ready for game
#define READY_SUCCESS "20000"
#define READY_E_NOTAUTH "20001"
#define READY_E_NOTINGAME "20002"
#define READY_E_ALREADY "20003"
#define READY_E_PLAYING "20004"
#define READY_E_HOST "20005"

// Unready for game
#define UNREADY_SUCCESS "20100"
#define UNREADY_E_NOTAUTH "20101"
#define UNREADY_E_NOTINGAME "20102"
#define UNREADY_E_ALREADY "20103"
#define UNREADY_E_PLAYING "20104"
#define UNREADY_E_HOST "20105"

// Start game
#define START_SUCCESS "20200"
#define START_E_NOTAUTH "20201"
#define START_E_NOTINGAME "20201"
#define START_E_NOTALLREADY "20203"
#define START_E_PLAYING "20204"
#define START_E_NOTHOST "20205"
#define START_E_ONETEAM "20206"

// Quit lobby
#define QUIT_SUCCESS "20300"
#define QUIT_E_NOTAUTH "20301"
#define QUIT_E_NOTINGAME "20302"
#define QUIT_E_READY "20303"


// Change team
#define CHANGE_SUCCESS "20400"
#define CHANGE_E_NOTAUTH "20401"
#define CHANGE_E_NOTINGAME "20402"
#define CHANGE_E_FULL "20403"
#define CHANGE_E_READY "20404"
#define CHANGE_E_PLAYING "20405"
#define CHANGE_E_UNKNOWNTEAM "20406"
#define CHANGE_E_CURRENTTEAM "20407"

// Attack castle
#define ATK_CST_SUCCESS "30000"
#define ATK_CST_E_TOOLATE "30001"	// Answer the question too late
#define ATK_CST_E_TOOWEAK "30002"	// Enemy build a better wall
#define ATK_CST_E_YOURS "30003"		// Guess your teammate got it first
#define ATK_CST_E_NOTPLAYING "30004"	// Either game or player is not playing
#define ATK_CST_E_FORMAT "30005"
#define ATK_CST_E_WRONG "30006"		// Using UPDATE_MINE_ATK_CST_W

// Attack mine
#define ATK_MINE_SUCCESS "30100"
#define ATK_MINE_E_TOOLATE "30101"	// Answer the question too late
#define ATK_MINE_E_NOTPLAYING "30102"	// Either game or player is not playing
#define ATK_MINE_E_FORMAT "30103"
#define ATK_MINE_E_WRONG "30104"	// Using UPDATE_MINE_ATK_MINE_W

// Buy weapon
#define BUY_WEAPON_SUCCESS "30200"
#define BUY_WEAPON_E_NOTENOUGH "30201"	// Not enough resources
#define BUY_WEAPON_E_WEAKER "30203"		// Can't buy a weaker weapon
#define BUY_WEAPON_E_NOTPLAYING "30204"

// Buy wall
#define BUY_WALL_SUCCESS "30300"
#define BUY_WALL_E_NOTENOUGH "30301"
#define BUY_WALL_E_WEAKER "30302"		// Can't by weaker wall
#define BUY_WALL_E_GONE "30303"		// Your castle is gone
#define BUY_WALL_E_NOTPLAYING "30304"
#define BUY_WALL_E_FORMAT "30305"


// Ingame
#define UPDATE_GAME_START "40100"
#define UPDATE_GAME_CSTQUEST "40101"
#define UPDATE_GAME_MINEQUEST "40102"
#define UPDATE_GAME_ATK_CST_R "40103"
#define UPDATE_GAME_ATK_MINE_R "40104"
#define UPDATE_GAME_ATK_CST_W "40105"
#define UPDATE_GAME_ATK_MINE_W "40106"
#define UPDATE_GAME_BUY_WPN "40107"
#define UPDATE_GAME_BUY_WALL "40108"

#define UPDATE_LOBBY_QUIT "40200"
#define UPDATE_LOBBY_JOIN "40201"
#define UPDATE_LOBBY_CHANGETEAM "40202"
#define UPDATE_LOBBY_READY "40203"
#define UPDATE_LOBBY_UNREADY "40204"

// REQUEST CODE
// Outgame - Request header
#define LOGIN "100"
#define SIGNUP "101"
#define LOGOUT "102"
#define CREATE_LOBBY "103"
#define GET_LOBBY "104"
#define JOIN_LOBBY "105"

// In lobby - Request header
#define READY_PLAY "200"
#define UNREADY_PLAY "201"
#define START_GAME "202"
#define QUIT_LOBBY "203"
#define CHANGE_TEAM "204"

// Ingame - Request header
#define ATTACK_CASTLE "300"
#define ATTACK_MINE "301"
#define BUY_WEAPON "302"
#define BUY_WALL "303"

// Update header - Server send back only
#define TIMELY_UPDATE "400"
#define UPDATE_GAME "401"
#define UPDATE_LOBBY "402"
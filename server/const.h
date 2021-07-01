#pragma once
// *** Server constant ***
// Macros
#define BUFFLEN 5 + strlen(buff + 5)

// Buffer size
#define BUFF_SIZE				8192
#define OP_SIZE					3
#define ACCOUNT_SIZE			50
#define TIME_SIZE				50
#define HEADER_SIZE				5
#define CASTLE_BUFF				4
#define MINE_BUFF				6
#define TEAM_BUFF				11

// Server address
#define SERVER_ADDR				"127.0.0.1"
#define SERVER_PORT				6000

// Completion Port Operation
#define RECEIVE					0
#define SEND					1

// File
#define ACCOUNT_FILE			"account.txt"
#define EASY_QUESTION_FILE		"easy.txt"
#define HARD_QUESTION_FILE		"hard.txt"

// Player state
#define NOT_AUTHORIZED			0
#define AUTHORIZED				1
#define JOINT					2
#define READY					3
#define PLAYING					4

// Game state
#define WAITING					0
#define ONGOING					1
#define FINISHED				2

// Mine resources
#define RESOURCE_NUM			3
#define WOOD					0
#define STONE					1
#define IRON					2

// Universal
#define UNKNOWN_HEADER			"000"

// Outgame - Request header
#define LOGIN					"100"
#define SIGNUP					"101"
#define LOGOUT					"102"
#define CREATE_GAME				"103"
#define GET_LOBBY				"104"
#define JOIN_GAME				"105"

// In lobby - Request header
#define READY_PLAY				"200" // nothing
#define UNREADY_PLAY			"201" // nothing
#define START_GAME				"202" // nothing
#define QUIT_GAME				"203" // nothing
#define CHANGE_TEAM				"204" // teamIndex
#define KICK					"205"

// Ingame - Request header
#define ATTACK_CASTLE			"300" // targetType	| targetIndex	| QuestionId Answer
#define ATTACK_MINE				"301"
#define BUY_WEAPON				"302" // weaponType
#define BUY_WALL				"303" // wallType	| castleIndex
#define CHEAT					"304" // Add 1000 to every resource, include gold

// Update header - Server send back only
#define TIMELY_UPDATE			"400"
#define UPDATE_GAME				"401"
#define UPDATE_LOBBY			"402"

// Outgame - Response
#define LOGIN_SUCCESS			"10000" // nothing
#define LOGIN_E_ALREADY			"10001" // nothing
#define LOGIN_E_ELSEWHERE		"10002" // nothing
#define LOGIN_E_PASSWORD		"10003" // nothing
#define LOGIN_E_NOTEXIST		"10004" // nothing

#define SIGNUP_SUCCESS			"10100" // nothing
#define SIGNUP_E_LOGGEDIN		"10101" // nothing
#define SIGNUP_E_FORMAT			"10102" // nothing
#define SIGNUP_E_EXIST			"10103" // nothing

#define LOGOUT_SUCCESS			"10200" // nothing
#define LOGOUT_E_NOTAUTH		"10201" // nothing
#define LOGOUT_E_INGAME			"10202" // nothing

#define CREATE_SUCCESS			"10300" // gameid
#define CREATE_E_NOTAUTH		"10301" // nothing
#define CREATE_E_INGAME			"10302" // nothing
#define CREATE_E_FULLGAME		"10303" // nothing
#define CREATE_E_INVALIDTEAM	"10304" // nothing

#define LOBBY_SUCCESS			"10400" // lobbylist
#define LOBBY_E_NOTAUTH			"10401" // nothing
#define LOBBY_E_INGAME			"10402"

#define JOIN_SUCCESS			"10500" 
#define JOIN_E_NOTAUTH			"10501" // nothing
#define JOIN_E_ALREADY			"10502" // lobbylist
#define JOIN_E_FORMAT			"10503" // lobbylist
#define JOIN_E_FULLGAME			"10504" // lobbylist
#define JOIN_E_FULLTEAM			"10505" // lobbylist
#define JOIN_E_NOGAME			"10506" // lobbylist
#define JOIN_E_NOTEAM			"10507" // lobbylist
#define JOIN_E_PLAYING			"10508" // nothing

//#define READY_SUCCESS			"20000" // Using UPDATE_LOBBY_READY instead
#define READY_E_NOTAUTH			"20001"
#define READY_E_NOTINGAME		"20002"
#define READY_E_ALREADY			"20003"
#define READY_E_PLAYING			"20004"
#define READY_E_HOST			"20005"

//#define UNREADY_SUCCESS		"20100" // Using UPDATE_GAME_UNREADY instead
#define UNREADY_E_NOTAUTH		"20101"
#define UNREADY_E_NOTINGAME		"20102"
#define UNREADY_E_ALREADY		"20103"
#define UNREADY_E_PLAYING		"20104"
#define UNREADY_E_HOST			"20105"

//#define START_SUCCESS			"20200" // Using UPDATE_GAME_START instead
#define START_E_NOTAUTH			"20201"
#define START_E_NOTINGAME		"20202"
#define START_E_NOTALLREADY		"20203"
#define START_E_PLAYING			"20204"
#define START_E_NOTHOST			"20205"
#define START_E_ONETEAM			"20206"

#define QUIT_SUCCESS			"20300" // Using to inform player quit success, and using UPDATE_LOBBY_QUIT to inform all player in that game room
#define QUIT_E_NOTAUTH			"20301"
#define QUIT_E_NOTINGAME		"20302"
#define QUIT_E_READY			"20303"

//#define CHANGE_SUCCESS		"20400" // Using UPDATE_LOBBY_CHANGE to inform all other player
#define CHANGE_E_NOTAUTH		"20401"
#define CHANGE_E_NOTINGAME		"20402"
#define CHANGE_E_FULL			"20403"
#define CHANGE_E_READY			"20404"
#define CHANGE_E_PLAYING		"20405"
#define CHANGE_E_UNKNOWNTEAM	"20406"
#define CHANGE_E_CURRENTTEAM	"20407"

#define KICK_SUCCESS			"20500" // To kicked player
#define KICK_E_NOTAUTH			"20501"
#define KICK_E_NOTINGAME		"20502"
#define KICK_E_PLAYING			"20503"
#define KICK_E_NOTHOST			"20504"
#define KICK_E_YOURSELF			"20505"
#define KICK_E_NOPLAYER			"20506"
#define KICK_E_FORMAT			"20507"

// Ingame - Response header
//#define ATK_CST_SUCCESS		"30000" // Using UPDATE_MINE_ATK_CST_R
#define ATK_CST_E_TOOLATE		"30001" // Answer the question too late
#define ATK_CST_E_TOOWEAK		"30002" // Enemy build a better wall
#define ATK_CST_E_YOURS			"30003" // Guess your teammate got it first
#define ATK_CST_E_NOTPLAYING	"30004" // Either game or player is not playing
#define ATK_CST_E_FORMAT		"30005"
//#define ATK_CST_E_WRONG		"30006" // Using UPDATE_MINE_ATK_CST_W

//#define ATK_MINE_SUCCESS		"30100" // Using UPDATE_MINE_ATK_MINE_R
#define ATK_MINE_E_TOOLATE		"30101" // Answer the question too late
#define ATK_MINE_E_NOTPLAYING	"30102" // Either game or player is not playing
#define ATK_MINE_E_FORMAT		"30103"
//#define ATK_MINE_E_WRONG		"30104" // Using UPDATE_MINE_ATK_MINE_W

//#define BUY_WEAPON_SUCCESS	"30200" // Using UPDATE_GAME_BUY_WPN
#define BUY_WEAPON_E_NOTENOUGH	"30201" // Guess your teammate bought it first
#define BUY_WEAPON_E_WEAKER		"30202" // Can't buy a weaker weapon
#define BUY_WEAPON_E_NOTPLAYING	"30203" // Either game or player is not playing
#define BUY_WEAPON_E_FORMAT		"30204"

//#define BUY_WALL_SUCCESS		"30300" // Using UPDATE_GAME_BUY_WALL
#define BUY_WALL_E_NOTENOUGH	"30301" // Guess your teammate bought it first
#define BUY_WALL_E_WEAKER		"30302" // Can't buy a weaker wall
#define BUY_WALL_E_GONE			"30303" // Castle has been taken by enemy
#define BUY_WALL_E_NOTPLAYING	"30304" // Either game or player is not playing
#define BUY_WALL_E_FORMAT		"30305"

//#define CHEAT_SUCCESS			"30400" // Use UPDATE_GAME_CHEAT instead
#define CHEAT_E_NOTPLAYING		"30401"
#define CHEAT_E_GREEDY			"30402"

#define UPDATE_GAME_START		"40100" // When game start
#define UPDATE_GAME_CSTQUEST	"40101" // Send new castle question
#define UPDATE_GAME_MINEQUEST	"40102" // Send new mine question
#define UPDATE_GAME_ATK_CST_R	"40103" // Attack castle success
#define UPDATE_GAME_ATK_MINE_R	"40104" // Attack mine success
#define UPDATE_GAME_ATK_CST_W	"40105" // Attack castle wrong answer
#define UPDATE_GAME_ATK_MINE_W	"40106" // Attack mine wrong answer
#define UPDATE_GAME_BUY_WPN		"40107" // Buy weapon
#define UPDATE_GAME_BUY_WALL	"40108" // Buy wall
#define UPDATE_GAME_CHEAT		"40109" // Cheat
#define UPDATE_GAME_OVER        "40110" // When game end

#define UPDATE_LOBBY_QUIT		"40200" // Inform disconnect from player
#define UPDATE_LOBBY_JOIN		"40201" // Inform join from player
#define UPDATE_LOBBY_CHANGETEAM	"40202" // Inform player change team
#define UPDATE_LOBBY_READY		"40203" // Inform player ready
#define UPDATE_LOBBY_UNREADY	"40204" // Inform player unready
#define UPDATE_LOBBY_KICK		"40205" // Inform player being kicked out

// *** Game logic constant ***
// Amount
#define MAX_CLIENT				1000
#define GAME_NUM				12
#define PLAYER_NUM				12
#define TEAM_NUM				4
#define CASTLE_NUM				3
#define MINE_NUM				6
#define WALL_NUM				5
#define WEAPON_NUM				4
#define HARDQUESTION_NUM		200
#define EASYQUESTION_NUM		100

// Wall type
#define NO_WALL					0
#define FENCE					1
#define WOOD_WALL				2
#define STONE_WALL				3
#define LEGEND_WALL				4

// Wall defense
#define NO_WALL_DEF				0
#define FENCE_DEF				200
#define WOOD_WALL_DEF			1000
#define STONE_WALL_DEF			3000
#define LEGEND_WALL_DEF			8000

// Wall's wood price
#define NO_WALL_WOOD			0
#define FENCE_WOOD				200
#define WOOD_WALL_WOOD			1000
#define STONE_WALL_WOOD			200
#define LEGEND_WALL_WOOD		1000

// Wall's stone price
#define NO_WALL_STONE			0
#define FENCE_STONE				50
#define WOOD_WALL_STONE			100
#define STONE_WALL_STONE		1000
#define LEGEND_WALL_STONE		2000

// Wall's iron price
#define NO_WALL_IRON			0
#define FENCE_IRON				50
#define WOOD_WALL_IRON			100
#define STONE_WALL_IRON			1000
#define LEGEND_WALL_IRON		2000

// Weapon type
#define NO_WEAPON				0
#define BALLISTA				1
#define CATAPULT				2
#define CANNON					3

// Weapon attack
#define NO_WEAPON_ATK			0
#define BALLISTA_ATK			1000
#define CATAPULT_ATK			3000
#define CANNON_ATK				8000

// Weapon's wood price
#define NO_WEAPON_WOOD			0
#define BALLISTA_WOOD			1500
#define CATAPULT_WOOD			400
#define CANNON_WOOD				500

// Weapon's stone price
#define NO_WEAPON_STONE			0
#define BALLISTA_STONE			0
#define CATAPULT_STONE			1500
#define CANNON_STONE			2500

// Weapon's iron price
#define NO_WEAPON_IRON			0
#define BALLISTA_IRON			200
#define CATAPULT_IRON			300
#define CANNON_IRON				1800

// Update loop info
#define LOOP_TIME               30000 
#define MAX_LOOP                480 // 4 hour

// Addtion per 30 seconds
#define ADDITION_GOLD			5
#define ADDITION_WOOD			20
#define ADDITION_STONE			15
#define ADDITION_IRON			10

// Maximum amount of resource each team
#define MAX_GOLD				999999
#define MAX_WOOD				999999
#define MAX_STONE				999999
#define MAX_IRON				999999
#define MAX_AMOUNT				999999

// Cheat amount
#define CHEAT_GOLD				10000
#define CHEAT_AMOUNT			10000
#define CHEAT_WOOD				10000
#define CHEAT_STONE				10000
#define CHEAT_IRON				10000
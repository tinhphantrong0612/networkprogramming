#pragma once
// *** Server constant ***
// Macros
#define BUFFLEN (4 + strlen(buff + 4))

// Buffer size
#define BUFF_SIZE				8192
#define ACCOUNT_SIZE			50
#define TIME_SIZE				50
#define HEADER_SIZE				4
#define CASTLE_BUFF				4
#define MINE_BUFF				6
#define TEAM_BUFF				11

// Server address
#define SERVER_ADDR				"127.0.0.1"
#define SERVER_PORT				6000

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

// Outgame - Request header
#define LOGIN					"01" // username	| password
#define SIGNUP					"02" // username	| password
#define CREATE_GAME				"03" // nothing
#define GET_LOBBY				"04" // nothing
#define JOIN_GAME				"05" // gameId
#define CHANGE_TEAM				"06" // teamIndex
#define READY_PLAY				"07" // nothing
#define UNREADY_PLAY			"08" // nothing
#define QUIT_GAME				"09" // nothing
#define START_GAME				"10" // nothing
#define LOGOUT					"11" // nothing

// Outgame - Response
#define LOGIN_SUCCESS			"010" // nothing
#define LOGIN_E_ALREADY			"011" // nothing
#define LOGIN_E_ELSEWHERE		"012" // nothing
#define LOGIN_E_PASSWORD		"013" // nothing
#define LOGIN_E_NOTEXIST		"014" // nothing

#define SIGNUP_SUCCESS			"020" // nothing
#define SIGNUP_E_LOGGEDIN		"021" // nothing
#define SIGNUP_E_FORMAT			"022" // nothing
#define SIGNUP_E_EXIST			"023" // nothing

#define CREATE_SUCCESS			"030" // gameid
#define CREATE_E_NOTAUTH		"031" // nothing
#define CREATE_E_INGAME			"032" // nothing
#define CREATE_E_FULLGAME		"033" // nothing
#define CREATE_E_INVALIDTEAM	"034" // nothing

#define LOBBY_SUCCESS			"040"
#define LOBBY_E_NOTAUTH			"041"

#define JOIN_SUCCESS			"050"
#define JOIN_E_NOTAUTH			"051"
#define JOIN_E_ALREADY			"052"
#define JOIN_E_FORMAT			"053"
#define JOIN_E_FULLGAME			"054"
#define JOIN_E_FULLTEAM			"055"
#define JOIN_E_NOGAME			"056"
#define JOIN_E_NOTEAM			"057"
#define JOIN_E_PLAYING			"058"

#define CHANGE_SUCCESS			"060"
#define CHANGE_E_NOTAUTH		"061"
#define CHANGE_E_NOTINGAME		"062"
#define CHANGE_E_FULL			"063"
#define CHANGE_E_READY			"064"
#define CHANGE_E_PLAYING		"065"
#define CHANGE_E_UNKNOWNTEAM	"066"
#define CHANGE_E_CURRENTTEAM	"067"

#define READY_SUCCESS			"070"
#define READY_E_NOTAUTH			"071"
#define READY_E_NOTINGAME		"072"
#define READY_E_ALREADY			"073"
#define READY_E_PLAYING			"074"
#define READY_E_HOST			"075"

#define UNREADY_SUCCESS			"080"
#define UNREADY_E_NOTAUTH		"081"
#define UNREADY_E_NOTINGAME		"082"
#define UNREADY_E_ALREADY		"083"
#define UNREADY_E_PLAYING		"084"
#define UNREADY_E_HOST			"085"

#define QUIT_SUCCESS			"090"
#define QUIT_E_NOTAUTH			"091"
#define QUIT_E_NOTINGAME		"092"
#define QUIT_E_READY			"093"

#define START_SUCCESS			"100"
#define START_E_NOTAUTH			"101"
#define START_E_NOTINGAME		"102"
#define START_E_NOTALLREADY		"103"
#define START_E_PLAYING			"104"
#define START_E_NOTHOST			"105"
#define START_E_ONETEAM			"106"

#define LOGOUT_SUCCESS			"110"
#define LOGOUT_E_NOTAUTH		"111"
#define LOGOUT_E_INGAME			"112"

// Ingame - Request header
#define ATTACK_CASTLE			"12" // targetType	| targetIndex	| QuestionId Answer
#define ATTACK_MINE				"13"
#define BUY_WEAPON				"14" // weaponType
#define BUY_WALL				"15" // wallType	| castleIndex
#define CASTLE_QUEST			"16"
#define MINE_QUEST				"17"
#define TIMELY_UPDATE			"18"
#define UPDATE_GAME				"19"
#define UPDATE_LOBBY			"20"

// Ingame - Response header
#define ATK_CST_SUCCESS			"120"
#define ATK_CST_E_TOOLATE		"121" // Answer the question too late
#define ATK_CST_E_TOOWEAK		"122" // Enemy build a better wall
#define ATK_CST_E_YOURS			"123" // Guess your teammate got it first
#define ATK_CST_E_NOTPLAYING	"124" // Either game or player is not playing
#define ATK_CST_E_WRONG			"125"
#define ATK_CST_E_FORMAT		"126"

#define ATK_MINE_SUCCESS		"130"
#define ATK_MINE_E_TOOLATE		"131" // Answer the question too late
#define ATK_MINE_E_NOTPLAYING	"132" // Either game or player is not playing
#define ATK_MINE_E_WRONG		"133"
#define ATK_MINE_E_FORMAT		"134"

#define BUY_WEAPON_SUCCESS		"140"
#define BUY_WEAPON_E_NOTENOUGH	"141" // Guess your teammate bought it first
#define BUY_WEAPON_E_WEAKER		"142" // Can't buy a weaker weapon
#define BUY_WEAPON_E_NOTPLAYING	"143" // Either game or player is not playing
#define BUY_WEAPON_E_FORMAT		"144"

#define BUY_WALL_SUCCESS		"150"
#define BUY_WALL_E_NOTENOUGH	"151" // Guess your teammate bought it first
#define BUY_WALL_E_WEAKER		"152" // Can't buy a weaker wall
#define BUY_WALL_E_GONE			"153" // Castle has been taken by enemy
#define BUY_WALL_E_NOTPLAYING	"154" // Either game or player is not playing
#define BUY_WALL_E_FORMAT		"155"

#define UPDATE_GAME_START		"190"
#define UPDATE_GAME_CASTQUEST	"191"
#define UPDATE_GAME_MINEQUEST	"192"
#define UPDATE_GAME_ATK_CST_R	"193"
#define UPDATE_GAME_ATK_MINE_R	"194"
#define UPDATE_GAME_ATK_CST_W	"195"
#define UPDATE_GAME_ATK_MINE_W	"196"
#define UPDATE_GAME_BUY_WPN		"197"
#define UPDATE_GAME_BUY_WALL	"198"

#define UPDATE_LOBBY_DISCONNECT	"200"
#define UPDATE_LOBBY_JOIN		"201"
#define UPDATE_LOBBY_CHANGETEAM	"202"
#define UPDATE_LOBBY_READY		"203"
#define UPDATE_LOBBY_UNREADY	"204"

// *** Game logic constant ***
// Amount
#define GAME_NUM				12
#define PLAYER_NUM				12
#define TEAM_NUM				4
#define CASTLE_NUM				3
#define MINE_NUM				6
#define WALL_NUM				5
#define WEAPON_NUM				4
#define HARDQUESTION_NUM		10
#define EASYQUESTION_NUM		10

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

// Addtion per 30 seconds
#define ADDITION_GOLD			5
#define ADDITION_WOOD			20
#define ADDITION_STONE			15
#define ADDITION_IRON			10
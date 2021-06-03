#pragma once
// *** Server constant ***
// Buffer size
#define BUFF_SIZE				8192
#define ACCOUNT_SIZE			50
#define TIME_SIZE				50
#define HEADER_SIZE				10
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

// Outgame - Request header
#define LOGIN					"01" // username	| password
#define SIGNUP					"02" // username	| password
#define CREATE_GAME				"03" // nothing
#define JOIN_GAME				"04" // gameId
#define CHANGE_TEAM				"05" // teamIndex
#define READY_PLAY				"06" // nothing
#define UNREADY_PLAY			"07" // nothing
#define OUT_GAME				"08" // nothing
#define START_GAME				"09" // nothing
#define LOGOUT					"10" // nothing

// Outgame - Response
#define LOGIN_SUCCESS			"010"
#define LOGIN_E_ALREADY			"011"
#define LOGIN_E_ELSEWHERE		"012"
#define LOGIN_E_PASSWORD		"013"
#define LOGIN_E_NOTEXIST		"014"

#define SIGNUP_SUCCESS			"020"
#define SIGNUP_E_LOGGEDIN		"021"
#define SIGNUP_E_EXIST			"022"

#define CREATE_SUCCESS			"030"
#define CREATE_E_NOTAUTH		"031"
#define CREATE_E_INGAME			"032"

#define JOIN_SUCCESS			"040"
#define JOIN_E_NOTAUTH			"041"
#define JOIN_E_FULL				"042"
#define JOIN_E_ALREADY			"043"

#define CHANGE_SUCCESS			"050"
#define CHANGE_E_NOTAUTH		"051"
#define CHANGE_E_NOTINGAME		"052"
#define CHANGE_E_FULL			"053"
#define CHANGE_E_READY			"054"
#define CHANGE_E_PLAYING		"055"

#define READY_SUCCESS			"060"
#define READY_E_NOTAUTH			"061"
#define READY_E_NOTINGAME		"062"
#define READY_E_ALREADY			"063"
#define READY_E_PLAYING			"064"
#define READY_E_CREATOR			"065"

#define UNREADY_SUCCESS			"070"
#define UNREADY_E_NOTAUTH		"071"
#define UNREADY_E_NOTINGAME		"072"
#define UNREADY_E_ALREADY		"073"
#define UNREADY_E_PLAYING		"074"
#define UNREADY_E_CREATOR		"075"

#define OUT_SUCCESS				"080"
#define OUT_E_NOTAUTH			"081"
#define OUT_E_NOTINGAME			"082"
#define OUT_E_READY				"083"
#define OUT_E_PLAYING			"084"

#define START_SUCCESS			"090"
#define START_E_NOTAUTH			"091"
#define START_E_NOTINGAME		"092"
#define START_E_NOTALLREADY		"093"
#define START_E_PLAYING			"094"
#define START_E_NOTCREATOR		"095"

#define LOGOUT_SUCCESS			"100"
#define LOGOUT_E_NOTAUTH		"101"
#define LOGOUT_E_INGAME			"102"

// Ingame - Request header
#define ATTACK					"11" // targetType	| targetIndex	| QuestionId Answer
#define BUY_WEAPON				"12" // weaponType
#define BUY_WALL				"13" // wallType	| castleIndex

// Ingame - Response header
// No success header because success will change the game,
// Server will send game info to all player
#define ATTACK_E_TOOLATE		"111" // Answer the question too late
#define ATTACK_E_TOOWEAK		"112" // Enemy build a better wall
#define ATTACK_E_YOURS			"113" // Guess your teammate got it first
#define ATTACK_E_NOTPLAYING		"114" // Either game or player is not playing

#define BUY_WEAPON_E_NOTENOUGH	"121" // Guess your teammate bought it first
#define BUY_WEAPON_E_WEAKER		"122" // Can't buy a weaker weapon
#define BUY_WEAPON_E_NOTPLAYING	"123" // Either game or player is not playing

#define BUY_WALL_E_NOTENOUGH	"131" // Guess your teammate bought it first
#define BUY_WALL_E_WEAKER		"132" // Can't buy a weaker wall
#define BUY_WALL_E_GONE			"133" // Castle has been taken by enemy
#define BUY_WALL_E_NOTPLAYING	"134" // Either game or player is not playing

// *** Game logic constant ***
// Amount
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
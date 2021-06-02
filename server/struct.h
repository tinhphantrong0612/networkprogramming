#pragma once

typedef struct _wall {
	int			type;
	int			defense;
	int			wood;
	int			stone;
	int			iron;

	_wall(int _type, int _defense, int _wood, int _stone, int _iron) {
		type	=	_type;
		defense =	_defense;
		wood	=	_wood;
		stone	=	_stone;
		iron	=	_iron;
	}
} *WALL;


typedef struct _weapon {
	int			type;
	int			attack;
	int			wood;
	int			stone;
	int			iron;

	_weapon(int _type, int _attack, int _wood, int _stone, int _iron) {
		type	=	_type;
		attack	=	_attack;
		wood	=	_wood;
		stone	=	_stone;
		iron	=	_iron;
	}
} *WEAPON;

typedef struct _castle {
	int			index;
	WALL		wall;
	int			occupiedBy;
	int			question;
	int			answer;
	GAME		game;
} *CASTLE;

typedef struct _mine {
	int			index;
	int			wood;
	int			stone;
	int			iron;
	int			woodQuestion;
	int			woodAnswer;
	int			stoneQuestion;
	int			stoneAnswer;
	int			ironQuestion;
	int			ironAnswer;
	GAME		game;
} *MINE;

typedef struct _player {
	SOCKET		socket;
	char		IP[INET_ADDRSTRLEN];
	int			port;
	int			teamIndex;
	int			placeInTeam;
	int			gameIndex;
	char		account[ACCOUNT_SIZE];
	int			state;
	GAME		game;
} *PLAYER;

typedef struct _team {
	int			index;
	PLAYER		players[3];
	int			castles[3];
	int			mines[6];
	WEAPON		weapon;
	int			gold;
	int			wood;
	int			stone;
	int			iron;
	GAME		game;
} *TEAM;

typedef struct _game {
	long long	id;
	long long	startAt;
	int			gameState;
	int			host;
	PLAYER		players[PLAYER_NUM];
	TEAM		teams[TEAM_NUM];
	CASTLE		castles[CASTLE_NUM];
	MINE		mines[MINE_NUM];
} *GAME;

/* The updatePlayerInfo function update a player info
* @param	player			[IN/OUT]	Player
* @param	socket			[IN]		Socket
* @param	IP				[IN]		IP Address
* @param	port			[IN]		Port
* @param	teamIndex		[IN]		Player's team's index
* @param	placeInTeam		[IN]		Player's place in team
* @param	gameIndex		[IN]		Player's place in game
* @param	account			[IN]		Player's account
* @param	state			[IN]		Player's state
* @return	nothing
*/
void updatePlayerInfo(PLAYER player, SOCKET socket, char *IP, int port, int teamIndex, int placeInTeam, int gameIndex, GAME game, char *account, int state) {
	player->socket = socket;
	player->port = port;
	player->teamIndex = teamIndex;
	player->placeInTeam = placeInTeam;
	player->gameIndex = gameIndex;
	player->game = game;
	player->state = state;
	if (IP == 0) memset(player->IP, 0, INET_ADDRSTRLEN);
	else strcpy_s(player->IP, INET_ADDRSTRLEN, IP);
	if (account == 0) memset(player->account, 0, ACCOUNT_SIZE);
	else strcpy_s(player->account, ACCOUNT_SIZE, account);
}

/* The updatePlayerInfo function clear a player info
* @param	player			[IN/OUT]	Player
* @return	nothing
*/
void clearPlayerInfo(PLAYER player) {
	// Remove player from game and team
	if (player->game != NULL) {
		GAME game = player->game;
		game->players[player->gameIndex] = NULL;
		game->teams[player->teamIndex]->players[player->placeInTeam] = NULL;
	}
	updatePlayerInfo(player, 0, 0, 0, 0, 0, 0, 0, 0, NOT_AUTHORIZED);
}

/* The calculateACastle function calculate a castle's properties into a buffer
* @param	castle			[IN]		Castle
* @param	buff			[IN/OUT]	Calculate result
* @return	buff
*/
char *calculateACastle(CASTLE castle, char *buff) {
	buff[0] = castle->occupiedBy + 48; // Occupied by
	buff[1] = castle->wall->type + 48; // Wall type
	buff[2] = castle->wall->defense / 256; // Wall defense
	buff[3] = castle->wall->defense % 256;
	return buff;
}

/* The calculateAMine function calculate a mine's properties into a buffer
* @param	mine			[IN]		Mine
* @param	buff			[IN/OUT]	Calculate result
* @return	buff
*/
char *calculateAMine(MINE mine, char *buff) {
	buff[0] = mine->wood / 256; // Current wood
	buff[1] = mine->wood % 256;
	buff[2] = mine->stone / 256; // Current stone
	buff[3] = mine->stone % 256;
	buff[4] = mine->iron / 256; // Current iron
	buff[5] = mine->iron % 256;
	return buff;
}

/* The calculateATeam function calculate a team's properties into a buffer
* @param	team			[IN]		Team
* @param	buff			[IN/OUT]	Calculate result
* @return	buff
*/
char *calculateATeam(TEAM team, char *buff) {
	buff[0]		=	team->weapon->type + 48;	// Weapon type
	buff[1]		=	team->weapon->attack / 256; // Weapon attack
	buff[2]		=	team->weapon->attack % 256;
	buff[3]		=	team->gold / 256;			// Team's gold
	buff[4]		=	team->gold % 256;
	buff[5]		=	team->wood / 256;			// Team's wood
	buff[6]		=	team->wood % 256;
	buff[7]		=	team->stone / 256;			// Team's stone
	buff[8]		=	team->stone % 256;
	buff[9]		=	team->iron / 256;			// Team's iron
	buff[10]	=	team->iron % 256;
	return buff;
}

/* The calculateGame function calculate a game's info into a buffer
* @param	game			[IN]		Game
* @param	buff			[IN/OUT]	Calculate result
* @return	buff
*/
char *calculateGame(GAME game, char *buff) {
	int currentBuffLen = 0;
	// Start with three castles
	for (int i = 0; i < CASTLE_NUM; i++) {
		calculateACastle(game->castles[i], buff + i * CASTLE_BUFF);
	}
	currentBuffLen += 3 * CASTLE_BUFF;
	// Then six mines
	for (int i = 0; i < MINE_NUM; i++) {
		calculateAMine(game->mines[i], buff + currentBuffLen + i * MINE_BUFF);
	}
	currentBuffLen += 6 * MINE_BUFF;
	// Then each team
	for (int i = 0; i < TEAM_NUM; i++) {
		calculateATeam(game->teams[i], buff + currentBuffLen + i * TEAM_BUFF);
	}
	return buff;
}

int getCastleQuestion(CASTLE castle, char *fileName, char *buff) {
	FILE *file;
	fopen_s(&file, fileName, "r");
	int seed = getTime() / 1000;
	srand(seed);

	castle->question = rand() % HARDQUESTION_NUM; // randomize
	int question = castle->question;
	while (question != 0) {
		fgets(buff, BUFF_SIZE, file);
	}
	fgets(buff, BUFF_SIZE, file); // Get question
	castle->answer = buff[0] - 48; // Get answer
	int questionLength = strlen(buff);
	buff[0] = castle->question / 256;
	buff[1] = castle->question % 256;
	return questionLength;
}

int getMineWoodQuestion(MINE mine, char *fileName, char *buff) {
	FILE *file;
	fopen_s(&file, fileName, "r");
	int seed = getTime() / 1000;
	srand(seed);

	mine->woodQuestion = rand() % EASYQUESTION_NUM; // randomize
	int question = mine->woodQuestion;
	while (question != 0) {
		fgets(buff, BUFF_SIZE, file);
	}
	fgets(buff, BUFF_SIZE, file); // Get question
	mine->woodAnswer = buff[0] - 48; // Get answer
	int questionLength = strlen(buff);
	buff[0] = mine->woodQuestion / 256;
	buff[1] = mine->woodQuestion % 256;
	return questionLength;
}

int getMineStoneQuestion(MINE mine, char *fileName, char *buff) {
	FILE *file;
	fopen_s(&file, fileName, "r");
	int seed = getTime() / 1000;
	srand(seed);

	mine->stoneQuestion = rand() % EASYQUESTION_NUM; // randomize
	int question = mine->stoneQuestion;
	while (question != 0) {
		fgets(buff, BUFF_SIZE, file);
	}
	fgets(buff, BUFF_SIZE, file); // Get question
	mine->woodAnswer = buff[0] - 48; // Get answer
	int questionLength = strlen(buff);
	buff[0] = mine->stoneQuestion / 256;
	buff[1] = mine->stoneQuestion % 256;
	return questionLength;
}

int getMineIronQuestion(MINE mine, char *fileName, char *buff) {
	FILE *file;
	fopen_s(&file, fileName, "r");
	int seed = getTime() / 1000;
	srand(seed);

	mine->ironQuestion = rand() % EASYQUESTION_NUM; // randomize
	int question = mine->ironQuestion;
	while (question != 0) {
		fgets(buff, BUFF_SIZE, file);
	}
	fgets(buff, BUFF_SIZE, file); // Get question
	mine->ironAnswer = buff[0] - 48; // Get answer
	int questionLength = strlen(buff);
	buff[0] = mine->ironQuestion / 256;
	buff[1] = mine->ironQuestion % 256;
	return questionLength;
}
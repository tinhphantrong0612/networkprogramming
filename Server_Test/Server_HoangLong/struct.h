#pragma once
typedef struct _wall		*WALL;
typedef struct _weapon		*WEAPON;
typedef struct _castle		*CASTLE;
typedef struct _mine		*MINE;
typedef struct _player		*PLAYER;
typedef struct _team		*TEAM;
typedef struct _game		*GAME;
typedef struct _perIoData	PER_IO_OPERATION_DATA, *LPPER_IO_OPERATION_DATA;

typedef struct _perIoData {
	WSAOVERLAPPED overlapped;
	WSABUF dataBuff;
	CHAR buffer[BUFF_SIZE];
	int bufLen;
	int recvBytes;
	int sentBytes;
	int operation;
} PER_IO_OPERATION_DATA, *LPPER_IO_OPERATION_DATA;

typedef struct _wall {
	int					type;
	int					defense;
} *WALL;


typedef struct _weapon {
	int					type;
	int					attack;
} *WEAPON;

typedef struct _castle {
	int					index;
	WALL				wall;
	int					occupiedBy;
	int					question;
	int					answer;
	GAME				game;
} *CASTLE;

typedef struct _mine {
	int					index;
	int					resources[RESOURCE_NUM];
	int					question[3];
	int					answer[3];
	GAME				game;
} *MINE;

typedef struct _player {
	SOCKET				socket;
	char				IP[INET_ADDRSTRLEN];
	int					port;
	int					teamIndex;
	int					placeInTeam;
	int					gameIndex;
	char				account[ACCOUNT_SIZE];
	int					state;
	GAME				game;
	CRITICAL_SECTION	criticalSection;
} *PLAYER;

typedef struct _team {
	int					index;
	PLAYER				players[3];
	WEAPON				weapon;
	int					gold;
	int					basedResources[RESOURCE_NUM];
	GAME				game;
} *TEAM;

typedef struct _game {
	long long			id;
	long long			startAt;
	int					gameState;
	int					host;
	int					teamNum;
	PLAYER				players[PLAYER_NUM];
	TEAM				teams[TEAM_NUM];
	CASTLE				castles[CASTLE_NUM];
	MINE				mines[MINE_NUM];
	CRITICAL_SECTION	criticalSection;
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

/* The calculateACastle function calculate a castle's properties into a buffer
* @param	castle			[IN]		Castle
* @param	buff			[IN/OUT]	Calculate result
* @return	buff
*/
void calculateACastle(CASTLE castle, char *buff) {
	_itoa_s(castle->index, buff + strlen(buff), BUFF_SIZE, 10);
	strcat_s(buff, BUFF_SIZE, "#");
	_itoa_s(castle->occupiedBy, buff + strlen(buff), BUFF_SIZE, 10);
	strcat_s(buff, BUFF_SIZE, "#");
	_itoa_s(castle->wall->type, buff + strlen(buff), BUFF_SIZE, 10);
	strcat_s(buff, BUFF_SIZE, "#");
	_itoa_s(castle->wall->defense, buff + strlen(buff), BUFF_SIZE, 10);
	strcat_s(buff, BUFF_SIZE, "#");
}

/* The calculateAMine function calculate a mine's properties into a buffer
* @param	mine			[IN]		Mine
* @param	buff			[IN/OUT]	Calculate result
* @return	buff
*/
void calculateAMine(MINE mine, char *buff) {
	_itoa_s(mine->index, buff + strlen(buff), BUFF_SIZE, 10);
	strcat_s(buff, BUFF_SIZE, "#");
	for (int i = 0; i < RESOURCE_NUM; i++) {
		_itoa_s(mine->resources[i], buff + strlen(buff), BUFF_SIZE, 10);
		strcat_s(buff, BUFF_SIZE, "#");
	}
}

/* The calculateATeam function calculate a team's properties into a buffer
* @param	team			[IN]		Team
* @param	buff			[IN/OUT]	Calculate result
* @return	buff
*/
void calculateATeam(TEAM team, char *buff) {
	_itoa_s(team->index, buff + strlen(buff), BUFF_SIZE, 10);
	strcat_s(buff, BUFF_SIZE, "#");
	_itoa_s(team->weapon->type, buff + strlen(buff), BUFF_SIZE, 10);
	strcat_s(buff, BUFF_SIZE, "#");
	_itoa_s(team->weapon->attack, buff + strlen(buff), BUFF_SIZE, 10);
	strcat_s(buff, BUFF_SIZE, "#");
	_itoa_s(team->gold, buff + strlen(buff), BUFF_SIZE, 10);
	strcat_s(buff, BUFF_SIZE, "#");
	for (int i = 0; i < RESOURCE_NUM; i++) {
		_itoa_s(team->basedResources[i], buff + strlen(buff), BUFF_SIZE, 10);
		strcat_s(buff, BUFF_SIZE, "#");
	}
}

/* The calculateGame function calculate a game's info into a buffer
* @param	game			[IN]		Game
* @param	buff			[IN/OUT]	Calculate result
* @return	nothing
*/
void getGameProperties(GAME game, char *buff) {
	// Start with three castles
	for (int i = 0; i < CASTLE_NUM; i++) {
		calculateACastle(game->castles[i], buff + strlen(buff));
	}
	// Then six mines
	for (int i = 0; i < MINE_NUM; i++) {
		calculateAMine(game->mines[i], buff + strlen(buff));
	}
	// Then each team
	for (int i = 0; i < TEAM_NUM; i++) {
		calculateATeam(game->teams[i], buff + strlen(buff));
	}
}

void getCastleQuestion(CASTLE castle, char *fileName, char *buff) {
	FILE *file;
	fopen_s(&file, fileName, "r");

	long long time = getTime();
	castle->question = (time + castle->index) % HARDQUESTION_NUM; // randomize
	int question = castle->question;
	while (question != 0) {
		fgets(buff, BUFF_SIZE, file);
		question--;
	}
	fgets(buff, BUFF_SIZE, file); // Get question
	fclose(file);
	castle->answer = buff[0] - 48; // Get answer
	strcpy_s(buff, BUFF_SIZE, buff + 1);
}

void getMineQuestion(MINE mine, char *fileName, int type, char *buff) {
	FILE *file;
	fopen_s(&file, fileName, "r");

	long long time = getTime();
	mine->question[type] = (time + type + mine->index) % EASYQUESTION_NUM; // randomize
	int question = mine->question[type];
	while (question != 0) {
		fgets(buff, BUFF_SIZE, file);
		question--;
	}
	fgets(buff, BUFF_SIZE, file); // Get question
	fclose(file);
	mine->answer[type] = buff[0] - 48; // Get answer
	strcpy_s(buff, BUFF_SIZE, buff + 1);
}

void createEmptyGame(GAME game) {
	game->id = 0; // set id to 0
	game->startAt = 0; // set start time to 0
	game->gameState = WAITING; // set game state to waiting
	game->host = 0;
	for (int i = 0; i < PLAYER_NUM; i++) game->players[i] = NULL; // Disconnect to all player
	for (int i = 0; i < CASTLE_NUM; i++) { // Unlink and clear castle
		game->castles[i] = (CASTLE)malloc(sizeof(_castle));
		game->castles[i]->occupiedBy = 4;
		game->castles[i]->index = i;
		game->castles[i]->wall = (WALL)malloc(sizeof(_wall));
		game->castles[i]->wall->type = NO_WALL;
		game->castles[i]->wall->defense = NO_WALL_DEF;
		game->castles[i]->game = game;
	}
	for (int i = 0; i < MINE_NUM; i++) { // Unlink and clear mine
		game->mines[i] = (MINE)malloc(sizeof(_mine));
		game->mines[i]->game = game;
		game->mines[i]->index = i;
		for (int j = 0; j < RESOURCE_NUM; j++) {
			game->mines[i]->resources[j] = 0;
		}
	}
	for (int i = 0; i < TEAM_NUM; i++) { // Unlink and clear team
		game->teams[i] = (TEAM)malloc(sizeof(_team));
		game->teams[i]->game = game;
		game->teams[i]->weapon = (WEAPON)malloc(sizeof(_weapon));
		game->teams[i]->weapon->type = NO_WEAPON;
		game->teams[i]->weapon->attack = NO_WEAPON_ATK;
		game->teams[i]->gold = 0;
		for (int j = 0; j < 3; j++) {
			game->teams[i]->players[j] = NULL;
		}
		for (int j = 0; j < 3; j++) {
			game->teams[i]->basedResources[j] = 0;
		}
	}
}

/* The emptyGame function clear a game
* @param	game			[IN/OUT]		Game
* @return	nothing
*/
void emptyGame(GAME game) {
	game->id = 0; // set id to 0
	game->startAt = 0; // set start time to 0
	game->gameState = WAITING; // set game state to waiting
	game->host = 0;
	for (int i = 0; i < PLAYER_NUM; i++) game->players[i] = NULL; // Disconnect to all player
	for (int i = 0; i < CASTLE_NUM; i++) { // Unlink and clear castle
		game->castles[i]->occupiedBy = 4;
		game->castles[i]->wall->type = NO_WALL;
		game->castles[i]->wall->defense = NO_WALL_DEF;
	}
	for (int i = 0; i < MINE_NUM; i++) { // Unlink and clear mine
		for (int j = 0; j < RESOURCE_NUM; j++) {
			game->mines[i]->resources[j] = 0;
		}
	}
	for (int i = 0; i < TEAM_NUM; i++) { // Unlink and clear team
		game->teams[i]->weapon->type = NO_WEAPON;
		game->teams[i]->weapon->attack = NO_WEAPON_ATK;
		game->teams[i]->gold = 0;
		for (int j = 0; j < 3; j++) {
			game->teams[i]->players[j] = NULL;
		}
		for (int j = 0; j < 3; j++) {
			game->teams[i]->basedResources[j] = 0;
		}
	}
}

/* The createGame function create a game
* @param	player			[IN/OUT]		Creator
* @param	game			[IN/OUT]		Pointer to a emptyGame
* @param	teamNum			[IN]			Number of teams in game
* @return	nothing
*/
void createGame(PLAYER player, GAME game, int teamNum) {
	// Init value
	game->id = getTime();
	game->startAt = 0;
	game->gameState = WAITING;
	game->host = 0;
	game->teamNum = teamNum;
	game->players[0] = player; // Set the first player is the host
	for (int i = 0; i < CASTLE_NUM; i++) {
		game->castles[i]->wall->type = NO_WALL;
		game->castles[i]->wall->defense = NO_WALL_DEF;
		game->castles[i]->occupiedBy = 4;
	}
	for (int i = 0; i < MINE_NUM; i++) {
		for (int j = 0; j < RESOURCE_NUM; j++) {
			game->mines[i]->resources[j] = 0;
		}
	}
	for (int i = 0; i < TEAM_NUM; i++) {
		for (int j = 0; j < 3; j++) {
			game->teams[i]->players[j] = NULL;
		}
		game->teams[i]->weapon->type = NO_WEAPON;
		game->teams[i]->weapon->attack = NO_WEAPON_ATK;
		game->teams[i]->gold = 0;
		for (int j = 0; j < 3; j++) {
			game->teams[i]->basedResources[j] = 0;
		}
	}
	game->teams[0]->players[0] = player;
	// Link player to game and team, 0, 0, 0 means player in team 0, at place 0 in that team, and place 0 in game
	updatePlayerInfo(player, player->socket, player->IP, player->port, 0, 0, 0, game, player->account, JOINT);
}

/* The resetGame function reset a game
* @param	game			[IN/OUT]		Pointer to a emptyGame
* @return	nothing
*/
void resetGame(GAME game) {
	// Init value
	game->id = getTime();
	game->startAt = 0;
	game->gameState = WAITING;
	for (int i = 0; i < CASTLE_NUM; i++) {
		game->castles[i]->wall->type = NO_WALL;
		game->castles[i]->wall->defense = NO_WALL_DEF;
		game->castles[i]->occupiedBy = 4;
	}
	for (int i = 0; i < MINE_NUM; i++) {
		for (int j = 0; j < RESOURCE_NUM; j++) {
			game->mines[i]->resources[j] = 0;
		}
	}
	for (int i = 0; i < TEAM_NUM; i++) {
		game->teams[i]->weapon->type = NO_WEAPON;
		game->teams[i]->weapon->attack = NO_WEAPON_ATK;
		game->teams[i]->gold = 0;
		for (int j = 0; j < 3; j++) {
			game->teams[i]->basedResources[j] = 0;
		}
	}
	for (int i = 0; i < PLAYER_NUM; i++) {
		if (game->players[i] != NULL) {
			updatePlayerInfo(game->players[i], game->players[i]->socket, game->players[i]->IP, game->players[i]->port,
				game->players[i]->teamIndex, game->players[i]->placeInTeam, game->players[i]->gameIndex, game, game->players[i]->account, JOINT);
		}
	}
}
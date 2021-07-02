#pragma once
extern CRITICAL_SECTION				accountMapCriticalSection;
extern CRITICAL_SECTION				gameListCriticalSection;
extern GAME							games[GAME_NUM];
extern unsigned __stdcall			timelyUpdate(LPVOID game);

int		Send(PLAYER, char *);
int		Send(PLAYER, LPPER_IO_OPERATION_DATA, DWORD);
int		Receive(PLAYER, LPPER_IO_OPERATION_DATA);
void	getLobbyList(char *);
void	getGameInfo(GAME, char *);
void	getTeamPlayerString(GAME, char *);
void	informGameRoomChange(GAME, int, char *, char *, char *);
void	getGameRoomChangeSuccessResponse(GAME, int, char *, char *);
void	sendToAllPlayersInGameRoom(GAME, char *);
void	sendNewMineQuestion(GAME, int, int, char *);
void	sendNewCastleQuestion(GAME, int, char *);
void	informCastleAttack(GAME, int, int, char *, char *, char *);
void	informMineAttack(GAME, int, int, int, char *, char *, char *);
void	setNewWeapon(TEAM, int, int, int, int, int);
void	informBuyWeapon(GAME, int, int, char *, char *, char *);
void	setNewWall(TEAM, CASTLE, int, int, int, int, int);
void	informBuyWall(GAME, int, int, int, char *, char *, char *);
void	informCheat(GAME, int, char *, char *, char *);
void	informUpdate(GAME, char *, char *);
void	informEndGame(GAME, char *, char *, char *);

/* The setResponseAndSend function sets response, then send to player
* @param	opcode				[IN]		Operation code
* @param	response			[IN]		Response buffer
* @param	responseLen			[IN]		Size of response
* @param	buff				[IN/OUT]	Buffer contain full message
* @return	Nothing
*/
void setResponse(char *opcode, char *response, int responseLen, char *buff) {
	for (int i = 0; i < OP_SIZE; i++) {
		buff[i] = opcode[i];
	}
	buff[HEADER_SIZE - 2] = responseLen / 255 + 1;
	buff[HEADER_SIZE - 1] = responseLen % 255 + 1;
	strcpy_s(buff + HEADER_SIZE, BUFF_SIZE, response);
}

/* The setResponseAndSend function sets response, then send to player
* @param	player				[IN]		Player's info
* @param	opcode				[IN]		Operation code
* @param	response			[IN]		Response buffer
* @param	responseLen			[IN]		Size of response
* @param	buff				[IN/OUT]	Buffer contain full message
* @return	Nothing
*/
void setResponseAndSend(PLAYER player, char *opcode, char *response, int responseLen, char *buff) {
	setResponse(opcode, response, responseLen, buff);
	Send(player, buff);
}

/* The handleLogin function handle login request from a player
* @param	player		[IN]		Player's info
* @param	opcode		[IN]		Operation code
* @param	buff		[IN]		Buffer to handle
* @return	Nothing
*/
void handleLogin(PLAYER player, char *opcode, char *buff) {
	while (!TryEnterCriticalSection(&player->criticalSection)) {}
	if (player->state != NOT_AUTHORIZED) setResponseAndSend(player, opcode, (char *) LOGIN_E_ALREADY, strlen(LOGIN_E_ALREADY), buff);
	else {
		char *sharp = strchr(buff, '#');
		if (sharp == NULL || sharp + 1 == NULL) setResponseAndSend(player, opcode, (char *) LOGIN_E_NOTEXIST, strlen(LOGIN_E_NOTEXIST), buff);
		else {
			unsigned int usernameLen = (int)(sharp - buff);
			unsigned int passwordLen = strlen(sharp + 1);
			if (usernameLen > ACCOUNT_SIZE || passwordLen > ACCOUNT_SIZE) {
				setResponseAndSend(player, opcode, (char *) LOGIN_E_NOTEXIST, strlen(LOGIN_E_NOTEXIST), buff);
			}
			else {
				// Get username, password from payload
				char username[ACCOUNT_SIZE];
				char password[ACCOUNT_SIZE];
				sharp[0] = 0;
				strcpy_s(username, ACCOUNT_SIZE, buff);
				strcpy_s(password, ACCOUNT_SIZE, sharp + 1);
				// Find username
				while (!TryEnterCriticalSection(&accountMapCriticalSection)) {}
				map<string, pair<string, int>>::iterator it;
				it = accountMap.find(username);
				if (it == accountMap.end()) setResponseAndSend(player, opcode, (char *) LOGIN_E_NOTEXIST, strlen(LOGIN_E_NOTEXIST), buff);
				else if (strcmp(it->second.first.c_str(), password) != 0) setResponseAndSend(player, opcode, (char *) LOGIN_E_PASSWORD, strlen(LOGIN_E_PASSWORD), buff);
				else if (it->second.second == AUTHORIZED) setResponseAndSend(player, opcode, (char *) LOGIN_E_ELSEWHERE, strlen(LOGIN_E_ELSEWHERE), buff);
				else {
					// Update player state and account state in account map
					updatePlayerInfo(player, player->socket, player->IP, player->port, 0, 0, 0, 0, username, AUTHORIZED);
					it->second.second = AUTHORIZED;
					setResponseAndSend(player, opcode, (char *) LOGIN_SUCCESS, strlen(LOGIN_SUCCESS), buff);
				}
				LeaveCriticalSection(&accountMapCriticalSection);
			}
		}
	}
	LeaveCriticalSection(&player->criticalSection);
}

/* The handleSignUp function handle signup request from a player
* @param	player		[IN]		Player's info
* @param	opcode		[IN]		Operation code
* @param	buff		[IN]		Buffer to handle
* @return	Nothing
*/
void handleSignUp(PLAYER player, char *opcode, char *buff) {
	while (!TryEnterCriticalSection(&player->criticalSection)) {}
	if (player->state != NOT_AUTHORIZED) setResponseAndSend(player, opcode, (char *) SIGNUP_E_LOGGEDIN, strlen(SIGNUP_E_LOGGEDIN), buff);
	else {
		char *sharp = strchr(buff, '#');
		if (sharp == NULL || sharp + 1 == NULL) {
			setResponseAndSend(player, opcode, (char *) SIGNUP_E_FORMAT, strlen(SIGNUP_E_FORMAT), buff);
		}
		else {
			unsigned int usernameLen = (int)(sharp - buff);
			unsigned int passwordLen = strlen(sharp + 1);
			if (usernameLen > ACCOUNT_SIZE || passwordLen > ACCOUNT_SIZE) setResponseAndSend(player, opcode, (char *) SIGNUP_E_FORMAT, strlen(SIGNUP_E_FORMAT), buff);
			else {
				// Get username, password from payload
				char username[ACCOUNT_SIZE];
				char password[ACCOUNT_SIZE];
				sharp[0] = 0;
				strcpy_s(username, ACCOUNT_SIZE, buff);
				strcpy_s(password, ACCOUNT_SIZE, sharp + 1);
				if (strlen(password) < passwordLen) setResponseAndSend(player, opcode, (char *) SIGNUP_E_FORMAT, strlen(SIGNUP_E_FORMAT), buff);
				else {
					while (!TryEnterCriticalSection(&accountMapCriticalSection)) {}
					map<string, pair<string, int>>::iterator it;
					it = accountMap.find(username);
					if (it != accountMap.end()) setResponseAndSend(player, opcode, (char *) SIGNUP_E_EXIST, strlen(SIGNUP_E_EXIST), buff);
					else {
						// Add new account to account map and to account file
						accountMap[username] = make_pair(password, NOT_AUTHORIZED);
						addNewAccount((char *) ACCOUNT_FILE, username, password);
						setResponseAndSend(player, opcode, (char *) SIGNUP_SUCCESS, strlen(SIGNUP_SUCCESS), buff);
					}
					LeaveCriticalSection(&accountMapCriticalSection);
				}
			}
		}
	}
	LeaveCriticalSection(&player->criticalSection);
}

/* The handleCreateGame function handle create game request from a player, include validate, create game (include create a new game, connect game and player)
* @param	player		[IN]		Player's info
* @param	opcode		[IN]		Operation code
* @param	buff		[IN]		Buffer to handle
* @return	Nothing
*/
void handleCreateGame(PLAYER player, char *opcode, char *buff) {
	while (!TryEnterCriticalSection(&player->criticalSection)) {}
	if (player->state == NOT_AUTHORIZED) setResponseAndSend(player, opcode, (char *) CREATE_E_NOTAUTH, strlen(CREATE_E_NOTAUTH), buff);
	else if (player->state != AUTHORIZED) setResponseAndSend(player, opcode, (char *) CREATE_E_INGAME, strlen(CREATE_E_INGAME), buff);
	else {
		int i;
		// Get number of teams
		int teamNum = buff[0] - 48;
		if ((teamNum < 2) || (teamNum > 4)) setResponseAndSend(player, opcode, (char *) CREATE_E_INVALIDTEAM, strlen(CREATE_E_INVALIDTEAM), buff);
		else {
			while (!TryEnterCriticalSection(&gameListCriticalSection)) {}
			for (i = 0; i < GAME_NUM; i++) {
				if (games[i]->id == 0) {
					// create new game with host player
					createGame(player, games[i], teamNum);
					break;
				}
			}
			if (i == GAME_NUM) setResponseAndSend(player, opcode, (char *) CREATE_E_FULLGAME, strlen(CREATE_E_FULLGAME), buff);
			else {
				long long gameId = games[i]->id;
				memset(buff, 0, BUFF_SIZE);
				strcpy_s(buff + HEADER_SIZE, BUFF_SIZE, CREATE_SUCCESS);
				strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
				_i64toa_s(gameId, buff + BUFFLEN, BUFF_SIZE, 10);
				setResponseAndSend(player, opcode, buff + HEADER_SIZE, strlen(buff + HEADER_SIZE), buff);
			}
			LeaveCriticalSection(&gameListCriticalSection);
		}
	}
	LeaveCriticalSection(&player->criticalSection);
}

/* The handleGetLobby function handle get lobby request from a player
* @param	player		[IN]		Player's info
* @param	opcode		[IN]		Operation code
* @param	buff		[IN]		Buffer to handle
* @return	Send Response result
*/
void handleGetLobby(PLAYER player, char *opcode, char *buff) {
	while (!TryEnterCriticalSection(&player->criticalSection)) {}
	if (player->state == NOT_AUTHORIZED) setResponseAndSend(player, opcode, (char *) LOBBY_E_NOTAUTH, strlen(LOBBY_E_NOTAUTH), buff);
	else if (player->state != AUTHORIZED) setResponseAndSend(player, opcode, (char *) LOBBY_E_INGAME, strlen(LOBBY_E_INGAME), buff);
	else {
		strcpy_s(buff + HEADER_SIZE, BUFF_SIZE, LOBBY_SUCCESS);
		while (!TryEnterCriticalSection(&gameListCriticalSection)) {}
		getLobbyList(buff);
		LeaveCriticalSection(&gameListCriticalSection);
		setResponseAndSend(player, opcode, buff + HEADER_SIZE, strlen(buff + HEADER_SIZE), buff);
	}
	LeaveCriticalSection(&player->criticalSection);
}

/* The getLobbyList function get lobby list from all games, start with buff + BUFFLEN, used in handleGetLobby
* @param	buff		[IN/OUT]	Buffer to store lobby list
* @return	Nothing
*/
void getLobbyList(char *buff) {
	for (int i = 0; i < GAME_NUM; i++) {
		if (games[i]->id != 0 && games[i]->gameState == WAITING) {
			strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
			getGameInfo(games[i], buff);
		}
	}
}

/* The getGameInfo function handle get a single game info
* @param	game		[IN]		Game to get info
* @param	buff		[IN/OUT]	Buffer to store game info
* @return	Nothing
*/
void getGameInfo(GAME game, char *buff) {
	_i64toa_s(game->id, buff + BUFFLEN, BUFF_SIZE, 10); // 13 bytes
	strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
	_itoa_s(game->teamNum, buff + BUFFLEN, BUFF_SIZE, 10);
	strcat_s(buff + BUFFLEN, BUFF_SIZE, "#"); // 16 bytes
	getTeamPlayerString(game, buff + BUFFLEN);
}

/* The getTeamPlayerString function get game-team-player info, example: Player 0, 3, 7 in team 0, player 4, 5, 9 in team 2, result: 0xx022x0x2xx
* @param	game		[IN]		Game
* @param	buff		[IN/OUT]	Buffer to store result
* @return	Nothing
*/
void getTeamPlayerString(GAME game, char *buff) {
	for (int i = 0; i < PLAYER_NUM; i++) {
		if (game->players[i] == NULL) {
			strcat_s(buff, BUFF_SIZE, "x");
		}
		else {
			_itoa_s(game->players[i]->gameIndex, buff + i, BUFF_SIZE, 10);
		}
	}
}

/* The handleJoinGame function handle a join request from player
* @param	player		[IN/OUT]	Request player
* @param	opcode		[IN/OUT]	Operation code
* @param	buff		[IN/OUT]	Buffer to store game info
* @return	Nothing
*/
void handleJoinGame(PLAYER player, char *opcode, char *buff) {
	while (!TryEnterCriticalSection(&player->criticalSection)) {}
	if (player->state == NOT_AUTHORIZED) setResponseAndSend(player, opcode, (char *) JOIN_E_NOTAUTH, strlen(JOIN_E_NOTAUTH), buff);
	else if (player->state != AUTHORIZED) setResponseAndSend(player, opcode, (char *) JOIN_E_ALREADY, strlen(JOIN_E_ALREADY), buff);
	else {
		char *sharp = strchr(buff, '#');
		if (sharp == NULL) setResponseAndSend(player, opcode, (char *) JOIN_E_FORMAT, strlen(JOIN_E_FORMAT), buff);
		else {
			int distance = int(sharp - buff);
			if (distance != 13 || *(sharp + 2) != 0) setResponseAndSend(player, opcode, (char *) JOIN_E_FORMAT, strlen(JOIN_E_FORMAT), buff);
			else {
				sharp[0] = 0;
				long long gameId = _atoi64(buff);
				if (gameId == 0) setResponseAndSend(player, opcode, (char *) JOIN_E_NOGAME, strlen(JOIN_E_NOGAME), buff);
				else {
					int team = atoi(sharp + 1);
					int i, emptyPlaceInTeam, emptyPlaceInGame = -1, countPlayer = 0;
					GAME game = NULL;
					while (!TryEnterCriticalSection(&gameListCriticalSection)) {}
					bool isLeavedGameListCriticalSection = false;
					for (i = 0; i < GAME_NUM; i++) {
						if (games[i]->id == gameId) {
							game = games[i];
							break;
						}
					}
					if (i == GAME_NUM || game == NULL) setResponseAndSend(player, opcode, (char *) JOIN_E_NOGAME, strlen(JOIN_E_NOGAME), buff);
					while (!TryEnterCriticalSection(&game->criticalSection)) {}
					if (game->gameState != WAITING) setResponseAndSend(player, opcode, (char *) JOIN_E_PLAYING, strlen(JOIN_E_PLAYING), buff);
					else {
						LeaveCriticalSection(&gameListCriticalSection);
						isLeavedGameListCriticalSection = true;
						for (i = 0; i < PLAYER_NUM; i++) {
							if (game->players[i] == NULL) {
								if (emptyPlaceInGame == -1) emptyPlaceInGame = i;
							}
							else countPlayer++;
						}
						if (countPlayer == game->teamNum * 3) setResponseAndSend(player, opcode, (char *) JOIN_E_FULLGAME, strlen(JOIN_E_FULLGAME), buff);
						else if ((team < 0) || (team > game->teamNum - 1)) setResponseAndSend(player, opcode, (char *) JOIN_E_NOTEAM, strlen(JOIN_E_NOTEAM), buff);
						else {
							for (i = 0; i < 3; i++) {
								if (game->teams[team]->players[i] == NULL) {
									emptyPlaceInTeam = i;
									break;
								}
							}
							if (i == 3) setResponseAndSend(player, opcode, (char *) JOIN_E_FULLTEAM, strlen(JOIN_E_FULLTEAM), buff);
							else {
								// Add player to team
								game->teams[team]->players[emptyPlaceInTeam] = player;
								// Add player to game
								game->players[emptyPlaceInGame] = player;
								// Update player info
								updatePlayerInfo(player, player->socket, player->IP, player->port, team, emptyPlaceInTeam, emptyPlaceInGame, game, player->account, JOINT);
								// Create response
								strcpy_s(buff + HEADER_SIZE, BUFF_SIZE, JOIN_SUCCESS);
								strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
								int tempLen = BUFFLEN;
								buff[BUFFLEN] = emptyPlaceInGame + 48;
								buff[tempLen + 1] = 0;
								// Send to player that request
								setResponseAndSend(player, opcode, buff + HEADER_SIZE, BUFFLEN - HEADER_SIZE, buff);
								// Inform to all player in game room
								informGameRoomChange(game, emptyPlaceInGame, (char *) UPDATE_LOBBY, (char *) UPDATE_LOBBY_JOIN, buff);
							}
						}

					}
					LeaveCriticalSection(&game->criticalSection);
					if (isLeavedGameListCriticalSection == false) LeaveCriticalSection(&gameListCriticalSection);
				}
			}
		}
	}
	LeaveCriticalSection(&player->criticalSection);
}

/* The informGameRoomChange function create a response and send to all players in a room whenever someone join, leave, ready or unready
* @param	game				[IN]		Game
* @param	requestPlayer		[IN]		Place of request player in game
* @param	responseCode		[IN]		Response code for request
* @param	buff				[IN/OUT]	Buffer to store result
* @return	Nothing
*/
void informGameRoomChange(GAME game, int index, char *opcode, char *responseCode, char *buff) {
	getGameRoomChangeSuccessResponse(game, index, responseCode, buff);
	setResponse(opcode, buff + HEADER_SIZE, strlen(buff + HEADER_SIZE), buff);
	sendToAllPlayersInGameRoom(game, buff);
}

/* The getGameRoomChangeSuccessResponse function create a response to send to all players in a room whenever someone join, leave, ready or unready
* @param	game				[IN]		Game
* @param	requestPlayer		[IN]		Place of request player in game
* @param	responseCode		[IN]		Response code for request
* @param	buff				[IN/OUT]	Buffer to store result
* @return	Nothing
*/
void getGameRoomChangeSuccessResponse(GAME game, int requestPlayer, char* responseCode, char *buff) {
	memset(buff, 0, BUFF_SIZE);
	strcpy_s(buff + HEADER_SIZE, BUFF_SIZE, responseCode);
	strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
	_itoa_s(game->teamNum, buff + BUFFLEN, BUFF_SIZE, 10);
	strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
	int tempLen = BUFFLEN;
	buff[BUFFLEN] = requestPlayer + 48;
	buff[tempLen + 1] = 0;
	strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
	tempLen = BUFFLEN;
	buff[BUFFLEN] = game->host + 48;
	buff[tempLen + 1] = 0;
	for (int i = 0; i < PLAYER_NUM; i++) {
		if (game->players[i] != NULL) {
			strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
			tempLen = BUFFLEN;
			_itoa_s(i, buff + BUFFLEN, BUFF_SIZE, 10);
			buff[tempLen + 1] = 0;
			strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
			strcpy_s(buff + BUFFLEN, BUFF_SIZE, game->players[i]->account);
			strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
			_itoa_s(game->players[i]->state, buff + BUFFLEN, BUFF_SIZE, 10);
			strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
			_itoa_s(game->players[i]->teamIndex, buff + BUFFLEN, BUFF_SIZE, 10);
		}
	};
}

/* The sendToAllPlayersInGameRoom function send message to all players in game room
* @param	game				[IN]		Game
* @param	buff				[IN/OUT]	Buffer to sent to all player
* @return	Nothing
*/
void sendToAllPlayersInGameRoom(GAME game, char *buff) {
	for (int i = 0; i < PLAYER_NUM; i++) {
		if (game->players[i] != NULL) {
			Send(game->players[i], buff);
		}
	}
}

/* The handleChangeTeam function handle a change team request from player
* @param	player		[IN/OUT]	Request player
* @param	opcode		[IN/OUT]	Operation code
* @param	buff		[IN/OUT]	Buffer to store game info
* @return	Nothing
*/
void handleChangeTeam(PLAYER player, char *opcode, char *buff) {
	while (!TryEnterCriticalSection(&player->criticalSection)) {}
	if (player->game == NULL) {
		setResponseAndSend(player, opcode, (char *) CHANGE_E_NOTINGAME, strlen(CHANGE_E_NOTINGAME), buff);
		LeaveCriticalSection(&player->criticalSection);
		return;
	}
	if (player->state == NOT_AUTHORIZED) setResponseAndSend(player, opcode, (char *) CHANGE_E_NOTAUTH, strlen(CHANGE_E_NOTAUTH), buff);
	else if (player->state == AUTHORIZED) setResponseAndSend(player, opcode, (char *) CHANGE_E_NOTINGAME, strlen(CHANGE_E_NOTINGAME), buff);
	else if (player->state == READY) setResponseAndSend(player, opcode, (char *) CHANGE_E_READY, strlen(CHANGE_E_READY), buff);
	else if (player->state == PLAYING) setResponseAndSend(player, opcode, (char *) CHANGE_E_PLAYING, strlen(CHANGE_E_PLAYING), buff);
	else {
		GAME game = player->game;
		while (!TryEnterCriticalSection(&game->criticalSection)) {}
		int emptyPlaceInTargetTeam, targetTeam = buff[0] - 48;
		if (targetTeam < 0 || targetTeam > game->teamNum - 1) setResponseAndSend(player, opcode, (char *) CHANGE_E_PLAYING, strlen(CHANGE_E_PLAYING), buff);
		else if (targetTeam == player->teamIndex) setResponseAndSend(player, opcode, (char *) CHANGE_E_CURRENTTEAM, strlen(CHANGE_E_CURRENTTEAM), buff);
		else {
			for (emptyPlaceInTargetTeam = 0; emptyPlaceInTargetTeam < 3; emptyPlaceInTargetTeam++)
				if (game->teams[targetTeam]->players[emptyPlaceInTargetTeam] == NULL) break;
			if (emptyPlaceInTargetTeam == 3) setResponseAndSend(player, opcode, (char *) CHANGE_E_FULL, strlen(CHANGE_E_FULL), buff);
			else {
				// empty player place in old team
				game->teams[player->teamIndex]->players[player->placeInTeam] = NULL;
				// link player to team
				updatePlayerInfo(player, player->socket, player->IP, player->port, targetTeam, emptyPlaceInTargetTeam, player->gameIndex, player->game, player->account, player->state);
				// link team to player
				game->teams[targetTeam]->players[emptyPlaceInTargetTeam] = player;
				informGameRoomChange(game, player->gameIndex, (char *) UPDATE_LOBBY, (char *) UPDATE_LOBBY_CHANGETEAM, buff);
			}
		}
		LeaveCriticalSection(&game->criticalSection);
	}
	LeaveCriticalSection(&player->criticalSection);
}

/* The handleReadyPlay function handle a ready play request from player
* @param	player		[IN/OUT]	Request player
* @param	opcode		[IN/OUT]	Operation code
* @param	buff		[IN/OUT]	Buffer to store game info
* @return	Nothing
*/
void handleReadyPlay(PLAYER player, char *opcode, char *buff) {
	while (!TryEnterCriticalSection(&player->criticalSection)) {}
	if (player->game == NULL) {
		setResponseAndSend(player, opcode, (char *) READY_E_NOTINGAME, strlen(READY_E_NOTINGAME), buff);
		LeaveCriticalSection(&player->criticalSection);
		return;
	}
	if (player->state == NOT_AUTHORIZED) setResponseAndSend(player, opcode, (char *) READY_E_NOTAUTH, strlen(READY_E_NOTAUTH), buff);
	else if (player->state == AUTHORIZED) setResponseAndSend(player, opcode, (char *) READY_E_NOTINGAME, strlen(READY_E_NOTINGAME), buff);
	else if (player->state == READY) setResponseAndSend(player, opcode, (char *) READY_E_ALREADY, strlen(READY_E_ALREADY), buff);
	else if (player->state == PLAYING) setResponseAndSend(player, opcode, (char *) READY_E_PLAYING, strlen(READY_E_PLAYING), buff);
	else {
		if (player->gameIndex == player->game->host) setResponseAndSend(player, opcode, (char *) READY_E_HOST, strlen(READY_E_HOST), buff);
		else {
			while (!TryEnterCriticalSection(&player->game->criticalSection)) {}
			player->state = READY; // Change player state to ready
			informGameRoomChange(player->game, player->gameIndex, (char *) UPDATE_LOBBY, (char *) UPDATE_LOBBY_READY, buff);
			LeaveCriticalSection(&player->game->criticalSection);
		}
	}
	LeaveCriticalSection(&player->criticalSection);
}

/* The handleUnreadyPlay function handle a unready request from player
* @param	player		[IN/OUT]	Request player
* @param	opcode		[IN/OUT]	Operation code
* @param	buff		[IN/OUT]	Buffer to store game info
* @return	1
*/
void handleUnreadyPlay(PLAYER player, char *opcode, char *buff) {
	while (!TryEnterCriticalSection(&player->criticalSection)) {}
	if (player->game == NULL) {
		setResponseAndSend(player, opcode, (char *) UNREADY_E_NOTINGAME, strlen(UNREADY_E_NOTINGAME), buff);
		LeaveCriticalSection(&player->criticalSection);
		return;
	}
	if (player->state == NOT_AUTHORIZED) setResponseAndSend(player, opcode, (char *) UNREADY_E_NOTAUTH, strlen(UNREADY_E_NOTAUTH), buff);
	else if (player->state == AUTHORIZED) setResponseAndSend(player, opcode, (char *) UNREADY_E_NOTINGAME, strlen(UNREADY_E_NOTINGAME), buff);
	else if (player->state == PLAYING) setResponseAndSend(player, opcode, (char *) UNREADY_E_PLAYING, strlen(UNREADY_E_PLAYING), buff);
	else {
		if (player->gameIndex == player->game->host) setResponseAndSend(player, opcode, (char *) UNREADY_E_HOST, strlen(UNREADY_E_HOST), buff);
		else if (player->state == JOINT) setResponseAndSend(player, opcode, (char *) UNREADY_E_ALREADY, strlen(UNREADY_E_ALREADY), buff);
		else {
			while (!TryEnterCriticalSection(&player->game->criticalSection)) {}
			player->state = JOINT;
			informGameRoomChange(player->game, player->gameIndex, (char *) UPDATE_LOBBY, (char *) UPDATE_LOBBY_UNREADY, buff);
			LeaveCriticalSection(&player->game->criticalSection);
		}
	}
	LeaveCriticalSection(&player->criticalSection);
}

/* The handleQuitGame function handle a quit request from player
* @param	player		[IN/OUT]	Request player
* @param	opcode		[IN/OUT]	Operation code
* @param	buff		[IN/OUT]	Buffer to store game info
* @return	1
*/
void handleQuitGame(PLAYER player, char *opcode, char *buff) {
	while (!TryEnterCriticalSection(&player->criticalSection)) {}
	if (player->game == NULL) {
		setResponseAndSend(player, opcode, (char *) QUIT_E_NOTINGAME, strlen(QUIT_E_NOTINGAME), buff);
		LeaveCriticalSection(&player->criticalSection);
		return;
	}
	GAME game = player->game;
	if (player->state == NOT_AUTHORIZED) setResponseAndSend(player, opcode, (char *) QUIT_E_NOTAUTH, strlen(QUIT_E_NOTAUTH), buff);
	else if (player->state == AUTHORIZED) setResponseAndSend(player, opcode, (char *) QUIT_E_NOTINGAME, strlen(QUIT_E_NOTINGAME), buff);
	else if (player->state == READY) setResponseAndSend(player, opcode, (char *) QUIT_E_READY, strlen(QUIT_E_READY), buff);
	else {
		while (!TryEnterCriticalSection(&game->criticalSection)) {}
		int i;
		int playerIndex = player->gameIndex;
		// Unlink game to player
		game->players[playerIndex] = NULL;
		// Unlink team to player
		game->teams[player->teamIndex]->players[player->placeInTeam] = NULL;
		for (i = 0; i < PLAYER_NUM; i++) {
			if (game->players[i] != NULL) {
				break;
			}
		}
		if (i == PLAYER_NUM) emptyGame(game);
		else if (game->host == player->gameIndex) game->host = i; // Update host if player is host
		if (player->game != NULL) informGameRoomChange(game, playerIndex, (char *) UPDATE_LOBBY, (char *) UPDATE_LOBBY_QUIT, buff);
		updatePlayerInfo(player, player->socket, player->IP, player->port, 0, 0, 0, 0, player->account, AUTHORIZED);
		setResponseAndSend(player, (char *) QUIT_GAME, (char *) QUIT_SUCCESS, strlen(QUIT_SUCCESS), buff);
		LeaveCriticalSection(&game->criticalSection);
	}
	LeaveCriticalSection(&player->criticalSection);
}

/* The handleStartGame function handle a start request from player
* @param	player		[IN/OUT]	Request player
* @param	opcode		[IN/OUT]	Operation code
* @param	buff		[IN/OUT]	Buffer to store game info
* @return	Nothing
*/
void handleStartGame(PLAYER player, char *opcode, char * buff) {
	while (!TryEnterCriticalSection(&player->criticalSection)) {}
	if (player->game == NULL) {
		setResponseAndSend(player, opcode, (char *) START_E_NOTINGAME, strlen(START_E_NOTINGAME), buff);
		LeaveCriticalSection(&player->criticalSection);
		return;
	}
	if (player->state == NOT_AUTHORIZED) setResponseAndSend(player, opcode, (char *) START_E_NOTAUTH, strlen(START_E_NOTAUTH), buff);
	else if (player->state == AUTHORIZED) setResponseAndSend(player, opcode, (char *) START_E_NOTINGAME, strlen(START_E_NOTINGAME), buff);
	else if (player->state == PLAYING) setResponseAndSend(player, opcode, (char *) START_E_PLAYING, strlen(START_E_PLAYING), buff);
	else if (player->state == READY) setResponseAndSend(player, opcode, (char *) START_E_NOTHOST, strlen(START_E_NOTHOST), buff);
	else {
		int i; 
		GAME game = player->game;
		if (game->host != player->gameIndex) setResponseAndSend(player, opcode, (char *) START_E_NOTHOST, strlen(START_E_NOTHOST), buff);
		else {
			bool isAllReady = true;
			for (i = 0; i < PLAYER_NUM; i++) {
				if (game->players[i] != NULL) {
					if (game->players[i]->state != READY && i != player->gameIndex) {
						isAllReady = false;
					}
				}
			}
			if (isAllReady == false) setResponseAndSend(player, opcode, (char *) START_E_NOTALLREADY, strlen(START_E_NOTALLREADY), buff);
			else {
				int countTeam = 0;
				for (i = 0; i < TEAM_NUM; i++) {
					for (int j = 0; j < 3; j++) {
						if (game->teams[i]->players[j] != NULL) {
							countTeam++;
							break;
						}
					}
				}
				if (countTeam < 2) setResponseAndSend(player, opcode, (char *) START_E_ONETEAM, strlen(START_E_ONETEAM), buff);
				else {
					while (!TryEnterCriticalSection(&game->criticalSection)) {}
					memset(buff, 0, BUFF_SIZE);
					// Start game
					game->gameState = ONGOING;
					game->startAt = getTime();
					// Set player state to playing
					for (i = 0; i < PLAYER_NUM; i++) {
						if (game->players[i] != NULL) {
							game->players[i]->state = PLAYING;
						}
					}
					_beginthreadex(NULL, NULL, &timelyUpdate, (void *)game, 0, 0);
					strcpy_s(buff + HEADER_SIZE, BUFF_SIZE, UPDATE_GAME_START);
					setResponse((char *) UPDATE_GAME, buff + HEADER_SIZE, strlen(buff + HEADER_SIZE), buff);
					sendToAllPlayersInGameRoom(game, buff);
					memset(buff + HEADER_SIZE, 0, BUFF_SIZE - 5);
					for (i = 0; i < CASTLE_NUM; i++) {
						sendNewCastleQuestion(game, i, buff);
					}
					for (i = 0; i < MINE_NUM; i++) {
						for (int j = 0; j < 3; j++) {
							sendNewMineQuestion(game, i, j, buff);
						}
					}
					LeaveCriticalSection(&game->criticalSection);
				}
			}
		}		
	}
	LeaveCriticalSection(&player->criticalSection);
}

/* The sendNewCastleQuestion function send new castle question when game start
* @param	game				[IN]		Game
* @param	castleId			[IN]		Id of castle
* @param	buff				[IN]		Buffer to store result
* @return	Nothing
*/
void sendNewCastleQuestion(GAME game, int castleId, char *buff) {
	memset(buff + HEADER_SIZE, 0, BUFF_SIZE - 5);
	strcpy_s(buff + BUFFLEN, BUFF_SIZE, UPDATE_GAME_CSTQUEST);
	strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
	_itoa_s(castleId, buff + BUFFLEN, BUFF_SIZE, 10);
	getCastleQuestion(game->castles[castleId], (char *) HARD_QUESTION_FILE, buff + BUFFLEN);
	setResponse((char *) UPDATE_GAME, buff + HEADER_SIZE, strlen(buff + HEADER_SIZE), buff);
	sendToAllPlayersInGameRoom(game, buff);
}

/* The sendNewCastleQuestion function send new mine question when game start
* @param	game				[IN]		Game
* @param	mineId				[IN]		Id of castle
* @param	type				[IN]		Resource type
* @param	buff				[IN]		Buffer to store result
* @return	Nothing
*/
void sendNewMineQuestion(GAME game, int mineId, int type, char *buff) {
	memset(buff + HEADER_SIZE, 0, BUFF_SIZE - 5);
	strcpy_s(buff + BUFFLEN, BUFF_SIZE, UPDATE_GAME_MINEQUEST);
	strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
	_itoa_s(mineId, buff + BUFFLEN, BUFF_SIZE, 10);
	strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
	_itoa_s(type, buff + BUFFLEN, BUFF_SIZE, 10);
	getMineQuestion(game->mines[mineId], (char *) EASY_QUESTION_FILE, type, buff + BUFFLEN);
	setResponse((char *) UPDATE_GAME, buff + HEADER_SIZE, strlen(buff + HEADER_SIZE), buff);
	sendToAllPlayersInGameRoom(game, buff);
}

/* The handleKick function handle a kick request from player
* @param	player		[IN/OUT]	Request player
* @param	opcode		[IN/OUT]	Operation code
* @param	buff		[IN/OUT]	Buffer to store game info
* @return	Nothing
*/
void handleKick(PLAYER player, char *opcode, char *buff) {
	while (!TryEnterCriticalSection(&player->criticalSection)) {}
	if (player->game == NULL) {
		setResponseAndSend(player, opcode, (char *) KICK_E_NOTINGAME, strlen(KICK_E_NOTINGAME), buff);
		LeaveCriticalSection(&player->criticalSection);
		return;
	}
	if (player->state == NOT_AUTHORIZED) setResponseAndSend(player, opcode, (char *) KICK_E_NOTAUTH, strlen(KICK_E_NOTAUTH), buff);
	else if (player->state == AUTHORIZED) setResponseAndSend(player, opcode, (char *) KICK_E_NOTINGAME, strlen(KICK_E_NOTINGAME), buff);
	else if (player->state == PLAYING) setResponseAndSend(player, opcode, (char *) KICK_E_PLAYING, strlen(KICK_E_NOTINGAME), buff);
	else {
		GAME game = player->game;
		if (player->gameIndex != game->host) setResponseAndSend(player, opcode, (char *) KICK_E_NOTHOST, strlen(KICK_E_NOTHOST), buff);
		else if (strlen(buff) != 1) setResponseAndSend(player, opcode, (char *) KICK_E_FORMAT, strlen(KICK_E_FORMAT), buff);
		else {
			int playerIndex = buff[0] - 48;
			if (playerIndex < 0 || playerIndex > 11) setResponseAndSend(player, opcode, (char *) KICK_E_FORMAT, strlen(KICK_E_FORMAT), buff);
			else if (playerIndex == game->host) setResponseAndSend(player, opcode, (char *) KICK_E_YOURSELF, strlen(KICK_E_YOURSELF), buff);
			else if (game->players[playerIndex] == NULL) setResponseAndSend(player, opcode, (char *) KICK_E_NOPLAYER, strlen(KICK_E_NOPLAYER), buff);
			else {
				while (!TryEnterCriticalSection(&game->criticalSection)) {}
				PLAYER otherPlayer = game->players[playerIndex];
				game->players[playerIndex] = NULL;
				game->teams[otherPlayer->teamIndex]->players[otherPlayer->placeInTeam] = NULL;
				updatePlayerInfo(otherPlayer, otherPlayer->socket, otherPlayer->IP, otherPlayer->port, 0, 0, 0, 0, otherPlayer->account, AUTHORIZED);
				setResponseAndSend(otherPlayer, (char *) KICK, (char *) KICK_SUCCESS, strlen(KICK_SUCCESS), buff);
				informGameRoomChange(game, playerIndex, (char *) UPDATE_LOBBY, (char *) UPDATE_LOBBY_KICK, buff);
				LeaveCriticalSection(&player->game->criticalSection);
			}
		}
	}
	LeaveCriticalSection(&player->criticalSection);
}

/* The handleLogout function handle a logout request from player
* @param	player		[IN/OUT]	Request player
* @param	opcode		[IN/OUT]	Operation code
* @param	buff		[IN/OUT]	Buffer to store game info
* @return	1
*/
void handleLogOut(PLAYER player, char *opcode, char *buff) {
	while (!TryEnterCriticalSection(&player->criticalSection)) {}
	if (player->state == NOT_AUTHORIZED) setResponseAndSend(player, opcode, (char *) LOGOUT_E_NOTAUTH, strlen(LOGOUT_E_NOTAUTH), buff);
	else if (player->state != AUTHORIZED) setResponseAndSend(player, opcode, (char *) LOGOUT_E_INGAME, strlen(LOGOUT_E_INGAME), buff);
	else {
		map<string, pair<string, int>>::iterator it = accountMap.find(player->account);
		if (it != accountMap.end()) {
			it->second.second = NOT_AUTHORIZED;
		}
		updatePlayerInfo(player, player->socket, player->IP, player->port, 0, 0, 0, 0, 0, NOT_AUTHORIZED);
		setResponseAndSend(player, opcode, (char *) LOGOUT_SUCCESS, strlen(LOGOUT_SUCCESS), buff);
	}
	LeaveCriticalSection(&player->criticalSection);
}

/* The handleAttackCastle function handle a attack castle request from player
* @param	player		[IN/OUT]	Request player
* @param	opcode		[IN/OUT]	Operation code
* @param	buff		[IN/OUT]	Buffer to store game info
* @return	1
*/
void handleAttackCastle(PLAYER player, char *opcode, char *buff) {
	while (!TryEnterCriticalSection(&player->criticalSection)) {}
	if (player->game == NULL) {
		setResponseAndSend(player, opcode, (char *) ATK_CST_E_NOTPLAYING, strlen(ATK_CST_E_NOTPLAYING), buff);
		LeaveCriticalSection(&player->criticalSection);
		return;
	}
	if (player->state != PLAYING) setResponseAndSend(player, opcode, (char *) ATK_CST_E_NOTPLAYING, strlen(ATK_CST_E_NOTPLAYING), buff);
	else {
		int castleId = 0, questionId = 0, answerId = 0;
		char *firstSharp = strchr(buff, '#');
		if (firstSharp == NULL) setResponseAndSend(player, opcode, (char *) ATK_CST_E_FORMAT, strlen(ATK_CST_E_FORMAT), buff);
		else {
			char *secondSharp = strchr(firstSharp + 1, '#');
			if (secondSharp == NULL) setResponseAndSend(player, opcode, (char *) ATK_CST_E_FORMAT, strlen(ATK_CST_E_FORMAT), buff);
			else {
				int castleIdSize = (int)(firstSharp - buff);
				int questionIdSize = (int)(secondSharp - firstSharp - 1);
				int answerIdSize = strlen(secondSharp + 1);
				if (castleIdSize != 1 || questionIdSize <= 0 || questionIdSize >= 8 || answerIdSize != 1) setResponseAndSend(player, opcode, (char *) ATK_CST_E_FORMAT, strlen(ATK_CST_E_FORMAT), buff);
				else {
					GAME game = player->game;
					TEAM team = game->teams[player->teamIndex];
					firstSharp[0] = 0;
					secondSharp[0] = 0;
					castleId = buff[0] - 48;
					questionId = atoi(firstSharp + 1);
					answerId = secondSharp[1] - 48;
					if (castleId < 0 || castleId > CASTLE_NUM - 1 || answerId < 0 || answerId > 4) setResponseAndSend(player, opcode, (char *) ATK_CST_E_FORMAT, strlen(ATK_CST_E_FORMAT), buff);
					else {
						while (!TryEnterCriticalSection(&game->criticalSection)) {}
						CASTLE targetCastle = game->castles[castleId];
						if (targetCastle->occupiedBy == player->teamIndex) setResponseAndSend(player, opcode, (char *) ATK_CST_E_YOURS, strlen(ATK_CST_E_YOURS), buff);
						else if (targetCastle->question != questionId) setResponseAndSend(player, opcode, (char *) ATK_CST_E_TOOLATE, strlen(ATK_CST_E_TOOLATE), buff);
						else {							
							if (targetCastle->answer != answerId) { // Wrong answer
								if (targetCastle->wall->defense >= team->weapon->attack) { // Lost weapon
									team->weapon->type = NO_WEAPON;
									team->weapon->attack = NO_WEAPON_ATK;
								}
								else { // Reduce attack
									team->weapon->attack -= targetCastle->wall->defense;
								}
								informCastleAttack(game, castleId, player->gameIndex, (char *) UPDATE_GAME, (char *) UPDATE_GAME_ATK_CST_W, buff);
							}
							else {
								if (targetCastle->wall->defense > team->weapon->attack) {
									targetCastle->wall->defense -= team->weapon->attack;
									team->weapon->type = NO_WEAPON;
									team->weapon->attack = NO_WEAPON_ATK;
									informCastleAttack(game, castleId, player->gameIndex, (char *) UPDATE_GAME, (char *) UPDATE_GAME_ATK_CST_R, buff);
								}
								else if (targetCastle->wall->defense < team->weapon->attack) {
									team->weapon->attack -= targetCastle->wall->defense;
									targetCastle->wall->type = NO_WALL;
									targetCastle->wall->defense = NO_WALL_DEF;
									targetCastle->occupiedBy = player->teamIndex;
									informCastleAttack(game, castleId, player->gameIndex, (char *) UPDATE_GAME, (char *) UPDATE_GAME_ATK_CST_R, buff);
								}
								else if (targetCastle->wall->defense == team->weapon->attack) {
									targetCastle->wall->type = NO_WALL;
									targetCastle->wall->defense = NO_WALL_DEF;
									team->weapon->type = NO_WEAPON;
									team->weapon->attack = NO_WEAPON_ATK;
									targetCastle->occupiedBy = player->teamIndex;
									informCastleAttack(game, castleId, player->gameIndex, (char *) UPDATE_GAME, (char *) UPDATE_GAME_ATK_CST_R, buff);
								}
							}	
						}
						LeaveCriticalSection(&game->criticalSection);
					}
				}
			}
		}
	}
	LeaveCriticalSection(&player->criticalSection);
}

/* The informCastleAttack function create a message with game properties and mine question and send to all players in a room whenever a castle being attack
* @param	game				[IN]		Game
* @param	castleId			[IN]		Id of castle being attack
* @param	playerIndex			[IN]		Place of request player in game
* @param	responseCode		[IN]		Response code for request
* @param	buff				[IN/OUT]	Buffer to store result
* @return	Nothing
*/
void informCastleAttack(GAME game, int castleId, int playerIndex, char *opcode, char* responseCode, char * buff) {
	memset(buff, 0, BUFF_SIZE);
	strcpy_s(buff + HEADER_SIZE, BUFF_SIZE, responseCode);
	strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
	int tempLen = BUFFLEN;
	buff[BUFFLEN] = playerIndex + 48; // Player Id
	buff[tempLen + 1] = 0;
	strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
	_itoa_s(castleId, buff + BUFFLEN, BUFF_SIZE, 10); // Castle Id
	strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
	_itoa_s(game->castles[castleId]->wall->type, buff + BUFFLEN, BUFF_SIZE, 10); // Wall type
	strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
	_itoa_s(game->castles[castleId]->wall->defense, buff + BUFFLEN, BUFF_SIZE, 10); // Defense
	strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
	_itoa_s(game->players[playerIndex]->teamIndex, buff + BUFFLEN, BUFF_SIZE, 10); // Team Index
	strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
	TEAM team = game->teams[game->players[playerIndex]->teamIndex];
	_itoa_s(team->weapon->type, buff + BUFFLEN, BUFF_SIZE, 10); // Weapon Type
	strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
	_itoa_s(team->weapon->attack, buff + BUFFLEN, BUFF_SIZE, 10); // Weapon Attack
	getCastleQuestion(game->castles[castleId], (char *) HARD_QUESTION_FILE, buff + BUFFLEN);
	setResponse(opcode, buff + HEADER_SIZE, strlen(buff + HEADER_SIZE), buff);
	sendToAllPlayersInGameRoom(game, buff);
}

/* The handleAttackMine function handle a logout request from player
* @param	player		[IN/OUT]	Request player
* @param	opcode		[IN/OUT]	Operation code
* @param	buff		[IN/OUT]	Buffer to store game info
* @return	Nothing
*/
void handleAttackMine(PLAYER player, char *opcode, char *buff) {
	while (!TryEnterCriticalSection(&player->criticalSection)) {}
	if (player->game == NULL) {
		setResponseAndSend(player, opcode, (char *) ATK_MINE_E_NOTPLAYING, strlen(ATK_MINE_E_NOTPLAYING), buff);
		LeaveCriticalSection(&player->criticalSection);
		return;
	}
	if (player->state != PLAYING) setResponseAndSend(player, opcode, (char *) ATK_MINE_E_NOTPLAYING, strlen(ATK_MINE_E_NOTPLAYING), buff);
	else {
		int mineId = 0, resourceType = 0, questionId = 0, answerId = 0;
		char *firstSharp = strchr(buff, '#');
		if (firstSharp == NULL || firstSharp + 1 == NULL) setResponseAndSend(player, opcode, (char *) ATK_MINE_E_FORMAT, strlen(ATK_MINE_E_FORMAT), buff);
		else {
			char *secondSharp = strchr(firstSharp + 1, '#');
			if (secondSharp == NULL) setResponseAndSend(player, opcode, (char *) ATK_MINE_E_FORMAT, strlen(ATK_MINE_E_FORMAT), buff);
			else {
				char *thirdSharp = strchr(secondSharp + 1, '#');
				if (thirdSharp == NULL) setResponseAndSend(player, opcode, (char *) ATK_MINE_E_FORMAT, strlen(ATK_MINE_E_FORMAT), buff);
				else {
					firstSharp[0] = 0;
					secondSharp[0] = 0;
					thirdSharp[0] = 0;
					int mineIdSize = (int)(firstSharp - buff);
					int resourceTypeSize = (int)(secondSharp - firstSharp - 1);
					int questionIdSize = (int)(thirdSharp - secondSharp - 1);
					int answerIdSize = strlen(thirdSharp + 1);
					if (mineIdSize != 1 || resourceTypeSize != 1 || questionIdSize <= 0 || questionIdSize > 8 || answerIdSize != 1) setResponseAndSend(player, opcode, (char *) ATK_MINE_E_FORMAT, strlen(ATK_MINE_E_FORMAT), buff);
					else {
						mineId = buff[0] - 48;
						resourceType = buff[2] - 48;
						questionId = atoi(secondSharp + 1);
						answerId = thirdSharp[1] - 48;
						if (mineId < 0 || mineId > MINE_NUM - 1 || resourceType < 0 || resourceType > 2 || answerId < 0 || answerId > 4) setResponseAndSend(player, opcode, (char *) ATK_MINE_E_FORMAT, strlen(ATK_MINE_E_FORMAT), buff);
						else {
							GAME game = player->game;
							while (!TryEnterCriticalSection(&game->criticalSection)) {}
							TEAM team = game->teams[player->teamIndex];
							MINE targetMine = game->mines[mineId];
							if (targetMine->question[resourceType] != questionId) setResponseAndSend(player, opcode, (char *) ATK_MINE_E_TOOLATE, strlen(ATK_MINE_E_TOOLATE), buff);
							else if (targetMine->answer[resourceType] != answerId) { // Wrong answer
								informMineAttack(game, mineId, resourceType, player->gameIndex, (char *) UPDATE_GAME, (char *) UPDATE_GAME_ATK_MINE_W, buff);
							}
							else { // Take resource and change question
								team->basedResources[resourceType] += targetMine->resources[resourceType];
								targetMine->resources[resourceType] = 0;
								informMineAttack(game, mineId, resourceType, player->gameIndex, (char *) UPDATE_GAME, (char *) UPDATE_GAME_ATK_MINE_R, buff);
							}
							LeaveCriticalSection(&game->criticalSection);
						}
					}
				}
			}
		}
	}
	LeaveCriticalSection(&player->criticalSection);
}

/* The informMineAttack function create a message with game properties and new question and send to all players in a room whenever a mine being attack
* @param	game				[IN]		Game
* @param	mineId				[IN]		Mine's index in game->mines[]
* @param	resourceType		[IN]		Attack resource
* @param	playerIndex			[IN]		Place of request player in game
* @param	responseCode		[IN]		Response code for request
* @param	buff				[IN/OUT]	Buffer to store result
* @return	Nothing
*/
void informMineAttack(GAME game, int mineId, int resourceType, int playerIndex, char *opcode, char* responseCode, char * buff) {
	memset(buff, 0, BUFF_SIZE);
	strcpy_s(buff + HEADER_SIZE, BUFF_SIZE, responseCode);
	strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
	int tempLen = BUFFLEN;
	buff[BUFFLEN] = playerIndex + 48; // Player Id
	buff[tempLen + 1] = 0;
	strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
	_itoa_s(mineId, buff + BUFFLEN, BUFF_SIZE, 10); // Mine Id
	strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
	_itoa_s(resourceType, buff + BUFFLEN, BUFF_SIZE, 10); // Resource Type
	strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
	_itoa_s(game->players[playerIndex]->teamIndex, buff + BUFFLEN, BUFF_SIZE, 10); // Team Index
	getMineQuestion(game->mines[mineId], (char *) EASY_QUESTION_FILE, resourceType, buff + BUFFLEN);
	setResponse(opcode, buff + HEADER_SIZE, strlen(buff + HEADER_SIZE), buff);
	sendToAllPlayersInGameRoom(game, buff);
}

/* The handleBuyWeapon function handle a buy weapon from player
* @param	player		[IN/OUT]	Request player
* @param	opcode		[IN/OUT]	Operation code
* @param	buff		[IN/OUT]	Buffer to store game info
* @return	Nothing
*/
void handleBuyWeapon(PLAYER player, char *opcode, char *buff) {
	while (!TryEnterCriticalSection(&player->criticalSection)) {}
	if (player->game == NULL) {
		setResponseAndSend(player, opcode, (char *) BUY_WEAPON_E_NOTPLAYING, strlen(BUY_WEAPON_E_NOTPLAYING), buff);
		LeaveCriticalSection(&player->criticalSection);
		return;
	}
	if (player->state != PLAYING) setResponseAndSend(player, opcode, (char *) BUY_WEAPON_E_NOTPLAYING, strlen(BUY_WEAPON_E_NOTPLAYING), buff);
	else {
		GAME game = player->game;
		TEAM team = game->teams[player->teamIndex];
		int weaponId = buff[0] - 48;
		if (weaponId <= 0 || weaponId > WEAPON_NUM - 1) setResponseAndSend(player, opcode, (char *) BUY_WEAPON_E_FORMAT, strlen(BUY_WEAPON_E_FORMAT), buff);
		else {
			while (!TryEnterCriticalSection(&game->criticalSection)) {}
			if (weaponId == BALLISTA) { // Ballista
				if (team->weapon->attack >= BALLISTA_ATK) setResponseAndSend(player, opcode, (char *) BUY_WEAPON_E_WEAKER, strlen(BUY_WEAPON_E_WEAKER), buff);
				else if (team->basedResources[WOOD] < BALLISTA_WOOD || team->basedResources[STONE] < BALLISTA_STONE || team->basedResources[IRON] < BALLISTA_IRON) setResponseAndSend(player, opcode, (char *) BUY_WEAPON_E_NOTENOUGH, strlen(BUY_WEAPON_E_FORMAT), buff);
				else {
					setNewWeapon(team, BALLISTA, BALLISTA_ATK, BALLISTA_WOOD, BALLISTA_STONE, BALLISTA_IRON);
					informBuyWeapon(game, player->gameIndex, weaponId, (char *) UPDATE_GAME, (char *) UPDATE_GAME_BUY_WPN, buff);
				}
			}
			else if (weaponId == CATAPULT) { // Catapult
				if (team->weapon->attack >= CATAPULT_ATK) setResponseAndSend(player, opcode, (char *) BUY_WEAPON_E_WEAKER, strlen(BUY_WEAPON_E_WEAKER), buff);
				else if (team->basedResources[WOOD] < CATAPULT_WOOD || team->basedResources[STONE] < CATAPULT_STONE || team->basedResources[IRON] < CATAPULT_IRON) setResponseAndSend(player, opcode, (char *) BUY_WEAPON_E_NOTENOUGH, strlen(BUY_WEAPON_E_FORMAT), buff);
				else {
					setNewWeapon(team, CATAPULT, CATAPULT_ATK, CATAPULT_WOOD, CATAPULT_STONE, CATAPULT_IRON);
					informBuyWeapon(game, player->gameIndex, weaponId, (char *) UPDATE_GAME, (char *) UPDATE_GAME_BUY_WPN, buff);
				}
			}
			else if (weaponId == CANNON) { // Cannon
				if (team->weapon->attack >= CANNON_ATK) setResponseAndSend(player, opcode, (char *) BUY_WEAPON_E_WEAKER, strlen(BUY_WEAPON_E_WEAKER), buff);
				if (team->basedResources[WOOD] < CANNON_WOOD || team->basedResources[STONE] < CANNON_STONE || team->basedResources[IRON] < CANNON_IRON) setResponseAndSend(player, opcode, (char *) BUY_WEAPON_E_NOTENOUGH, strlen(BUY_WEAPON_E_FORMAT), buff);
				else {
					setNewWeapon(team, CANNON, CANNON_ATK, CANNON_WOOD, CANNON_STONE, CANNON_IRON);
					informBuyWeapon(game, player->gameIndex, weaponId, (char *) UPDATE_GAME, (char *) UPDATE_GAME_BUY_WPN, buff);
				}
			}
			LeaveCriticalSection(&game->criticalSection);
		}
	}
	LeaveCriticalSection(&player->criticalSection);
}

/* The setNewWeapon function handle a buy weapon from player
* @param	team		[IN]		Team buy weapon
* @param	weaponId	[IN]		WeaponId
* @param	weaponAtk	[IN]		Weapon Attack
* @param	weaponWood	[IN]		Wood cost of weapon
* @param	weaponStone	[IN]		Stone cost of weapon
* @param	weaponIron	[IN]		Iron cost of weapon
* @return	Nothing
*/
void setNewWeapon(TEAM team, int weaponId, int weaponAtk, int weaponWood, int weaponStone, int weaponIron) {
	team->weapon->type = weaponId;
	team->weapon->attack = weaponAtk;
	team->basedResources[WOOD] -= weaponWood;
	team->basedResources[STONE] -= weaponStone;
	team->basedResources[IRON] -= weaponIron;
}

/* The informBuyWeapon function inform all player that someone just buy weapon
* @param	game				[IN]		Game
* @param	playerIndex			[IN]		Place of request player in team
* @param	weaponId			[IN]		Weapon id
* @param	opcode				[IN]		Operation code
* @param	responseCode		[IN]		Response code for request
* @param	buff				[IN/OUT]	Buffer to store result
* @return	Nothing
*/
void informBuyWeapon(GAME game, int playerIndex, int weaponId, char *opcode, char *responseCode, char *buff) {
	memset(buff, 0, BUFF_SIZE);
	strcpy_s(buff + HEADER_SIZE, BUFF_SIZE, responseCode);
	strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
	int tempLen = BUFFLEN;
	buff[BUFFLEN] = playerIndex + 48;
	buff[tempLen + 1] = 0;
	strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
	_itoa_s(game->players[playerIndex]->teamIndex, buff + BUFFLEN, BUFF_SIZE, 10);
	strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
	_itoa_s(weaponId, buff + BUFFLEN, BUFF_SIZE, 10);
	setResponse(opcode, buff + HEADER_SIZE, strlen(buff + HEADER_SIZE), buff);
	sendToAllPlayersInGameRoom(game, buff);
};

/* The handleBuyWall function handle a buy wall from player
* @param	player		[IN/OUT]	Request player
* @param	opcode		[IN/OUT]	Operation code
* @param	buff		[IN/OUT]	Buffer to store game info
* @return	Nothing
*/
void handleBuyWall(PLAYER player, char *opcode, char *buff) {
	while (!TryEnterCriticalSection(&player->criticalSection)) {}
	if (player->game == NULL) {
		setResponseAndSend(player, opcode, (char *) BUY_WALL_E_NOTPLAYING, strlen(BUY_WALL_E_NOTPLAYING), buff);
		LeaveCriticalSection(&player->criticalSection);
		return;
	}
	if (player->state != PLAYING) setResponseAndSend(player, opcode, (char *) BUY_WALL_E_NOTPLAYING, strlen(BUY_WALL_E_NOTPLAYING), buff);
	else {
		GAME game = player->game;
		TEAM team = game->teams[player->teamIndex];
		int castleId = 0, wallId = 0;
		if (strlen(buff) != 3) setResponseAndSend(player, opcode, (char *) BUY_WALL_E_FORMAT, strlen(BUY_WALL_E_FORMAT), buff);
		else {
			castleId = buff[0] - 48;
			wallId = buff[2] - 48;
			if (castleId < 0 || castleId > CASTLE_NUM - 1 || wallId <= 0 || wallId > 4) setResponseAndSend(player, opcode, (char *) BUY_WALL_E_FORMAT, strlen(BUY_WALL_E_FORMAT), buff);
			else {
				while (!TryEnterCriticalSection(&game->criticalSection)) {}
				CASTLE castle = game->castles[castleId];
				if (player->teamIndex != castle->occupiedBy) setResponseAndSend(player, opcode, (char *) BUY_WALL_E_GONE, strlen(BUY_WALL_E_GONE), buff);
				else if (wallId == FENCE) {
					if (castle->wall->defense >= FENCE_DEF) setResponseAndSend(player, opcode, (char *) BUY_WALL_E_WEAKER, strlen(BUY_WALL_E_WEAKER), buff);
					else if (team->basedResources[WOOD] < FENCE_WOOD || team->basedResources[STONE] < FENCE_STONE || team->basedResources[IRON] < FENCE_IRON) setResponseAndSend(player, opcode, (char *) BUY_WALL_E_NOTENOUGH, strlen(BUY_WALL_E_NOTENOUGH), buff);
					else {
						setNewWall(team, castle, FENCE, FENCE_DEF, FENCE_WOOD, FENCE_STONE, FENCE_IRON);
						informBuyWall(game, player->gameIndex, castleId, wallId, (char *) UPDATE_GAME, (char *) UPDATE_GAME_BUY_WALL, buff);
					}
				}
				else if (wallId == WOOD_WALL) {
					if (castle->wall->defense >= WOOD_WALL_DEF) setResponseAndSend(player, opcode, (char *) BUY_WALL_E_WEAKER, strlen(BUY_WALL_E_WEAKER), buff);
					else if (team->basedResources[WOOD] < WOOD_WALL_WOOD || team->basedResources[STONE] < WOOD_WALL_STONE || team->basedResources[IRON] < WOOD_WALL_IRON) setResponseAndSend(player, opcode, (char *) BUY_WALL_E_NOTENOUGH, strlen(BUY_WALL_E_NOTENOUGH), buff);
					else {
						setNewWall(team, castle, WOOD_WALL, WOOD_WALL_DEF, WOOD_WALL_WOOD, WOOD_WALL_STONE, WOOD_WALL_IRON);
						informBuyWall(game, player->gameIndex, castleId, wallId, (char *) UPDATE_GAME, (char *) UPDATE_GAME_BUY_WALL, buff);
					}
				}
				else if (wallId == STONE_WALL) {
					if (castle->wall->defense >= STONE_WALL_DEF) setResponseAndSend(player, opcode, (char *) BUY_WALL_E_WEAKER, strlen(BUY_WALL_E_WEAKER), buff);
					else if (team->basedResources[WOOD] < STONE_WALL_WOOD || team->basedResources[STONE] < STONE_WALL_STONE || team->basedResources[IRON] < STONE_WALL_IRON) setResponseAndSend(player, opcode, (char *) BUY_WALL_E_NOTENOUGH, strlen(BUY_WALL_E_NOTENOUGH), buff);
					else {
						setNewWall(team, castle, STONE_WALL, STONE_WALL_DEF, STONE_WALL_WOOD, STONE_WALL_STONE, STONE_WALL_IRON);
						informBuyWall(game, player->gameIndex, castleId, wallId, (char *) UPDATE_GAME, (char *) UPDATE_GAME_BUY_WALL, buff);
					}
				}
				else if (wallId == LEGEND_WALL) {
					if (castle->wall->defense >= LEGEND_WALL_DEF) setResponseAndSend(player, opcode, (char *) BUY_WALL_E_WEAKER, strlen(BUY_WALL_E_WEAKER), buff);
					else if (team->basedResources[WOOD] < LEGEND_WALL_WOOD || team->basedResources[STONE] < LEGEND_WALL_STONE || team->basedResources[IRON] < LEGEND_WALL_IRON) setResponseAndSend(player, opcode, (char *) BUY_WALL_E_NOTENOUGH, strlen(BUY_WALL_E_NOTENOUGH), buff);
					else {
						setNewWall(team, castle, LEGEND_WALL, LEGEND_WALL_DEF, LEGEND_WALL_WOOD, LEGEND_WALL_STONE, LEGEND_WALL_IRON);
						informBuyWall(game, player->gameIndex, castleId, wallId, (char *) UPDATE_GAME, (char *) UPDATE_GAME_BUY_WALL, buff);
					}
				}
				LeaveCriticalSection(&game->criticalSection);
			}
		}
	}
	LeaveCriticalSection(&player->criticalSection);
}

/* The setNewWall function handle a buy wall from player
* @param	team		[IN]		Team buy wall
* @param	castle		[IN]		Castle equip new wall
* @param	wallId		[IN]		Wall Id
* @param	wallAtk		[IN]		Wall defense
* @param	wallWood	[IN]		Wood cost of wall
* @param	wallStone	[IN]		Stone cost of wall
* @param	wallIron	[IN]		Iron cost of wall
* @return	Nothing
*/
void setNewWall(TEAM team, CASTLE castle, int wallId, int wallDefense, int wallWood, int wallStone, int wallIron) {
	castle->wall->type = wallId;
	castle->wall->defense = wallDefense;
	team->basedResources[WOOD] -= wallWood;
	team->basedResources[STONE] -= wallStone;
	team->basedResources[IRON] -= wallIron;
}

/* The informBuyWall function inform all player that someone just buy wall
* @param	game				[IN]		Game
* @param	playerIndex			[IN]		Place of request player in team
* @param	castleId			[IN]		Castle equip new wall
* @param	wallId				[IN]		Wall id
* @param	opcode				[IN]		Operation code
* @param	responseCode		[IN]		Response code for request
* @param	buff				[IN/OUT]	Buffer to store result
* @return	Nothing
*/
void informBuyWall(GAME game, int playerIndex, int castleId, int wallId, char *opcode, char *responseCode, char *buff) {
	memset(buff, 0, BUFF_SIZE);
	strcpy_s(buff + HEADER_SIZE, BUFF_SIZE, responseCode);
	strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
	int tempLen = BUFFLEN;
	buff[BUFFLEN] = playerIndex + 48;
	buff[tempLen + 1] = 0;
	strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
	_itoa_s(castleId, buff + BUFFLEN, BUFF_SIZE, 10);
	strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
	_itoa_s(game->castles[castleId]->wall->type, buff + BUFFLEN, BUFF_SIZE, 10);
	strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
	_itoa_s(game->players[playerIndex]->teamIndex, buff + BUFFLEN, BUFF_SIZE, 10);
	setResponse(opcode, buff + HEADER_SIZE, strlen(buff + HEADER_SIZE), buff);
	sendToAllPlayersInGameRoom(game, buff);
};

/* The handleCheat function handle a cheat request from player
* @param	player		[IN/OUT]	Request player
* @param	opcode		[IN/OUT]	Operation code
* @param	buff		[IN/OUT]	Buffer to store game info
* @return	Nothing
*/
void handleCheat(PLAYER player, char *opcode, char *buff) {
	while (!TryEnterCriticalSection(&player->criticalSection)) {}
	if (player->game == NULL) {
		setResponseAndSend(player, opcode, (char *) BUY_WALL_E_NOTPLAYING, strlen(BUY_WALL_E_NOTPLAYING), buff);
		LeaveCriticalSection(&player->criticalSection);
		return;
	}
	if (player->state != PLAYING) setResponseAndSend(player, opcode, (char *) CHEAT_E_NOTPLAYING, strlen(CHEAT_E_NOTPLAYING), buff);
	else {
		while (!TryEnterCriticalSection(&player->game->criticalSection)) {}
		GAME game = player->game;
		TEAM team = game->teams[player->teamIndex];
		bool isOverMaxAmount = false;
		for (int i = 0; i < RESOURCE_NUM; i++)
			if (team->basedResources[i] + CHEAT_AMOUNT > MAX_AMOUNT) {
				setResponseAndSend(player, opcode, (char *) CHEAT_E_GREEDY, strlen(CHEAT_E_GREEDY), buff);
				isOverMaxAmount = true;
			}
		if (isOverMaxAmount == false) {
			for (int i = 0; i < RESOURCE_NUM; i++) team->basedResources[i] += CHEAT_AMOUNT;
			informCheat(game, player->gameIndex, (char *) UPDATE_GAME, (char *) UPDATE_GAME_CHEAT, buff);
		}
		LeaveCriticalSection(&player->game->criticalSection);
	}
	LeaveCriticalSection(&player->criticalSection);
}

/* The informCheat function inform all player that someone just cheat
* @param	game				[IN]		Game
* @param	playerIndex			[IN]		Place of request player in team
* @param	opcode				[IN]		Operation code
* @param	responseCode		[IN]		Response code for request
* @param	buff				[IN/OUT]	Buffer to store result
* @return	Nothing
*/

void informCheat(GAME game, int playerIndex, char *opcode, char *responseCode, char *buff) {
	memset(buff, 0, BUFF_SIZE);
	strcpy_s(buff + HEADER_SIZE, BUFF_SIZE, responseCode);
	strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
	int tempLen = BUFFLEN;
	buff[BUFFLEN] = playerIndex + 48;
	buff[tempLen + 1] = 0;
	strcat_s(buff + BUFFLEN, BUFF_SIZE, "#");
	_itoa_s(game->players[playerIndex]->teamIndex, buff + BUFFLEN, BUFF_SIZE, 10);
	setResponse(opcode, buff + HEADER_SIZE, strlen(buff + HEADER_SIZE), buff);
	sendToAllPlayersInGameRoom(game, buff);
}

/* The informUpdate function inform resource update to all player
* @param	game				[IN]		Game
* @param	requestPlayer		[IN]		Place of request player in team
* @param	buff				[IN/OUT]	Buffer to store result
* @return	Nothing
*/
void informUpdate(GAME game, char *opcode, char *buff) {
	memset(buff, 0, BUFF_SIZE);
	getGameProperties(game, buff + HEADER_SIZE);
	buff[strlen(buff) - 1] = 0;
	setResponse(opcode, buff + HEADER_SIZE, strlen(buff + HEADER_SIZE), buff);
	sendToAllPlayersInGameRoom(game, buff);
};

/* The informEndGame function inform endgame signal to all player
* @param	game				[IN]		Game
* @param	requestPlayer		[IN]		Place of request player in team
* @param	responseCode		[IN]		Response code for request
* @param	buff				[IN/OUT]	Buffer to store result
* @return	Nothing
*/
void informEndGame(GAME game, char *opcode, char* responseCode, char *buff) {
	memset(buff, 0, BUFF_SIZE);
	strcpy_s(buff + HEADER_SIZE, BUFF_SIZE, responseCode);
	setResponse(opcode, buff + HEADER_SIZE, strlen(buff + HEADER_SIZE), buff);
	sendToAllPlayersInGameRoom(game, buff);
};
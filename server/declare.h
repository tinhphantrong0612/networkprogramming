#pragma once

typedef struct _wall	*WALL;
typedef struct _weapon	*WEAPON;
typedef struct _castle	*CASTLE;
typedef struct _mine	*MINE;
typedef struct _player	*PLAYER;
typedef struct _team	*TEAM;
typedef struct _game	*GAME;

char*			calculateATeam(TEAM, char *);
char*			calculateACastle(CASTLE, char *);
char*			calculateAMine(MINE, char *);
char*			calculateGame(GAME, char *);
void			loadAccountMap(char *);
void			addNewAccount(char *, char *, char *);
void			Swap(PLAYER, PLAYER, WSAEVENT, WSAEVENT);
int				Communicate(PLAYER);
int				Send(PLAYER, char *, int, int);
int				Receive(PLAYER, char *, int, int);
int				receiveAndProcessPayload(PLAYER, char *, int, char *);
int				handleLogin(PLAYER, char *, char *);
int				handleSignUp(PLAYER, char *, char *);
int				handleCreateGame(PLAYER, char *, char *);
int				handleGetLobby(PLAYER, char *, char *);
int				handleJoinGame(PLAYER, char *, char *);
int				setResponseAndSend(PLAYER, char *, char *, int, char *);
void			emptyGame(GAME);
void			getLobbyList(char *);
void			getGameInfo(GAME, char *);
long long		getTime();
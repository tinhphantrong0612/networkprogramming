#pragma once

typedef struct _wall	*WALL;
typedef struct _weapon	*WEAPON;
typedef struct _castle	*CASTLE;
typedef struct _mine	*MINE;
typedef struct _player	*PLAYER;
typedef struct _team	*TEAM;
typedef struct _game	*GAME;

char*			calculateATeam(TEAM team, char *buff);
char*			calculateACastle(CASTLE castle, char *buff);
char*			calculateAMine(MINE mine, char *buff);
char*			calculateGame(GAME game, char *buff);
void			Swap(PLAYER, PLAYER, WSAEVENT, WSAEVENT);
int				Communicate(PLAYER);
int				Send(PLAYER, char *, int, int);
int				Receive(PLAYER, char *, int, int);
long long		getTime();
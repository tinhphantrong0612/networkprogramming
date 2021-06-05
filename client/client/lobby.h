#include "stream.h"
#include "auth.h"

class Lobby {
public:
	int id;
	int team_number;
	int current_number_player;
	User creator;
	User members[MAX_NUM_PLAYER];
	int state;

	Lobby();
	Lobby(int id, int team_number);
	~Lobby();

	static Lobby create_lobby(Socket& socket, int team_number);
	static void join_lobby(Socket& socket, char* id);
};
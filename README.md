# Design of network
## The resquest/response structure
| Code | Length | Payload|
|---|---|---|
|2 bytes|2 bytes| max 2048 bytes|


## CODE
``` c++
01: LOGIN
02: SIGNUP
03: CREATE_GAME
04: GET_LOBBY
05: JOIN_GAME
06: CHANGE_TEAM
07: READY_PLAY
08: UNREADY_PLAY
09: QUIT_GAME
10: START_GAME
11: LOGOUT
12: ATTACK_CASTLE
13: ATTACK_MINE
14: BUY_WEAPON
15: BUY_WALL
16: UPDATE_CASTLE_QUESTION // From server only
17: UPDATE_MINE_QUESTION // From server only
18: TIMELY_UPDATE // From server only
```

## Request/Success response structure
### Login
``` c++
01|strlen(data)|<username> <password>
01|strlen(data)|<result_code>
```
### Sign up
```c++
02|strlen(data)|<username> <password>
02|strlen(data)|<result_code>
```
### Create lobby
```c++
03|strlen(data)|<team_number>
03|strlen(data)|<result_code> <game_id>
```
### Get lobby
```c++
04|strlen(data)|<null> 
04|strlen(data)|<result_code> [<game_id> <team_number> <team-player-string>]*
```
`game_id` is 13 bytes, `team_number` is 1 bytes, `team-player-string` is 12 bytes  
`<team-player-string>` example: player 0, 3, 4 in team 0, player 2, 6, 7 in team 1, player 8, 10 in team 2 and 11 in team 3 then `<team-player-string>` is `0x100x112x23`
### Join lobby
```c++
05|strlen(data)|<game_id> <team_id>
05|strlen(data)|<result_code> <game_id> <request_player_ingame_id> <team-player-string> [<player_ingame_id> <player_name> <player_state>]*
```
`player_ingame_id` is player's index in players array in game struct
Whenever a player joins a lobby successfully, server sends update to all players in that lobby
```c++
05|strlen(data)|<result_code> <game_id> <request_player_ingame_id> <team-player-string> [<player_ingame_id> <player_name> <player_state>]*
```
### Change team
```c++
06|strlen(data)|<team_id>
06|strlen(data)|<result_code> <game_id> <request_player_ingame_id> <team-player-string> [<player_ingame_id> <player_name> <player_state>]*
```
Whenever a player changes team successfully, server sends update to all players in that lobby
```c++
06|strlen(data)|<result_code> <game_id> <request_player_ingame_id> <team-player-string> [<player_ingame_id> <player_name> <player_state>]*
```
### Ready
```c++
07|strlen(data)|<none>
07|strlen(data)|<result_code> <game_id> <request_player_ingame_id> <team-player-string> [<player_ingame_id> <player_name> <player_state>]*
```
Whenever a player is ready, server sends update to all players in that lobby
```c++
07|strlen(data)|<result_code> <game_id> <request_player_ingame_id> <team-player-string> [<player_ingame_id> <player_name> <player_state>]*
```
### Unready
```c++
08|strlen(data)|<none>
08|strlen(data)|<result_code> <game_id> <request_player_ingame_id> <team-player-string> [<player_ingame_id> <player_name> <player_state>]*
```
Whenever a player is unready, server sends update to all players in that lobby
```c++
08|strlen(data)|<result_code> <game_id> <request_player_ingame_id> <team-player-string> [<player_ingame_id> <player_name> <player_state>]*
```
### Quit Game
```c++
09|strlen(data)|<none>
09|strlen(data)|<result_code>
```
Whenever a player is quit game or disconnect, server sends update to all players in that lobby
```c++
09|strlen(data)|<result_code> <game_id> <request_player_ingame_id> <team-player-string> [<player_ingame_id> <player_name> <player_state>]*
```
### Start Game
```c++
10|strlen(data)|<none>
10|strlen(data)|<result_code> <game_id>
```
Whenever host starts game successfully, server sends update to all players in that lobby
```c++
10|strlen(data)|<result_code> <game_id>
```
And sends questions to all players in that lobby
```c++
16|strlen(data)|<game_id> <castle_id> <question_id> <question> [<answer>]*
17|strlen(data)|<game_id> <mine_id> <type> <question_id> <question> [<answer>]*
```
### Log Out
Only when player is not in any game.
```c++
11|strlen(data)|<none>
11|strlen(data)|<result_code>
```
### Attack castle
```c++
12|strlen(data)|<castle_id> <question_id> <answer_id>
```
Whenever a player answers a castle question, server sends result and new question to players
```c++
12|strlen(data)|<result_code> <game_id> <castle_id> <request_player_ingame_id> [<occupied_by> <wall_type> <wall_def>]* [<wood> <stone> <iron>]* [<weapon_type> <weapon_atk> <gold> <wood> <stone> <iron>]*
16|strlen(data)|<game_id> <castle_id> <question_id> <question> [<answer>]*
```

### Attack mine
```c++
13|strlen(data)|<mine_id> <type> <question_id> <answer_id>
```
Whenever a player answers a castle question, server sends result and new question to all players
```c++
13|strlen(data)|<result_code> <game_id> <mine_id> <type> <request_player_ingame_id> [<occupied_by> <wall_type> <wall_def>]* [<wood> <stone> <iron>]* [<weapon_type> <weapon_atk> <gold> <wood> <stone> <iron>]*
17|strlen(data)|<game_id> <mine_id> <type> <question_id> <question> [<answer>]*
```
### Buy weapon
```c++
14|strlen(data)|<weapon_id>
```
Whenever a player answers a castle question, server sends result and new question to all players
```c++
14|strlen(data)|<result_code> <game_id> <request_player_ingame_id> [<occupied_by> <wall_type> <wall_def>]* [<wood> <stone> <iron>]* [<weapon_type> <weapon_atk> <gold> <wood> <stone> <iron>]*
```
### Buy wall
```c++
15|strlen(data)|<castle_id> <wall_id>
```
Whenever a player answers a castle question, server sends result and new question to players
```c++
15|strlen(data)|<result_code> <game_id> <request_player_ingame_id> [<occupied_by> <wall_type> <wall_def>]* [<wood> <stone> <iron>]* [<weapon_type> <weapon_atk> <gold> <wood> <stone> <iron>]*
```

### Timely update
```c++
18|strlen(data)|<game_id> [<occupied_by> <wall_type> <wall_def>]* [<wood> <stone> <iron>]* [<weapon_type> <weapon_atk> <gold> <wood> <stone> <iron>]*
```

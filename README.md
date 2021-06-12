# Design of network
## The resquest/response structure
| Code | Length | Payload|
|---|---|---|
|3 bytes|2 bytes| 8000 bytes|

## SOME CONSTANT
```c++
0: WOOD
1: STONE
2: IRON

0: NO_WALL
1: FENCE
2: WOOD_WALL
3: STONE_WALL
4: LEGEND_WALL

// Wall defense
0:    NO_WALL_DEF				
200:  FENCE_DEF				
1000: WOOD_WALL_DEF			
3000: STONE_WALL_DEF			
8000: LEGEND_WALL_DEF		

// Wall's wood price
0:    NO_WALL_WOOD			
200:  FENCE_WOOD				
1000: WOOD_WALL_WOOD			
200:  STONE_WALL_WOOD			
1000: LEGEND_WALL_WOOD		

// Wall's stone price
5:    NO_WALL_STONE			
50:   FENCE_STONE				
100:  WOOD_WALL_STONE		
1000: STONE_WALL_STONE		
2000: LEGEND_WALL_STONE		

// Wall's iron price
0:    NO_WALL_IRON			
50:   FENCE_IRON
100:  WOOD_WALL_IRON			
1000: STONE_WALL_IRON			
2000: LEGEND_WALL_IRON		


0: NO_WEAPON
1: BALLISTA
2: CATAPULT
3: CANNON

// Weapon attack
0:    NO_WEAPON_ATK			
1000: BALLISTA_ATK			
3000: CATAPULT_ATK			
8000: CANNON_ATK				

// Weapon's wood price
0:    NO_WEAPON_WOOD	
1500: BALLISTA_WOOD	
400:  CATAPULT_WOOD	
500:  CANNON_WOOD	

// Weapon's stone price
0:    NO_WEAPON_STONE		
0:    BALLISTA_STONE		
1500: CATAPULT_STONE		
2500: CANNON_STONE		

// Weapon's iron price
0:    NO_WEAPON_IRON			
200:  BALLISTA_IRON			
300:  CATAPULT_IRON			
1800: CANNON_IRON				
```
``` C++
// Universal
000: UNKNOWN_HEADER - response 000|length|<none>
// Outgame - Request header
100: LOGIN
101: SIGNUP
102: LOGOUT
103: CREATE_GAME
104: GET_LOBBY
105: JOIN_GAME

// In lobby - Request header
200: READY_PLAY
201: UNREADY_PLAY
202: START_GAME
203: QUIT_GAME
204: CHANGE_TEAM

// Ingame - Request header
300: ATTACK_CASTLE
301: ATTACK_MINE
302: BUY_WEAPON
303: BUY_WALL

// Update header - Server send back only
400: TIMELY_UPDATE
401: UPDATE_GAME
402: UPDATE_LOBBY

// Outgame - Response

// Ingame - Response header
40100: UPDATE_GAME_START
40101: UPDATE_GAME_CSTQUEST
40102: UPDATE_GAME_MINEQUEST
40103: UPDATE_GAME_ATK_CST_R
40104: UPDATE_GAME_ATK_MINE_R
40105: UPDATE_GAME_ATK_CST_W
40106: UPDATE_GAME_ATK_MINE_W
40107: UPDATE_GAME_BUY_WPN
40108: UPDATE_GAME_BUY_WALL

40200: UPDATE_LOBBY_QUIT
40201: UPDATE_LOBBY_JOIN
40202: UPDATE_LOBBY_CHANGETEAM
40203: UPDATE_LOBBY_READY
40204: UPDATE_LOBBY_UNREADY
```
## Request/Success response structure
### Login
``` c++
100|strlen(data)|<username>#<password>
100|strlen(data)|<result_code>
```
Result code:
``` c++
10000: LOGIN_SUCCESS
10001: LOGIN_E_ALREADY
10002: LOGIN_E_ELSEWHERE
10003: LOGIN_E_PASSWORD
10004: LOGIN_E_NOTEXIST
```
### Sign up
```c++
101|strlen(data)|<username>#<password>
101|strlen(data)|<result_code>
```
Result code:
``` c++
10100: SIGNUP_SUCCESS
10101: SIGNUP_E_LOGGEDIN
10102: SIGNUP_E_FORMAT
10103: SIGNUP_E_EXIST
```
### Log Out
Only when player is not in any game.
```c++
102|strlen(data)|<none>
102|strlen(data)|<result_code>
```
Result code:
```c++
10200: LOGOUT_SUCCESS
10201: LOGOUT_E_NOTAUTH
10202: LOGOUT_E_INGAME
```

### Create lobby
```c++
103|strlen(data)|<team_number>
103|strlen(data)|<result_code>#<game_id>
```
Result code:
``` c++
10300: CREATE_SUCCESS
10301: CREATE_E_NOTAUTH
10302: CREATE_E_INGAME
10303: CREATE_E_FULLGAME
10304: CREATE_E_INVALIDTEAM
```
### Get lobby
```c++
104|strlen(data)|<null> 
104|strlen(data)|<result_code>#[<game_id>#<team_number>#<team-player-string>]*
```
Result code:
``` C++
10400: LOBBY_SUCCESS
10401: LOBBY_E_NOTAUTH
10402: LOBBY_E_INGAME
```
`game_id` is 13 bytes, `team_number` is 1 bytes, `team-player-string` is 12 bytes  
`<team-player-string>` example: player 0, 3, 4 in team 0, player 2, 6, 7 in team 1, player 8, 10 in team 2 and 11 in team 3 then `<team-player-string>` is `0x100x112x23`  
Example: "04xx040#1622867470450#2#0x100x11xxxx#1622867475670#3#0x20xx11xx2x#"
### Join lobby
```c++
105|strlen(data)|<game_id>#<team_id>
```
Result code:
```C++
//10500: JOIN_SUCCESS // Using UPDATE_LOBBY_JOIN instead
10501: JOIN_E_NOTAUTH
10502: JOIN_E_ALREADY
10503: JOIN_E_FORMAT
10504: JOIN_E_FULLGAME
10505: JOIN_E_FULLTEAM
10506: JOIN_E_NOGAME
10507: JOIN_E_NOTEAM
10508: JOIN_E_PLAYING
```
`player_ingame_id` and `request_player_ingame_id` is player's index in players array in game struct, and using a ASCII character, from '0' to ';' in ASCII table, subtract 48 when receive  
`player_state` is similar, subtract 48 when receive
Whenever a player joins a lobby successfully, server sends update to all players in that lobby  
```c++
402|strlen(data)|UPDATE_LOBBY_JOIN#<team_number>#<request_player_ingame_id>#[<player_ingame_id>#<player_name>#<player_state>#<team>]*
```
### Ready
```c++
200|strlen(data)|<none>
```
Result code:
```
//20000: READY_SUCCESS // Using UPDATE_LOBBY_READY instead
20001: READY_E_NOTAUTH
20002: READY_E_NOTINGAME
20003: READY_E_ALREADY
20004: READY_E_PLAYING
20005: READY_E_HOST
```
Whenever a player is ready, server sends update to all players in that lobby
```c++
402|strlen(data)|UPDATE_LOBBY_READY#<team_number>#<request_player_ingame_id>#[<player_ingame_id>#<player_name>#<player_state>#<team>]*
```
### Unready
```c++
201|strlen(data)|<none>
```
Result code:
```
//20100: UNREADY_SUCCESS // Using UPDATE_GAME_UNREADY instead
20101: UNREADY_E_NOTAUTH
20102: UNREADY_E_NOTINGAME
20103: UNREADY_E_ALREADY
20104: UNREADY_E_PLAYING
20105: UNREADY_E_HOST
```
Whenever a player is unready, server sends update to all players in that lobby
```c++
402|strlen(data)|UPDATE_LOBBY_UNREADY#<team_number>#<request_player_ingame_id>#[<player_ingame_id>#<player_name>#<player_state>#<team>]*
```
### Start Game
```c++
15|strlen(data)|<none>
```
Result code:
```
//20200: START_SUCCESS // Using UPDATE_GAME_START instead
20201: START_E_NOTAUTH
20202: START_E_NOTINGAME
20203: START_E_NOTALLREADY
20204: START_E_PLAYING
20205: START_E_NOTHOST
20206: START_E_ONETEAM
```
Whenever host starts game successfully, server sends update to all players in that lobby
```c++
401|strlen(data)|UPDATE_GAME_START
```
And sends questions to all players in that lobby
```c++
401|strlen(data)|UPDATE_GAME_CASTQUEST#<castle_id>#<question_id>#<question>#<answer>#<answer>#<answer>#<answer>
401|strlen(data)|UPDATE_GAME_MINEQUEST#<mine_type_id>#<question_id>#<question>#<answer>#<answer>#<answer>#<answer>
```
`mine_type_id` = `mine_id * 3 + type`, `mine_id` from 0 to 5, `type` from 0 to 2, Wood->stone->iron, when receive need to subtract 48
### Quit Game
```c++
14|strlen(data)|<none>
```
Result code:
```
20300: QUIT_SUCCESS	// Using to inform player quit success, and using UPDATE_LOBBY_QUIT to inform all player in that game room
20301: QUIT_E_NOTAUTH
20302: QUIT_E_NOTINGAME
20303: QUIT_E_READY
```
Whenever a player is quit game or disconnect, server sends update to all players in that lobby
```c++
402|strlen(data)|UPDATE_LOBBY_DISCONNECT#<team_number>#<request_player_ingame_id>#[<player_ingame_id>#<player_name>#<player_state>#<team>]*
```
### Change team
```c++
11|strlen(data)|<team_id>
```
Result code:
``` C++
//20400: CHANGE_SUCCESS	// Using UPDATE_LOBBY_CHANGE to inform all other player
20401: CHANGE_E_NOTAUTH
20402: CHANGE_E_NOTINGAME
20403: CHANGE_E_FULL
20404: CHANGE_E_READY
20405: CHANGE_E_PLAYING
20406: CHANGE_E_UNKNOWNTEAM
20407: CHANGE_E_CURRENTTEAM
```
Whenever a player changes team successfully, server sends update to all players in that lobby
```c++
402|strlen(data)|UPDATE_LOBBY_CHANGETEAM#<team_number>#<request_player_ingame_id>#[<player_ingame_id>#<player_name>#<player_state>#<team>]*
```
### Attack castle
```c++
300|strlen(data)|<castle_id>#<question_id>#<answer_id>
```
Whenever a player answers a castle question, server sends result and new question to players
```c++
401|strlen(data)|UPDATE_GAME_ATK_CST_W/R#<request_player_ingame_id>#<castle_id>#[<occupied_by>#<wall_type>#<wall_def>]*3#[<weapon_type>#<weapon_atk>#<gold>#<wood>#<stone>#<iron>]*4#<question_id>#<question>#<answer>#<answer>#<answer>#<answer>
```
`request_player_ingame_id` is request player's ingame index from 0 to 11, subtract 48 when receive  
`castle_id` is target castle, 0 to 2, subtract 48 when receive  
`[<occupied_by>#<wall_type>#<wall_def>]*3` is three castle's info  
	- `occupied_by` is team that occupied the castle, 0 to 4, 4 is unoccupied, subtract 48 when receive  
	- `wall_type` is type of wall at that castle, 0 to 4, subtract 48 when receive  
	- `wall_def` is defense of the wall, atoi when receive  
`[<weapon_type>#<weapon_atk># <gold>#<wood>#<stone>#<iron>]*4` is 4 castle info  
	- `weapon_id` is similar to `wall_type`
	- `weapon_atk` is similar to `wall_def`
	- `<gold>#<wood>#<stone>#<iron>` use atoi  
`<question_id>#<question>#<answer>#<answer>#<answer>#<answer>` is question id, question, and 4 answer
Result code:
```
//30000: ATK_CST_SUCCESS // Using UPDATE_MINE_ATK_CST_R
30001: ATK_CST_E_TOOLATE // Answer the question too late
30002: ATK_CST_E_TOOWEAK // Enemy build a better wall
30003: ATK_CST_E_YOURS // Guess your teammate got it first
30004: ATK_CST_E_NOTPLAYING	// Either game or player is not playing
30005: ATK_CST_E_FORMAT
//30006: ATK_CST_E_WRONG // Using UPDATE_MINE_ATK_CST_W
```

### Attack mine
```c++
301|strlen(data)|<mine_id>#<type>#<question_id>#<answer_id>
```
Whenever a player answers a castle question, server sends result and new question to all players
```c++
401|strlen(data)|UPDATE_GAME_ATK_MINE_W/R#<request_player_ingame_id>#<mine_type_id>#[<wood>#<stone>#<iron>]*6#[<weapon_type>#<weapon_atk>#<gold>#<wood>#<stone>#<iron>]*4#<question_id>#<question>#<answer>#<answer>#<answer>#<answer>
```
`request_player_ingame_id` is request player's ingame index from 0 to 11, subtract 48 when receive  
`mine_type_id` = `mine_id * 3 + type`, `mine_id` from 0 to 5, `type` from 0 to 2, Wood->stone->iron, when receive need to subtract 48  
`[<wood>#<stone>#<iron>]*6` is 6 mine's info, atoi when receive  
`[<weapon_type>#<weapon_atk># <gold>#<wood>#<stone>#<iron>]*4` is 4 castle info  
	- `weapon_id` is similar to `wall_type`
	- `weapon_atk` is similar to `wall_def`
	- `<gold>#<wood>#<stone>#<iron>` use atoi  
`<question_id>#<question>#<answer>#<answer>#<answer>#<answer>` is question id, question, and 4 answer
``` C++
//30100: ATK_MINE_SUCCESS // Using UPDATE_MINE_ATK_MINE_R
30101: ATK_MINE_E_TOOLATE // Answer the question too late
30102: ATK_MINE_E_NOTPLAYING // Either game or player is not playing
30103: ATK_MINE_E_FORMAT
//30104: ATK_MINE_E_WRONG // Using UPDATE_MINE_ATK_MINE_W
```
### Buy weapon
```c++
302|strlen(data)|<weapon_id>
```
Whenever a player answers a castle question, server sends result and new question to all players
```c++
401|strlen(data)|UPDATE_GAME_BUY_WEAPON#<request_player_ingame_id>#<weapon_id>#[<weapon_type>#<weapon_atk>#<gold>#<wood>#<stone>#<iron>]*4
```
`request_player_ingame_id` is request player's ingame index from 0 to 11, subtract 48 when receive    
`weapon_id` is target castle, 0 to 3, subtract 48 when receive  
`[<occupied_by>#<wall_type>#<wall_def>]*3` is three castle's info  
	- `occupied_by` is team that occupied the castle, 0 to 4, with 4 is unoccupied, subtract 48 when receive   
	- `wall_type` is type of wall at that castle, 0 to 4, subtract 48 when receive  
	- `wall_def` is defense of the wall, atoi when receive  
`[<weapon_type>#<weapon_atk># <gold>#<wood>#<stone>#<iron>]*4` is 4 castle info  
	- `weapon_id` is similar to `wall_type`
	- `weapon_atk` is similar to `wall_def`
	- `<gold>#<wood>#<stone>#<iron>` use atoi  
Result code:
``` C++
//30200: BUY_WEAPON_SUCCESS // Using UPDATE_GAME_BUY_WPN
30201: BUY_WEAPON_E_NOTENOUGH // Guess your teammate bought it first
30202: BUY_WEAPON_E_WEAKER // Can't buy a weaker weapon
30203: BUY_WEAPON_E_NOTPLAYING // Either game or player is not playing
30204: BUY_WEAPON_E_FORMAT
```
### Buy wall
```c++
303|strlen(data)|<castle_id>#<wall_id>
```
Whenever a player answers a castle question, server sends result and new question to players
```c++
401|strlen(data)|UPDATE_GAME_BUY_WALL#<request_player_ingame_id>#<castle_wall_id>#[<occupied_by>#<wall_type>#<wall_def>]*3#[<weapon_type>#<weapon_atk>#<gold>#<wood>#<stone>#<iron>]*4
```
`request_player_ingame_id` is request player's ingame index from 0 to 11, subtract 48 when receive  
`castle_wall_id` = `castle_id * 5 + wall_id`, `castle_id` from 0 to 2, `wall_id` from 0 to 4, when receive need to subtract 48
`[<occupied_by>#<wall_type>#<wall_def>]*3` is three castle's info  
	- `occupied_by` is team that occupied the castle, 0 to 4, with 4 is unoccupied, subtract 48 when receive  
	- `wall_type` is type of wall at that castle, 0 to 4, subtract 48 when receive  
	- `wall_def` is defense of the wall, atoi when receive  
`[<weapon_type>#<weapon_atk># <gold>#<wood>#<stone>#<iron>]*4` is 4 castle info  
	- `weapon_id` is similar to `wall_type`
	- `weapon_atk` is similar to `wall_def`
	- `<gold>#<wood>#<stone>#<iron>` use atoi 
Result code: 
``` C++
//30300: BUY_WALL_SUCCESS // Using UPDATE_GAME_BUY_WALL
30301: BUY_WALL_E_NOTENOUGH	// Guess your teammate bought it first
30302: BUY_WALL_E_WEAKER // Can't buy a weaker wall
30303: BUY_WALL_E_GONE // Castle has been taken by enemy
30304: BUY_WALL_E_NOTPLAYING // Either game or player is not playing
30305: BUY_WALL_E_FORMAT
```
### Timely update
```c++
400|strlen(data)|[<occupied_by>#<wall_type>#<wall_def>]*#[<wood>#<stone>#<iron>]*#[<weapon_type>#<weapon_atk>#<gold>#<wood>#<stone>#<iron>]*
```
`[<occupied_by>#<wall_type>#<wall_def>]*3` is three castle's info  
	- `occupied_by` is team that occupied the castle, 0 to 4, with 4 is unoccupied, subtract 48 when receive  
	- `wall_type` is type of wall at that castle, 0 to 4, subtract 48 when receive  
	- `wall_def` is defense of the wall, atoi when receive  
`[<wood>#<stone>#<iron>]*6` is 6 mine's info, atoi when receive  
`[<weapon_type>#<weapon_atk># <gold>#<wood>#<stone>#<iron>]*4` is 4 castle info   
	- `weapon_id` is similar to `wall_type`
	- `weapon_atk` is similar to `wall_def`
	- `<gold>#<wood>#<stone>#<iron>` use atoi 

# Design of network
## The resquest/response structure
| Code | Length | Payload|
|---|---|---|
|2 bytes|2 bytes| 8000 bytes|

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
19: UPDATE_GAME // From server only
20: UPDATE_LOBBY // From server only
```

## RESPONSE CODE FROM SERVER
```c++
190: UPDATE_GAME_START
191: UDPATE_GAME_CASTQUEST
192: UPDATE_GAME_MINEQUEST
193: UPDATE_GAME_ATTACK_CST_R
194: UPDATE_GAME_ATTACK_MINE_R
195: UPDATE_GAME_ATTACK_CST_W
196: UPDATE_GAME_ATTACK_MINE_W
197: UPDATE_GAME_BUY_WPN
198: UPDATE_GAME_BUY_WALL

200: UPDATE_LOBBY_DISCONNECT
201: UPDATE_LOBBY_JOIN
202: UPDATE_LOBBY_CHANGETEAM
203: UPDATE_LOBBY_READY
204: UPDATE_LOBBY_UNREADY
```
## Request/Success response structure
### Login
``` c++
01|strlen(data)|<username>#<password>
01|strlen(data)|<result_code>
```
Result code:
``` c++
010: LOGIN_SUCCESS
011: LOGIN_E_ALREADY
012: LOGIN_E_ELSEWHERE
013: LOGIN_E_PASSWORD
014: LOGIN_E_NOTEXIST
```
### Sign up
```c++
02|strlen(data)|<username>#<password>
02|strlen(data)|<result_code>
```
Result code:
``` c++
020: SIGNUP_SUCCESS
021: SIGNUP_E_LOGGEDIN
022: SIGNUP_E_FORMAT
023: SIGNUP_E_EXIST
```
### Create lobby
```c++
03|strlen(data)|<team_number>
03|strlen(data)|<result_code>#<game_id>
```
Result code:
``` c++
030: CREATE_SUCCESS
031: CREATE_E_NOTAUTH	
032: CREATE_E_INGAME			
033: CREATE_E_FULLGAME		
034: CREATE_E_INVALIDTEAM
```
### Get lobby
```c++
04|strlen(data)|<null> 
04|strlen(data)|<result_code>#[<game_id>#<team_number>#<team-player-string>]*

040: LOBBY_SUCCESS		
041: LOBBY_E_NOTAUTH	
```
`game_id` is 13 bytes, `team_number` is 1 bytes, `team-player-string` is 12 bytes  
`<team-player-string>` example: player 0, 3, 4 in team 0, player 2, 6, 7 in team 1, player 8, 10 in team 2 and 11 in team 3 then `<team-player-string>` is `0x100x112x23`  
Example: "04xx040#1622867470450#2#0x100x11xxxx#1622867475670#3#0x20xx11xx2x#"
### Join lobby
```c++
05|strlen(data)|<game_id>#<team_id>

050: JOIN_SUCCESS			
051: JOIN_E_NOTAUTH		
052: JOIN_E_ALREADY			
053: JOIN_E_FORMAT			
054: JOIN_E_FULLGAME			
055: JOIN_E_FULLTEAM		
056: JOIN_E_NOGAME		
057: JOIN_E_NOTEAM	
058: JOIN_E_PLAYING // Game already start
```
`player_ingame_id` and `request_player_ingame_id` is player's index in players array in game struct, and using a ASCII character, from '0' to ';' in ASCII table, subtract 48 when receive  
`player_state` is similar, subtract 48 when receive
Whenever a player joins a lobby successfully, server sends update to all players in that lobby  
```c++
20|strlen(data)|UPDATE_LOBBY_JOIN#<team_number>#<request_player_ingame_id>#<team-player-string>#[<player_ingame_id>#<player_name>#<player_state>]*
```
`JOIN_E_NOGAME`, `JOIN_E_FULLGAME`, `JOIN_E_NOTEAM`, `JOIN_E_FULLTEAM` and `JOIN_E_PLAYING` response will have lobby list attach to update lobby list  
```c++
05|strlen(data)|<result_code>#[<game_id>#<team_number>#<team-player-string>]*
```
### Change team
```c++
06|strlen(data)|<team_id>

060: CHANGE_SUCCESS		
061: CHANGE_E_NOTAUTH	
062: CHANGE_E_NOTINGAME	
063: CHANGE_E_FULL		
064: CHANGE_E_READY		
065: CHANGE_E_PLAYING	
066: CHANGE_E_UNKNOWNTEAM
067: CHANGE_E_CURRENTTEAM
```
Whenever a player changes team successfully, server sends update to all players in that lobby
```c++
20|strlen(data)|UPDATE_LOBBY_CHANGETEAM#<team_number>#<request_player_ingame_id>#<team-player-string>#[<player_ingame_id>#<player_name>#<player_state>]*
```
### Ready
```c++
07|strlen(data)|<none>

070: READY_SUCCESS	
071: READY_E_NOTAUTH		
072: READY_E_NOTINGAME	
073: READY_E_ALREADY		
074: READY_E_PLAYING	
075: READY_E_HOST	
```
Whenever a player is ready, server sends update to all players in that lobby
```c++
20|strlen(data)|UPDATE_LOBBY_READY#<team_number>#<request_player_ingame_id>#<team-player-string>#[<player_ingame_id>#<player_name>#<player_state>]*
```
### Unready
```c++
08|strlen(data)|<none>

080: UNREADY_SUCCESS
081: UNREADY_E_NOTAUTH
082: UNREADY_E_NOTINGAME
083: UNREADY_E_ALREADY
084: UNREADY_E_PLAYING
085: UNREADY_E_HOST
```
Whenever a player is unready, server sends update to all players in that lobby
```c++
20|strlen(data)|UPDATE_LOBBY_UNREADY#<team_number>#<request_player_ingame_id>#<team-player-string>#[<player_ingame_id>#<player_name>#<player_state>]*
```
### Quit Game
```c++
09|strlen(data)|<none>

090: QUIT_SUCCESS
091: QUIT_E_NOTAUTH
092: QUIT_E_NOTINGAME
093: QUIT_E_READY
```
Whenever a player is quit game or disconnect, server sends update to all players in that lobby
```c++
20|strlen(data)|UPDATE_LOBBY_DISCONNECT#<team_number>#<request_player_ingame_id>#<team-player-string>#[<player_ingame_id>#<player_name>#<player_state>]*
```
### Start Game
```c++
10|strlen(data)|<none>

100: START_SUCCESS			
101: START_E_NOTAUTH	
102: START_E_NOTINGAME		
103: START_E_NOTALLREADY		
104: START_E_PLAYING		
105: START_E_NOTHOST
106: START_E_ONETEAM
```
Whenever host starts game successfully, server sends update to all players in that lobby
```c++
10|strlen(data)|190
```
And sends questions to all players in that lobby
```c++
16|strlen(data)|UPDATE_GAME_CASTQUEST#<castle_id>#<question_id>#<question>#<answer>#<answer>#<answer>#<answer>
17|strlen(data)|UPDATE_GAME_MINEQUEST#<mine_type_id>#<question_id>#<question>#<answer>#<answer>#<answer>#<answer>
```
`mine_type_id` = `mine_id * 3 + type`, `mine_id` from 0 to 5, `type` from 0 to 2, Wood->stone->iron, when receive need to subtract 48
### Log Out
Only when player is not in any game.
```c++
11|strlen(data)|<none>
11|strlen(data)|<result_code>

110: LOGOUT_SUCCESS
111: LOGOUT_E_NOTAUTH
112: LOGOUT_E_INGAME
```
### Attack castle
```c++
12|strlen(data)|<castle_id>#<question_id>#<answer_id>
```
Whenever a player answers a castle question, server sends result and new question to players
```c++
19|strlen(data)|UPDATE_GAME_ATK_CST_W/R#<request_player_ingame_id>#<castle_id>#[<occupied_by>#<wall_type>#<wall_def>]*#[<wood>#<stone>#<iron>]*#[<weapon_type>#<weapon_atk># <gold>#<wood>#<stone>#<iron>]*#<question_id>#<question>#<answer>#<answer>#<answer>#<answer>

120: ATK_CST_SUCCESS
121: ATK_CST_E_TOOLATE // Answer the question too late
122: ATK_CST_E_TOOWEAK // Enemy build a better wall
123: ATK_CST_E_YOURS // Your castle
124: ATK_CST_E_NOTPLAYING
125: ATK_CST_E_WRONG
126: ATK_CST_E_FORMAT
```

### Attack mine
```c++
13|strlen(data)|<mine_id>#<type>#<question_id>#<answer_id>
```
Whenever a player answers a castle question, server sends result and new question to all players
```c++
19|strlen(data)|UPDATE_GAME_ATK_MINE_W/R#<request_player_ingame_id>#<mine_type_id>#[<occupied_by>#<wall_type>#<wall_def>]*#[<wood>#<stone>#<iron>]*#[<weapon_type>#<weapon_atk>#<gold>#<wood>#<stone>#<iron>]*#<question_id>#<question>#<answer>#<answer>#<answer>#<answer>

130: ATK_MINE_SUCCESS
131: ATK_MINE_E_TOOLATE	// Answer the question too late
132: ATK_MINE_E_NOTPLAYING
133: ATK_MINE_E_WRONG
134: ATK_MINE_E_FORMAT
```
### Buy weapon
```c++
14|strlen(data)|<weapon_id>

140: BUY_WEAPON_SUCCESS
141: BUY_WEAPON_E_NOTENOUGH	// Not enough resources
142: BUY_WEAPON_E_WEAKER // Can't buy a weaker weapon
143: BUY_WEAPON_E_NOTPLAYING
```
Whenever a player answers a castle question, server sends result and new question to all players
```c++
19|strlen(data)|UPDATE_GAME_BUY_WEAPON#<request_player_ingame_id>#<weapon_id>#[<occupied_by>#<wall_type>#<wall_def>]*#[<wood>#<stone>#<iron>]*#[<weapon_type>#<weapon_atk>#<gold>#<wood>#<stone>#<iron>]*
```
### Buy wall
```c++
15|strlen(data)|<castle_id>#<wall_id>

150: BUY_WALL_SUCCESS
151: BUY_WALL_E_NOTENOUGH
152: BUY_WALL_E_WEAKER // Can't by weaker wall
153: BUY_WALL_E_GONE // Your castle is gone
154: BUY_WALL_E_NOTPLAYING
```
Whenever a player answers a castle question, server sends result and new question to players
```c++
19|strlen(data)|UPDATE_GAME_BUY_WALL#<request_player_ingame_id>#<castle_wall_id>#[<occupied_by>#<wall_type>#<wall_def>]*#[<wood>#<stone>#<iron>]*#[<weapon_type>#<weapon_atk>#<gold>#<wood>#<stone>#<iron>]*
```
`castle_wall_id` = `castle_id * 5 + wall_id`, `castle_id` from 0 to 2, `wall_id` from 0 to 4, when receive need to subtract 48
### Timely update
```c++
18|strlen(data)|[<occupied_by>#<wall_type>#<wall_def>]*#[<wood>#<stone>#<iron>]*#[<weapon_type>#<weapon_atk>#<gold>#<wood>#<stone>#<iron>]*
```

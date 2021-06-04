# Design of network
## The resquest/response structure
| Code | ID | Length | Payload|
|---|---|---|---|
|2 bytes|4 bytes |4 bytes| max 2048 bytes|


## CODE
``` c++
01: LOGIN
02: SIGNUP
03: CREATE_LOBBY
04: JOIN_LOBBY
05: CHOOSE_TEAM
06: CHOOSE_MINE
07: CHOOSE_CASTLE
08: CHOOSE_QUESTION
09: CHOOSE_ANSWER
10: ATTACK_CASTLE
11: EQUIP_WALL
```

## Request structure
### Login
``` c++
01 | nuLL     | strlen(data) |<username> <password>
```
### Sign up
```c++
02 | nuLL     | strlen(data) |<username> <password>
```
### Create lobby
```c++
03 | null     | strlen(data) |<team_number>
```
### Join lobby
```c++
04 | lobby_id | 0            |<null> 
```
### Join lobby
```c++
05 | lobby_id | 0            |<user_id> <team_id> 
```
### Choose mine
```c++
06 | lobby_id | strlen(data) |<user_id> <team_id> <mine_id>
```
### Choose castle
```c++
07 | lobby_id | strlen(data) |<user_id> <team_id> <castle_id>
```
### Choose question
```c++
08 | lobby_id | strlen(data) |<user_id> <team_id> <question_id>
```
### Answer question
```c++
09 | lobby_id | strlen(data) |<user_id> <team_id> <question_id> <answer_id>
```
### Attack castle
```c++
10 | lobby_id | strlen(data) |<user_id> <team_id> <weapon_id> <castle_id>
```
### Equip wall
```c++
11 | lobby_id | strlen(data) |<user_id> <team_id> <wall_id> <castle_id>
```



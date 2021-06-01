# Design of network
## The response
| Code | ID | Length | Payload|
|---|---|---|---|
|2 bytes|4 bytes |4 bytes| max 2048 bytes|


## CODE
``` c++
01: LOGIN
02: SIGNUP
03: CREATE_LOBBY
04: JOIN_LOBBY
```

## Request structure
### Login
``` c++
01 | nuLL     | strlen(data) |<username> <password>
```
### Sign up
```c+
02 | nuLL     | strlen(data) |<username> <password>
```
### Create lobby
```c+
03 | null     | strlen(data) |<team_number>
```
### Join lobby
```c+
04 | lobby_id | 0            |<null> 
```

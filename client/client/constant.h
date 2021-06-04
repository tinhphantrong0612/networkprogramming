#pragma once

//Buffer size
#define PAYLOAD_SIZE 2048
#define BUFF_SIZE 32000
#define ID_SIZE 4
#define PAYLOAD_LEN 4
#define TEAM_NUMBER_SIZE 1
#define USERNAME_LEN 256
#define ERROR_MESS_LEN 1024
#define NAME_LENGTH 256
#define QUESTION_LENGTH 256
#define ANSWER_LENGTH 256

// Boundery
#define MAX_NUM_PLAYER 12

//CODE
#define LOGIN "01"
#define SIGNUP "02"
#define CREATE_GAME "03"
#define GET_LOBBY "04"
#define JOIN_GAME "05"
#define CHANGE_TEAM "06"
#define READY_PLAY "07"
#define UNREADY_PLAY "08"
#define QUIT_GAME "09"
#define START_GAME "10"
#define LOGOUT "11"
#define ATTACK_CASTLE "12"
#define ATTACK_MINE "13"
#define BUY_WEAPON "14"
#define BUY_WALL "15"
#define UPDATE_CASTLE_QUESTION "16"
#define UPDATE_MINE_QUESTION "17"
#define TIMELY_UPDATE
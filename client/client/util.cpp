#include "stdafx.h"
#include "util.h"
#include "constant.h"
#include <stdlib.h>
#include <string.h>

void pack(char* code, char* payload, char* mess) {

	// Cast payload length -> string
	char payload_len[PAYLOAD_LEN_SIZE + 1];
	int len = strlen(payload);
	int first_byte = len / 256;
	int second_byte = len % 256;
	payload_len[0] = first_byte;
	payload_len[1] = second_byte;

	// Pack as 1 request
	strcat_s(mess, BUFF_SIZE, code);
	strcat_s(mess, BUFF_SIZE, payload_len);
	strcat_s(mess, BUFF_SIZE, payload);

}

void auth_payload(char* username, char* password, char* mess) {
	strcat_s(mess, PAYLOAD_SIZE, username);
	strcat_s(mess, PAYLOAD_SIZE, " ");
	strcat_s(mess, PAYLOAD_SIZE, password);
}

Auth auth_data(char* payload) {
	return Auth{ atoi(payload) };
}

Create_lobby lobby_data(char* payload) {
	char *next_token;
	int request_code = atoi(strtok_s(payload, DELIM_RESPONSE, &next_token));
	int id = atoi(strtok_s(NULL, DELIM_RESPONSE, &next_token));
	return Create_lobby{ request_code, id };
}
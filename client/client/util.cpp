#include "stdafx.h"
#include "util.h"
#include "constant.h"
#include <stdlib.h>
#include <string.h>

void pack(char* code, int id, char* payload, char* mess) {
	// Cast id -> string
	char id_str[ID_SIZE + 1];
	_itoa_s(id, id_str, ID_SIZE + 1, 10);
	int rest = ID_SIZE - strlen(id_str);
	for (int i = 0; i < rest; i++) {
		strcat_s(id_str, ID_SIZE + 1, " ");
	}

	// Cast payload length -> string
	char payload_len[PAYLOAD_LEN + 1];
	_itoa_s(id, payload_len, PAYLOAD_LEN + 1, 10);
	rest = PAYLOAD_LEN - strlen(payload_len);
	for (int i = 0; i < rest; i++) {
		strcat_s(payload_len, PAYLOAD_LEN + 1, " ");
	}

	// Pack as 1 request
	strcat_s(mess, BUFF_SIZE, code);
	strcat_s(mess, BUFF_SIZE, id_str);
	strcat_s(mess, BUFF_SIZE, payload_len);
	strcat_s(mess, BUFF_SIZE, payload);

}
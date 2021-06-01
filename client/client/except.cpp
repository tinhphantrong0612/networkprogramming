#include "stdafx.h"
#include "except.h"

ValidationError::ValidationError(char* msg) {
	strcpy_s(this->msg, ERROR_MESS_LEN, msg);
}

ValidationError::~ValidationError() {

}

const char* ValidationError::message() {
	return (const char*)this->msg;
}

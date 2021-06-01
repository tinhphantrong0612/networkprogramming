#include "stdafx.h"
#include <exception>
#include "constant.h"

class ValidationError : public std::exception {
private:
	char msg[ERROR_MESS_LEN];

public:
	ValidationError(char* msg);
	~ValidationError();

	const char* message();
};

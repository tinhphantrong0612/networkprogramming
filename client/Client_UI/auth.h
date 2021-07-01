#pragma once

#include "stream.h"
#include "qmessagebox.h"

class User {
public:
    char username[USERNAME_LEN + 1];
    int state;

    User();
    void login_request(Socket& socket, char* username, char* password);
    void signup_request(Socket& socket, char* username, char* password1, char* password2);
    void logout_request(Socket& socket);

    void login_response(char* payload);
    void signup_response(char* payload);
    void logout_response(char* payload);

    ~User();
};


#include "util.h"
#include "auth.h"

User::User() : state{ USER_NONAUTH } {
    strcpy_s(this->username, USERNAME_LEN, DEFAULT_USRNAME);
}

User::~User() {

}

void User::login_request(Socket& socket, char* username, char* password) {
    // Send login request
    char payload[PAYLOAD_SIZE + 1] = "";
    auth_payload(username, password, payload);
    socket.tcp_send((char*)LOGIN, payload);
    strcpy_s(this->username, USERNAME_LEN, username);
}

void User::signup_request(Socket& socket, char* username, char* password1, char* password2) {
    if (strcmp(password1, password2)) {
        // error message
    }
    // Send signup request
    char payload[PAYLOAD_SIZE + 1] = "";
    auth_payload(username, password1, payload);
    socket.tcp_send((char*)SIGNUP, payload);
    strcpy_s(this->username, USERNAME_LEN, username);
}

void User::login_response(char* payload) {
    Auth response = auth_data(payload);
    if (!strcmp(response.result_code, LOGIN_SUCCESS)){
        QMessageBox::information(nullptr,"Success","Login successful!",0);
        this->state = USER_AUTH;
    }
    else if (!strcmp(response.result_code, LOGIN_E_ELSEWHERE) || !strcmp(response.result_code, LOGIN_E_ALREADY)) {
        QMessageBox::information(nullptr,"Error","Already login or login by other client!",0);
    }
    else if (!strcmp(response.result_code, LOGIN_E_NOTEXIST) || !strcmp(response.result_code, LOGIN_E_PASSWORD)) {
        QMessageBox::information(nullptr,"Error","Username or password are wrong",0);
    }
    else {
        QMessageBox::information(nullptr,"Error","Invalid operation",0);
    }
}

void User::signup_response(char* payload) {
    Auth response = auth_data(payload);
    if (!strcmp(response.result_code, SIGNUP_SUCCESS))
        QMessageBox::information(nullptr,"Success","Register successful!",0);
    else if (!strcmp(response.result_code, SIGNUP_E_FORMAT) || !strcmp(response.result_code, SIGNUP_E_EXIST)) {
        QMessageBox::information(nullptr,"Error","Invalid username!",0);
    }
    else {
        QMessageBox::information(nullptr,"Error","Check password or username existed,...",0);
    }
}

void User::logout_request(Socket& socket) {
    socket.tcp_send((char*)LOGOUT, (char*)"");
}

void User::logout_response(char* payload) {
    Auth response = auth_data(payload);

    if (!strcmp(response.result_code, LOGOUT_SUCCESS)) {
        this->state = USER_NONAUTH;
        QMessageBox::information(nullptr,"Success","Logout successful",0);
    }
    else if (!strcmp(response.result_code, LOGOUT_E_NOTAUTH)) {
        QMessageBox::information(nullptr,"Error","Your client hasn't logged in",0);
    }
    else if (!strcmp(response.result_code, LOGOUT_E_INGAME)) {
        QMessageBox::information(nullptr,"Error","You can't loggout while in the game",0);
    }
    else {
        QMessageBox::information(nullptr,"Error","Unknown operation",0);
    }
}

#include "iostream"
#include "stream.h"
#include "util.h"
#include "QMessageBox"
#include "qdebug.h"

Socket::Socket(){
    this->client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    strcpy_s(this->ip_address, INET_ADDRSTRLEN, (char*)"127.0.0.1");
    this->port_number = 5500;
};

Socket::Socket(int port_number, char* ip_address) : port_number{ port_number }{
    strcpy_s(this->ip_address, INET_ADDRSTRLEN, ip_address);

    this->client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (this->client_socket == INVALID_SOCKET) {
        printf("Can't create socket for client with error: %d\n", WSAGetLastError());
    }
}

Socket::~Socket() {
    closesocket(this->client_socket);
    WSACleanup();
};

void Socket::set_timeout(int time) {
    setsockopt(this->client_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)(&time), sizeof(int));
}

int Socket::connect_to_server() {
    //Set info for server socket
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(this->port_number);
    inet_pton(AF_INET, this->ip_address, &serverAddr.sin_addr);

    //Set client connect state
    if (connect(this->client_socket, (sockaddr *)&serverAddr, sizeof(serverAddr))) {
        return 1;
    }
    return 0;
}

int Socket::tcp_send(char* code, char* payload) {
    char mess[BUFF_SIZE] = "";
    pack(code, payload, mess);
    qDebug() << "Send :" << mess;
    int ret = send(this->client_socket, mess, strlen(mess), 0);
    if (ret == SOCKET_ERROR) {
        QMessageBox::information(nullptr,"Error","Cannot send to server!",0);	// Dòng này thay bằng thông báo của UI
        return WSAGetLastError();
    }
    if (!ret) {
        return WSAECONNRESET;
    }
    return 0;
}

int Socket::tcp_receive(char* code, char* payload) {
    char mess[BUFF_SIZE] = "";
    int ret = recv(this->client_socket, mess, BUFF_SIZE, 0);
    if (ret == SOCKET_ERROR) {
        printf("Can't receive from the server with error: %d\n", WSAGetLastError());	// Dòng này thay bằng thông báo của UI
        return WSAGetLastError();
    }
    if (ret) {
        mess[ret] = '\0';
        char* ptr = mess;
        strncpy_s(code, CODE_SIZE + 1, mess, CODE_SIZE);
        ptr += CODE_SIZE;
        int first_byte = ptr[0];
        int second_byte = ptr[1];
        int len = first_byte * 256 + second_byte;
        strncpy_s(payload, PAYLOAD_SIZE + 1, ptr + PAYLOAD_LEN_SIZE, len);
    }
    else {
        return WSAECONNRESET;
    }
    return 0;
}

//The receive wrapper function
int Socket::Receive(char *buff){
    int ret, msgLen, received;
    ret = recv(this->client_socket, buff, 5, MSG_WAITALL);
    if (ret == SOCKET_ERROR) {
        qDebug() << "SOCKET_ERROR";
    }
    else {
        msgLen = (((buff[3] + 255) % 256) * 255) + (buff[4] + 255) % 256;
        received = 0;

        while (received < msgLen) {
            ret = recv(this->client_socket, buff + received, msgLen - received, 0);
            if (ret == SOCKET_ERROR) {
                printf("Error %d: Cannot receive message from server.\n", WSAGetLastError());
            }
                else {
                    received += ret;
                }
            }
        buff[received] = 0;
    }
    return ret;
}


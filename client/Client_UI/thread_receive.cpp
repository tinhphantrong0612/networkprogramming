#include "thread_receive.h"
#include "qdebug.h"

Thread_Receive::Thread_Receive(QObject *parent) : QThread(parent){

}

Thread_Receive::Thread_Receive(QObject *parent,Socket *thisSocket) : QThread(parent){
    bindSocket(&this->threadSocket,thisSocket);
}

void Thread_Receive::run(){
    // This Thread receive from server continously
    SOCKET socket = this->threadSocket.client_socket;

    int ret, msgLen, received;
    char *buff = (char *)malloc(BUFF_SIZE);
    while (1){
        //char buff[BUFF_SIZE];
        //Receive
        ret = recv(socket, buff, 5, MSG_WAITALL);
        if (ret == SOCKET_ERROR) {
            emit send((char*)DISCONNECTED);
            break;
        }
        else {
            msgLen = (((buff[3] + 255) % 256) * 255) + (buff[4] + 255) % 256;
            received = 0;

            while (received < msgLen) {
                ret = recv(socket, buff + received, msgLen - received, 0);
                if (ret == SOCKET_ERROR) {
                    emit send((char*)DISCONNECTED);
                    break;
                }
                else {
                    received += ret;
                }
            }
            buff[received] = 0;

            // qDebug() <<"Send: " << buff ;

            emit send(buff);
            char resultCode[RESULT_CODE_SIZE+1];
            strncpy_s(resultCode, buff, RESULT_CODE_SIZE);
            if (!strcmp(resultCode,"40100")) Sleep(500); // Stop emitting while Game UI is loading
            Sleep(50); // Prevent emitted message duplicated
        }
    }
}

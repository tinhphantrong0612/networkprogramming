#ifndef THREAD_RECEIVE_H
#define THREAD_RECEIVE_H

#include <QObject>
#include <QThread>
#include "stream.h"
#include "auth.h"
#include "util.h"
#include "uitextconst.h"

class Thread_Receive : public QThread
{
    Q_OBJECT
public:
    explicit Thread_Receive(QObject *parent = nullptr);
    Thread_Receive(QObject *parent = nullptr,Socket *socket = new Socket());

    Socket threadSocket;
    void run();

signals:
    void send(char*);
};

#endif // THREAD_RECEIVE_H

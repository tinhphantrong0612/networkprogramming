#ifndef STAGELOGIN_H
#define STAGELOGIN_H

#include <QMainWindow>
#include "stream.h"

QT_BEGIN_NAMESPACE
namespace Ui { class StageLogin; }
QT_END_NAMESPACE

class StageLogin : public QMainWindow
{
    Q_OBJECT

public:
    StageLogin(QWidget *parent = nullptr);
    ~StageLogin();
    Socket clientSocket;
    bool loginStatus;
    void initializeStage(Socket*, int);

private slots:
    void on_btnLogin_clicked();

    void on_btnRetry_clicked();

    void on_btnRegister_clicked();

private:
    Ui::StageLogin *ui;
};
#endif // STAGELOGIN_H

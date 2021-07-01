#include "stagelogin.h"
#include "ui_stagelogin.h"
#include "stagewaitingroom.h"
#include "util.h"
#include "auth.h"
#include "QMessageBox"
#include "QInputDialog"

StageLogin::StageLogin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StageLogin)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    //INIT state of Stage "Login"
    this->setWindowTitle("Login");
}

StageLogin::~StageLogin()
{
    delete ui;
}

void StageLogin::initializeStage(Socket *socket, int index){
    //Connect to server
    if ( index == 0 ){
        //Binding Socket to Stage Login on the first time
        bindSocket(&clientSocket,socket);
        if (this->clientSocket.connect_to_server() == 0) {
            ui->labelStatus->setText("Connected to server!");
            ui->btnLogin->setDisabled(false);
                ui->btnRegister->setDisabled(false);
            ui->btnRetry->hide();
        } else {
            ui->labelStatus->setText("Can't connect to server!");
            ui->btnLogin->setDisabled(true);
            ui->btnRegister->setDisabled(true);
            ui->btnRetry->show();
        }
    } else {
        // create new socket if current socket connection destroyed
        ui->labelStatus->setText("Press Retry to connect to server!");
        ui->btnLogin->setDisabled(false);
        ui->btnRegister->setDisabled(true);
        ui->btnRetry->show();
    }
}

void StageLogin::on_btnRetry_clicked()
{
    // Reconnect
    qDebug() << "Retry" ;
    if (this->clientSocket.connect_to_server() == 0) {
        ui->labelStatus->setText("Connected to server!");
        ui->btnLogin->setDisabled(false);
        ui->btnRegister->setDisabled(false);
        ui->btnRetry->hide();
    } else {
        ui->labelStatus->setText("Can't connect to server!");
        ui->btnLogin->setDisabled(true);
        ui->btnRegister->setDisabled(true);
        ui->btnRetry->show();
    }
}

void StageLogin::on_btnLogin_clicked()
{
    // send a login request to server with value of "txtUsername" and "txtPassword"
    QByteArray byteOfUsername = ui->txtUsername->text().toLocal8Bit();
    QByteArray byteOfPassword = ui->txtPassword->text().toLocal8Bit();
    char *username = byteOfUsername.data();
    char *password = byteOfPassword.data();

    User clientUser = User();
    clientUser.login_request(this->clientSocket,username,password);

    //Wait for response authenticate result
    char buff[BUFF_SIZE];
    if ( this->clientSocket.Receive(buff) ){
        clientUser.login_response(buff);
    }

    // Case: Login success
    // Create a Waiting Room scene with clientSocket
    if ( clientUser.state == USER_AUTH ){
        StageWaitingRoom *waitingRoom = new StageWaitingRoom();
        waitingRoom->initializeStage(&this->clientSocket,&clientUser);
        waitingRoom->show();
        this->close();
    }
}

void StageLogin::on_btnRegister_clicked()
{
    // send register request
    QByteArray byteOfUsername = ui->txtUsername->text().toLocal8Bit();
    QByteArray byteOfPassword = ui->txtPassword->text().toLocal8Bit();
    char *username = byteOfUsername.data();
    char *password1 = byteOfPassword.data();

    User clientUser = User();

    if (!strcmp(username,"") || !strcmp(password1, "")){
        QMessageBox::information(nullptr,"Warning","To register,first enter your desired username and password fields above!",0);
    } else {
        bool isFilled = false;
        // valid case. Step1: Re-enter password
        QString password = QInputDialog::getText(this,0,"Re-enter password",QLineEdit::Password,"re-enter password",&isFilled,Qt::Popup);
        if (!isFilled){
            QMessageBox::information(nullptr,"Notice","Register cancelled",0);
        } else {
            // Ask for confirmation
            QMessageBox::StandardButton isRegisterConfirmed;
            isRegisterConfirmed = QMessageBox::question(this, "Confirmation", "Are you sure register?" ,QMessageBox::Yes|QMessageBox::No);
            if (isRegisterConfirmed == QMessageBox::Yes){
                // Send Register request and receive response
                char *password2 = password.toLocal8Bit().data();
                clientUser.signup_request(clientSocket,username,password1,password2);
                char buff[BUFF_SIZE];
                if ( this->clientSocket.Receive(buff) ){
                    clientUser.signup_response(buff);
                }
            } else {
                QMessageBox::information(nullptr,"Notice","Register cancelled",0);
            }
        }
    }
}


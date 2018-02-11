#include "loginform.h"
#include "ui_loginform.h"
#include <iostream>
#include <QDebug>

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
//    setStyleSheet("background-image: url(:/images/SpaceImage.png);");
    ui->graphicsView->setStyleSheet("background-image: url(:/images/backgroundImage.png);");
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_Register_Button_clicked()
{
    emit ShowRegisterForm();
//    regForm.show();
//    this->show();
}

void LoginForm::on_Login_Button_clicked()
{
    QString userName = ui->Username_Text->toPlainText();
    QString password = ui->Password_Text->toPlainText();

    emit SendUsernameSignal(userName, password);
    //regForm.db.ConnectTODb(userName, password);
    //this->close();
}

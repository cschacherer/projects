#include "registerform.h"
#include "ui_registerform.h"
#include <QString>
#include <QDebug>

RegisterForm::RegisterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterForm)
{
    ui->setupUi(this);
}

RegisterForm::~RegisterForm()
{
    delete ui;
}

void RegisterForm::on_Save_Button_clicked()
{
    QString firstName = ui->FirstName_Text->toPlainText();
    QString lastName = ui->LastName_Text->toPlainText();
    QString userName = ui->Username_Text->toPlainText();
    QString password = ui->Password_Text->toPlainText();

    emit SendRegisterSignal(userName, password, firstName, lastName);


//    db.RegisterUser(firstName, lastName,userName, password);
//    if(db.isSaved == true)
//    {
//        ui->FirstName_Text->setText("");
//        ui->LastName_Text->setText("");
//        ui->Username_Text->setText("");
//        ui->Password_Text->setText("");
//        this->hide();
//    }
}

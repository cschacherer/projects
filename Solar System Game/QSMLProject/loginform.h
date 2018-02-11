#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <iostream>

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = 0);
    ~LoginForm();

public slots:
    void on_Register_Button_clicked();
    void on_Login_Button_clicked();

signals:
    void SendUsernameSignal(QString name, QString pass);
    void ShowRegisterForm();

private:
    Ui::LoginForm *ui;
    //RegisterForm regForm;
};

#endif // LOGINFORM_H

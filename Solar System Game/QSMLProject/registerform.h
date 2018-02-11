#ifndef REGISTERFORM_H
#define REGISTERFORM_H

#include <QWidget>


namespace Ui {
class RegisterForm;
}

class RegisterForm : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterForm(QWidget *parent = 0);
    ~RegisterForm();

private slots:
    void on_Save_Button_clicked();

signals:
    void SendRegisterSignal(QString, QString, QString, QString);

private:
    Ui::RegisterForm *ui;
};

#endif // REGISTERFORM_H


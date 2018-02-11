#ifndef BACKPACK_H
#define BACKPACK_H

#include <QDialog>

namespace Ui {
class Backpack;
}

class Backpack : public QDialog
{
    Q_OBJECT

public:
    explicit Backpack(QWidget *parent = 0);
    ~Backpack();

private slots:
    void on_backButton_clicked();

    void on_souvenir1_clicked();

    void on_souvenir4_clicked();

    void on_souvenir2_clicked();

    void on_souvenir3_clicked();

    void on_souvenir5_clicked();

    void on_souvenir6_clicked();

    void on_souvenir7_clicked();

    void on_souvenir8_clicked();

    void on_souvenir9_clicked();

private:
    Ui::Backpack *ui;
    int itemSelected ;
    QString currentPlanet;
    void showItemInformation();
};

#endif // BACKPACK_H

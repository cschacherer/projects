#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QGraphicsRectItem>
#include <planets.h>
#include <QMouseEvent>
#include <QGraphicsPixmapItem>
#include <QPushButton>
#include <iostream>
#include <Box2D/Box2D.h>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QRadioButton>
#include <QLabel>
#include <QTimer>
#include <QTime>
#include <quizzes.h>
#include <QDialog>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include "QMessageBox"
#include <QString>
#include "earth.h"
#include "uranus.h"
#include "journal.h"
#include "backpack.h"
#include "saturn.h"
#include "mars.h"
#include "souvenir.h"
#include "mercury.h"
#include "venus.h"
#include "moon.h"
#include "neptune.h"
#include "jupiter.h"
#include "loginform.h"
#include "registerform.h"
#include "client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void reset();
    void addCharacter();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent * event);
    QGraphicsRectItem* character;
    QGraphicsPixmapItem characterImage;
    QDialogButtonBox* buttonBox;
    QDialog *question;
    QDialog score;
    void earthLevel();
    void SetButtons();
    void venusLevel();
    void mercuryLevel();
    void moonLevel();
    void SaturnLevel();
    void UranusLevel();
    void MarsLevel();
    void JupiterLevel();
    void NeptuneLevel();
    void displayMessage();
    void removeMessage();
    void pickUpItem();

    Earth earth;
    Earth *earthPointer = &earth;
    Venus venus;
    Moon moon;
    Mercury mercury;
    Mars mars;
    Saturn saturn;
    Uranus uranus;
    Mercury *mercuryPointer = &mercury;
    Neptune neptune;
    Jupiter jupiter;
    void goToPlanetAnimation(int animationCount);
    int animationCount;

public slots:
    void showButton();
    void checkClick();
    void displayPlanet();
    void SouvenirHoverSlot(std::string name, std::string description);
    void LoginUsername(QString name, QString pass);
    void ShowRegister();
    void RegisterPlayer(QString name, QString pass, QString first, QString last);

private slots:
    void closeQuiz();
    void gradeQuiz(QVector<QRadioButton*> options, QVector<int> Solution);

    void item1ButtonSlot();
    void item2ButtonSlot();
    void item3ButtonSlot();
    void item4ButtonSlot();
    void item5ButtonSlot();
    void item6ButtonSlot();
    void item7ButtonSlot();
    void item8ButtonSlot();
    void item9ButtonSlot();
    void openJournal();
    void openBackpack(); // backpack

    void on_journalButton_clicked();
    void on_backpackButton_clicked();
    void on_jump_clicked();

    void on_radioNasa_clicked();

private:
    Ui::MainWindow *ui;
    Planets *planets;
    QGraphicsScene *backgroundScene;
    QImage background;
    QPixmap backgroundPix;
    void nextLevel(int currenLevel);
    int loadQuiz(int level);
    void playAudio();
    QString imagePath;
    int level;
    Journal *winJournal;
    Backpack *winBackpack;
    LoginForm login;
    Client client;
    RegisterForm regForm;
    std::string onPlanet;

signals:
    void gradeQuizSignal(QVector<QRadioButton*>, QVector<int>);

};

#endif // MAINWINDOW_H

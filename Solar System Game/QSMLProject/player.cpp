#include "player.h"

Player::Player()
{
    username = "";
    password = "";
    isAdmin = false;

    //setting quiz scores to nothing
    quizScores[1] = 0;
    quizScores[2] = 0;
    quizScores[3] = 0;
    quizScores[4] = 0;
    quizScores[5] = 0;
    quizScores[6] = 0;
    quizScores[7] = 0;
    quizScores[8] = 0;
    quizScores[9] = 0;
    quizScores[10] = 0;
}

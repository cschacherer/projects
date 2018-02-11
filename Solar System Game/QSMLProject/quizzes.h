#ifndef QUIZZES_H
#define QUIZZES_H
#include <QVector>
#include <QString>

class Quizzes
{
public:
    Quizzes();
    QVector<QVector<QString> > getQuiz(int level);
    QVector<int> getSolution(int level);
    QVector< QVector<QVector<QString> > > quizzesInOrder;
    QVector<QVector<int> > solutionsInOrder;

    QVector<QVector<QString> > moonQuiz;
    QVector<QVector<QString> > mercuryQuiz;
    QVector<QVector<QString> > marsQuiz;
    QVector<QVector<QString> > venusQuiz;
    QVector<QVector<QString> > saturnQuiz;
    QVector<QVector<QString> > jupiterQuiz;
    QVector<QVector<QString> > uranusQuiz;
    QVector<QVector<QString> > neptuneQuiz;
    QVector<QVector<QString> > plutoQuiz;

    QVector<int> moonSolutions;
    QVector<int> mercurySolutions;
    QVector<int> marsSolutions;
    QVector<int> venusSolutions;
    QVector<int> saturnSolutions;
    QVector<int> jupiterSolutions;
    QVector<int> uranusSolutions;
    QVector<int> neptuneSolutions;
    QVector<int> plutoSolutions;
};

#endif // QUIZZES_H

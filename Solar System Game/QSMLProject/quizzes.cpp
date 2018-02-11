#include "quizzes.h"
#include <QVector>
Quizzes::Quizzes()
{
    moonQuiz.push_back(QVector<QString>() << "How many times does the moon orbit the sun in earth days?" <<
    "27.9" <<"45.9" << "27.3" << "45.3");


    moonQuiz.push_back(QVector<QString>() << "Who was the first person to set foot on the moon?" <<
    "Neil Armstrong" <<"Michael Collins" << "Yuri Gagarin" << "Buzz Aldrin");

    moonQuiz.push_back(QVector<QString>() << "How far is the moon from the Earth?" <<
    "100001 miles" << "230100 miles" << "5000 miles" << "47382 miles");

    moonQuiz.push_back(QVector<QString>() <<"The moon is Earth’s only natural _____." <<
    "light" << "satellite" << "energy" << "cooling source");

    moonQuiz.push_back(QVector<QString>() << "The _____ side of the moon is the side of the moon we can see from earth." <<
    "close" << "far" << "near" << "distant");

    moonSolutions << 0 << 0 << 1 << 0 <<
                     1 << 0 << 0 << 0 <<
                     0 << 1 << 0 << 0 <<
                     0 << 1 << 0 << 0 <<
                     0 << 0 << 1 << 0;

    mercuryQuiz.push_back(QVector<QString>() << "Mercury is the closest planet to the sun." <<
    "True" <<	"False");

    mercuryQuiz.push_back(QVector<QString>() << "Mercury has a very thick atmosphere." <<
    "True" <<	"False");

    mercuryQuiz.push_back(QVector<QString>() << "What is the orbital period of Mercury in earth days?" <<
    "56" << "71" << "88" << "94");

    mercuryQuiz.push_back(QVector<QString>() << "Mercury is a planet that ______." <<
    "can retain water" << "can retain heat" << "can NOT retain water" << "can NOT retain heat");

    mercuryQuiz.push_back(QVector<QString>() << "Mercury’s radius consists of mostly what?" <<
    "Rock" << "Metal" << "Ice" << "Ammonia");


    mercurySolutions << 1 << 0 <<
                        0 << 1 <<
                        0 << 0 << 1 << 0 <<
                        0 << 0 << 0 << 1 <<
                        0 << 1 << 0 << 0;

    venusQuiz.push_back(QVector<QString>() << "Venus rotates in opposite direction of other planets in the solar system." <<
                        "True" << "False");

    venusQuiz.push_back(QVector<QString>() << "The four terrestrial planets are composed of mainly silicate rocks and metals." <<
                        "True" << "False");

    venusQuiz.push_back(QVector<QString>() << "Venus is the ______ from the sun with an orbital period of _____ earth days." <<
                        "second planet, 224.7" << "second planet, 107.3" << "third planet, 224.7" << "third planet, 107.3");

    venusQuiz.push_back(QVector<QString>() << "Why is Venus considered a “sister” planet to Earth?" <<
                        "Because they are about the same size" << "Because they are about the same mass" << "Because they are about the same distance from the sun" <<
                        "All of the above");

    venusQuiz.push_back(QVector<QString>() << "Out of the 4 terrestrial planets Venus has the _____ which consists of _____ carbon dioxide." <<
                        "greatest mass, 96%" << "greatest mass, 84%" << "densest atmosphere, 96%" << "densest atmosphere, 84%");

    venusSolutions << 1 << 0 <<
                      1 << 0 <<
                      1 << 0 << 0 << 0 <<
                      0 << 0 << 0 << 1 <<
                      0 << 0 << 1 << 0;

    marsQuiz.push_back(QVector<QString>() << "What color is the atmosphere of Mars and why?" <<
    "It is blue because it is frozen over from the low temperatures." << "It is blue because it consists of mainly carbon dioxide." <<
    "It is red because of the high temperatures and proximity to the sun." <<
    "It is red because of all of the Iron in the soil.");

    marsQuiz.push_back(QVector<QString>() << "Mars is __ the size of our home planet Earth." <<
    "1/3" <<
    "1/4" <<
    "1/5" <<
    "1/6");

    marsQuiz.push_back(QVector<QString>() << "What is the average temperature of Mars?" <<
    "-100 to 0 fahrenheit" <<
    "-207 to 80 fahrenheit" <<
    "-267 to -100 fahrenheit" <<
    "-301 to  -15 fahrenheit");

    marsQuiz.push_back(QVector<QString>() << "If you drop a rock on mars it will fall _____ times slower than if you dropped it on Earth" <<
    "2" <<
    "3" <<
    "4" <<
    "5");

    marsQuiz.push_back(QVector<QString>() << "Mars is the fourth planet from the Sun and the second-smallest planet in the Solar System" <<
    "third, third-smallest" <<
    "third, second-smallest" <<
    "fourth, second-smallest" <<
    "fifth , second-smallest");

    marsSolutions << 0 << 0 << 0 << 1 <<
                     0 << 0 << 0 << 1 <<
                     0 << 1 << 0 << 0 <<
                     0 << 1 << 0 << 0 <<
                     0 << 0 << 1 << 0;

    jupiterQuiz.push_back(QVector<QString>() << "Jupiter is the biggest planet in our solar system." <<
   "True, it is almost twice as big than any of the other planets" <<
    "True, it is almost three times bigger than any of the other planets" <<
    "False, it is almost twice as small than any of the other planets" <<
    "False, it is almost three times smaller than any of the other planets");

    jupiterQuiz.push_back(QVector<QString>() << "What are the names of Jupiter’s four large moons?" <<
    "Io, Helus, Callisto, Omus" <<
    "Europa, Callisto, Omus, Pasis" <<
    "Io, Europa, Ganymede, Callisto" <<
    "Europa, Helus, Pasis, Callisto");

    jupiterQuiz.push_back(QVector<QString>() << "Jupiter’s atmosphere like Saturn, Uranus, and Neptune consist of mostly _____ and _____. " <<
    "Helium, Hydrogen" <<
    "Helium, Nitrogen" <<
    "Magnesium, Hydrogen" <<
    "Magnesium, Nitrogen");

    jupiterQuiz.push_back(QVector<QString>() <<"Jupiter consists of_____, which is provided by the ammonia in its atmosphere." <<
    "blue rocks" <<
    "colorful rocks" <<
    "blue air" <<
    "colorful clouds");

    jupiterQuiz.push_back(QVector<QString>() <<"Jupiter spins once every _____ earth days." <<
    "9" <<
    "10" <<
    "11" <<
    "12");

    jupiterSolutions << 1 << 0 << 0 << 0 <<
                     0 << 0 << 1 << 0 <<
                     1 << 0 << 0 << 0 <<
                     0 << 0 << 0 << 1 <<
                     0 << 1 << 0 << 0;

    saturnQuiz.push_back(QVector<QString>() << "Saturn is surrounded by a thin flat ring." <<
        "True" <<			"False");
     saturnQuiz.push_back(QVector<QString>() << "Saturn ring consists of _____ main rings." <<
    "7" <<
    "8" <<
    "9" <<
    "10");
     saturnQuiz.push_back(QVector<QString>() << "Saturn’s rings are mostly composed of _____ and a small amount of _____." <<
    "Ice particles, rocky debris" <<
    "Ice particles, ammonia" <<
    "Hydrogen, rocky debris" <<
    "Hydrogen, ammonia");
     saturnQuiz.push_back(QVector<QString>() << "How many moons orbit Saturn?" <<
    "Less than 53" <<
    "More than 53" <<
    "Exactly 53");
     saturnQuiz.push_back(QVector<QString>() << "Saturn’s core consist of what?" <<
    "Iron" <<
    "Nickel" <<
    "Rock"<<
    "Silver" <<
    "All of the above" <<
    "a, b, c" <<
    "b, c, d");

     saturnSolutions << 1 << 0 <<
                        0 << 0 << 1 << 0 <<
                        1 << 0 << 0 << 0 <<
                        0 << 1 << 0 << 0 <<
                        0 << 0 << 0 << 0 << 1 << 0;

     uranusQuiz.push_back(QVector<QString>() << "Why is Uranus considered similar to neptune?" <<
     "Because they are similar in size" <<
     "Because they are similar in mass" <<
     "Because they are both considered “bulk chemical” composition" <<
     "All of the above");
     uranusQuiz.push_back(QVector<QString>() << "Uranus is the _____ planet from the sun" <<
     "1st" <<
     "3rd" <<
     "5th" <<
     "7th");
     uranusQuiz.push_back(QVector<QString>() << "Besides from consisting of mostly helium and hydrogen it also consists of:" <<
     "ammonia" <<
     "methane" <<
     "water" <<
     "All of the above");
     uranusQuiz.push_back(QVector<QString>() << "It is the warmest planetary atmosphere in the solar system." <<
      "True"		<<	"False");
     uranusQuiz.push_back(QVector<QString>() << "Uranus has a minimum temperature of -224.2 celsius." <<
      "True"	<<	"False");

     uranusSolutions << 0 << 0 << 1 << 0 <<
                        0 << 0 << 0 << 1 <<
                        0 << 0 << 0 << 1 <<
                        0 << 1 <<
                        1 << 0;

     neptuneQuiz.push_back(QVector<QString>() << "Neptune is the farthest planet from the sun." <<
         "True"		<<	"False");
     neptuneQuiz.push_back(QVector<QString>() << "Neptune is the densest planet in the solar system." <<
         "True" 	<<		"False");
     neptuneQuiz.push_back(QVector<QString>() << "Neptune is the only planet that was discovered through _____." <<
     "Mathematical predictions" <<
     "Empirical Observation" <<
     "Weather occurrences");
     neptuneQuiz.push_back(QVector<QString>() << "Neptune has the strongest sustained winds in the solar system. Because of this, there is active and "
                                                 "visible weather patterns on its atmosphere" <<
     "True" << "False");
     neptuneQuiz.push_back(QVector<QString>() << "There is active  _____ on Neptune’s atmosphere." <<
     "and visible weather patterns" <<
     "growing mass" <<
     "and visible fog" <<
     "earthquakes");

     neptuneSolutions << 1 << 0 <<
                        1 << 0 <<
                        1 << 0 << 0 << 0 <<
                        1 << 0 <<
                        1 << 0;

     plutoQuiz.push_back(QVector<QString>() << "Pluto is not considered a planet but a _____ instead." <<
     "Mediator" <<
     "Dwarf planet" <<
     "Star");
     plutoQuiz.push_back(QVector<QString>() << "When was pluto first Discovered?" <<
     "1910" <<
     "1920" <<
     "1930" <<
     "1940");
     plutoQuiz.push_back(QVector<QString>() << "When was Pluto classified as not being a planet?" <<
     "2005" <<
     "2006" <<
     "2007" <<
     "2008");

     plutoSolutions << 0 << 1 << 0 << 0 <<
                       0 << 0 << 1 << 0 <<
                       1 << 0 << 0 << 0;

     quizzesInOrder << moonQuiz << mercuryQuiz << venusQuiz << marsQuiz << jupiterQuiz << saturnQuiz << uranusQuiz << neptuneQuiz << plutoQuiz;
     solutionsInOrder << moonSolutions << mercurySolutions << venusSolutions << marsSolutions << jupiterSolutions << saturnSolutions << uranusSolutions
                      << neptuneSolutions << plutoSolutions;
}

QVector<QVector<QString> > Quizzes::getQuiz(int level)
{
    if (level >= 1)
        return quizzesInOrder[level];
    else
        return moonQuiz;
}

QVector<int> Quizzes::getSolution(int level)
{
    if (level >= 1)
        return solutionsInOrder[level];
    else
        return moonSolutions;

}

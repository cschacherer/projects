#include "journal.h"
#include "ui_journal.h"
#include <iostream>
Journal::Journal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Journal)
{
    page_number = 0;
    ui->setupUi(this);
    ui->notebook->setReadOnly(true);
    ui->notebook->setEnabled(true);


    ui->leftArrowButton->setIcon(QIcon(":/journalItems/orngLeftArrow.png"));
    connect(ui->leftArrowButton, &QPushButton::clicked, this, &Journal::prevPageClicked);
    ui->leftArrowButton->setIconSize(QSize(20,20));

    ui->rightArrowButton->setIcon(QIcon(":/journalItems/orngRightArrow.png"));
    connect(ui->rightArrowButton, &QPushButton::clicked, this, &Journal::nextPageClicked);
    ui->rightArrowButton->setIconSize(QSize(20,20));

    //ui->notebook->setStyleSheet("background-image: url(:/journalItems/pluto_Journal.jpeg);");
    ui->notebook->setStyleSheet("background-image: url(:/journalItems/maleNotebookImage.png);");

}

Journal::~Journal()
{
    delete ui;
}

void Journal::prevPageClicked()
{
    if(page_number != 0){
        page_number --;
        changeTextInNoteBook();
    }
}

void Journal::nextPageClicked()
{
    if(page_number != 12)
    {
      page_number++;
      changeTextInNoteBook();
      std::cout << page_number << "" << std::endl;
    }
}

void Journal:: changeTextInNoteBook(){
    ui->notebook->clear();
       if(page_number == 0) // Intro Picture
        {
           ui->notebook->setStyleSheet("background-image: url(:/journalItems/maleNotebookImage.png);");
        }
        else if (page_number == 1) // Sun
        {
           ui->notebook->setStyleSheet("background-image: url(:/journalItems/sun_Journal.jpg);");
           ui->notebook->insertHtml("<body>");
           ui->notebook->insertHtml("<center><font color='BLACK'><h1 style = 'font-family:Comic Sans MS;'>Sun</h1></font></center>");
           ui->notebook->insertHtml("<br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>~The sun is a yellow dwarf and is 4.6 billion years old. </P></font>");
           ui->notebook->insertHtml("<font color='BLACK'><P style = 'font-family:Comic Sans MS;'><br>~One million Earths could fit inside the sun</P></font>");
           ui->notebook->insertHtml("<font color='BLACK'><P style = 'font-family:Comic Sans MS;'><br>~The temperature inside the sun can reach 15 million degrees Celsius </P></font>");
           ui->notebook->insertHtml("<font color='BLACK'><P style = 'font-family:Comic Sans MS;'><br>~The sun is in the middle of its life cycle</P></font>");
           ui->notebook->insertHtml("<font color='BLACK'><P style = 'font-family:Comic Sans MS;'><br>~Te primary elements that the sun is made up of 72% hydrogen, 26 % helium and has traces of oxygen, carbon, neon, nitrogen, magnesium, iron and silicon</P></font>");
           ui->notebook->insertHtml("</body></html>");
        }
        else if (page_number == 2) // Moon
        {
            ui->notebook->setStyleSheet("background-image: url(:/journalItems/moon_Journal.jpg);");
            ui->notebook->insertHtml("<body>");
            ui->notebook->insertHtml("<center><font color='BLACK'><h1 style = 'font-family:Comic Sans MS;'>Moon</h1></font></center>");
            ui->notebook->insertHtml("<br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>~The moon is the Earth’s only natural satellite, it is also the brightest natural object in the night sky. </P></font>");
            ui->notebook->insertHtml("<font color='BLACK'><P style = 'font-family:Comic Sans MS;'><br>~230100 miles is the average distance from the moon to the earth.  </P></font>");
            ui->notebook->insertHtml("<font color='BLACK'><P style = 'font-family:Comic Sans MS;'><br>~The moon also orbits the sun every 27.3 earth days. </P></font>");
            ui->notebook->insertHtml("<font color='BLACK'><P style = 'font-family:Comic Sans MS;'><br>~We call on face of the moon the “near side” which is the side that we can see on earth. The other face of the earth is called the “far side”.</P></font>");
            ui->notebook->insertHtml("<font color='BLACK'><P style = 'font-family:Comic Sans MS;'><br>~USA NASA Apollo mission was the first time mankind landed on the moon.</P></font>");
            ui->notebook->insertHtml("<font color='BLACK'><P style = 'font-family:Comic Sans MS;'><br>~Neil Armstrong was the first man to set foot on moon.</P></font>");
            ui->notebook->insertHtml("<font color='BLACK'></P></font>");
            ui->notebook->insertHtml("</body></html>");
        }
        else if (page_number == 3) // Mercury
        {
           ui->notebook->setStyleSheet("background-image: url(:/journalItems/mercury_Journal.jpg);");
           ui->notebook->insertHtml("<body>");
           ui->notebook->insertHtml("<center><font color='BLACK'><h1 style = 'font-family:Comic Sans MS;'>Mercury</h1></font></center>");
           ui->notebook->insertHtml("<br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>~Mercury is the closest planet to the sun, it is also the smallest planet in the solar system. </P></font>");
           ui->notebook->insertHtml("<font color='BLACK'><P style = 'font-family:Comic Sans MS;'><br>~It has an orbital period of 88 earth days, so it is also the fastest planet out of all the other planets in our solar system.</P></font>");
           ui->notebook->insertHtml("<font color='BLACK'><P style = 'font-family:Comic Sans MS;'><br>~Mercury has a metal core which consists of most of the planet’s radius so just like the moon, it has a thin atmosphere.  </P></font>");
           ui->notebook->insertHtml("<font color='BLACK'><P style = 'font-family:Comic Sans MS;'><br>~Mercury is a planet that can not retain heat</P></font>");
           ui->notebook->insertHtml("</body></html>");
        }
        else if (page_number == 4) // Venus
        {
           ui->notebook->setStyleSheet("background-image: url(:/journalItems/Venus_Journal.jpg);");
           ui->notebook->insertHtml("<body>");
           ui->notebook->insertHtml("<center><font color='BLACK'><h1 style = 'font-family:Comic Sans MS;'>Venus</h1></font></center>");
           ui->notebook->insertHtml("<br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>~Venus is the second planet from the sun with an orbital period of 224.7 earth days. </P></font>");
           ui->notebook->insertHtml("<font color='BLACK'><P style = 'font-family:Comic Sans MS;'><br>~Venus rotates in opposite direction to the other planets in the solar system.</P></font>");
           ui->notebook->insertHtml("<font color='BLACK'><P style = 'font-family:Comic Sans MS;'><br>~Venus has no natural satellite but it is the second brightest natural object in the night sky. </P></font>");
           ui->notebook->insertHtml("<font color='BLACK'><P style = 'font-family:Comic Sans MS;'><br>~Earth is considered the “sister” planet of Venus because of the similarity in size, mass and distance to the sun. </P></font>");
           ui->notebook->insertHtml("<font color='BLACK'><P style = 'font-family:Comic Sans MS;'><br>~Out of the 4 terrestrial planets Venus has the densest atmosphere which consists of 96% carbon dioxide. </P></font>");
           ui->notebook->insertHtml("<P style = 'font-family:Comic Sans MS;'><font color='BLACK'><br>~The four terrestrial planets are composed of mainly silicate rocks and metals. These four planets are Mercury, Venus, Mars and Earth. </P></font>");
           ui->notebook->insertHtml("</body></html>");
        }
        else if (page_number == 5) // Earth
        {
           ui->notebook->setStyleSheet("background-image: url(:/journalItems/earth_Journal.jpg);");
           ui->notebook->insertHtml("<body>");
           ui->notebook->insertHtml("<center><font color='BLACK'><h1 style = 'font-family:Comic Sans MS;'>Earth</h1></font></center>");
           ui->notebook->insertHtml("<br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>~The Earth rotation is slowing down at a rate of 17 milliseconds per 100 years </P></font>");
           ui->notebook->insertHtml("<font color='BLACK'><P style = 'font-family:Comic Sans MS;'><br>~People used to believe that the Earth was the center of the universe </P></font>");
           ui->notebook->insertHtml("<P style = 'font-family:Comic Sans MS;'><font color='BLACK'><br>~Earth is the only planet not named after a god. </P></font>");
           ui->notebook->insertHtml("<font color='BLACK'><P style = 'font-family:Comic Sans MS;'><br>~Earth is the densest planet in the Solar System </P></font>");
           ui->notebook->insertHtml("</body></html>");
        }
        else if (page_number == 6) // Mars
        {
           ui->notebook->setStyleSheet("background-image: url(:/journalItems/Mars_Journal.jpg);");
           ui->notebook->insertHtml("<body>");
           ui->notebook->insertHtml("<center><font color='BLACK'><h1  style = 'font-family:Comic Sans MS;'>Mars</h1></font></center>");
           ui->notebook->insertHtml("<br><font color='BLACK'><P  style = 'font-family:Comic Sans MS;'>~Mars is the fourth planet from the sun . </P></font>");
           ui->notebook->insertHtml("<font color='BLACK'><P  style = 'font-family:Comic Sans MS;'><br>~Mars is red from the iron in the soil. </P></font>");
           ui->notebook->insertHtml("<P style = 'font-family:Comic Sans MS;'><font color='BLACK'><br>~Mars is ⅙ the size of our home planet Earth. </P></font>");
           ui->notebook->insertHtml("<font color='BLACK'><P  style = 'font-family:Comic Sans MS;'><br>~Mars is a very cold planet it averages -207 to 80 fahrenheit. </P></font>");
           ui->notebook->insertHtml("<font color='BLACK'><P  style = 'font-family:Comic Sans MS;'><br>~If you drop a rock on mars it will fall 3 times slower than if you dropped it on Earth. This is because mars gravity is ⅓ of Earth’s. </P></font>");
           ui->notebook->insertHtml("<P style = 'font-family:Comic Sans MS;'><font color='BLACK'><br>~Mars is the fourth planet from the Sun and the second-smallest planet in the Solar System </P></font>");
           ui->notebook->insertHtml("</body></html>");
        }
        else if (page_number == 7) // Jupiter
        {
           ui->notebook->setStyleSheet("background-image: url(:/journalItems/Jupiter_Journal.jpg);");
           ui->notebook->insertHtml("<body>");
           ui->notebook->insertHtml("<center><font color='BLACK'><h1  style = 'font-family:Comic Sans MS;'>Jupiter</h1></font></center>");
           ui->notebook->insertHtml("<br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>~Jupiter is the biggest planet in our solar system, it is almost twice as big than any of the other planets. </P></font>");
           ui->notebook->insertHtml("<font color='BLACK'><P style = 'font-family:Comic Sans MS;'><br>~Jupiter has consists of colorful clouds, which is provided by the ammonia in its atmosphere. </P></font>");
           ui->notebook->insertHtml("<P style = 'font-family:Comic Sans MS;'><font color='BLACK'><br>~Has the fastest rotating body in our solar system, spinning about once every 10 earth hours. </P></font>");
           ui->notebook->insertHtml("<font color='BLACK'><P style = 'font-family:Comic Sans MS;'><br>~Jupiter’s atmosphere like Saturn, Uranus, and Neptune consist of mostly hydrogen and helium. </P></font>");
           ui->notebook->insertHtml("<font color='BLACK'><P style = 'font-family:Comic Sans MS;'><br>~Jupiter has many moons , 4 of which are the largest and have been named. The four large moons in Jupiter are  Io, Europa, Ganymede and Callisto.  </P></font>");
           ui->notebook->insertHtml("<P style = 'font-family:Comic Sans MS;'><font color='BLACK'><br>~Jupiter is formed of gasses so there is no solid ground on Jupiter. </P></font>");
           ui->notebook->insertHtml("<P style = 'font-family:Comic Sans MS;'><font color='BLACK'><br>~Gravity pull is 2 and a half times stronger than it is on Earth </P></font>");
           ui->notebook->insertHtml("</body></html>");
        }
       else if (page_number == 8) // Saturn
       {
          ui->notebook->setStyleSheet("background-image: url(:/journalItems/Saturn_Journal.png);");
          ui->notebook->insertHtml("<body>");
          ui->notebook->insertHtml("<center><font color='BLACK'><h1 style = 'font-family:Comic Sans MS;'>Saturn</h1></font></center>");
          ui->notebook->insertHtml("<br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>~Saturn is surrounded by a thin flat ring that consists on 9 main rings. They are mostly composed of ice particles and a small amount of rocky debris. </P></font>");
          ui->notebook->insertHtml("<font color='BLACK'><P style = 'font-family:Comic Sans MS;'><br>~Many moons orbit saturn, only 53 of them have been names and that is not including the hundreds of moonlets that comprise the rings. </P></font>");
          ui->notebook->insertHtml("<P style = 'font-family:Comic Sans MS;'><font color='BLACK'><br>~Saturn’s core consists of Iron, Nickel, and Rock, it is surrounded by a thin layer of metallic hydrogen. </P></font>");
          ui->notebook->insertHtml("</body></html>");
      }
        else if (page_number == 9) // Uranus
        {
           ui->notebook->setStyleSheet("background-image: url(:/journalItems/uranus_Journal.jpg);");
           ui->notebook->insertHtml("<body>");
           ui->notebook->insertHtml("<center><font color='BLACK'><h1  style = 'font-family:Comic Sans MS;'>Uranus</h1></font></center>");
           ui->notebook->insertHtml("<br><font color='BLACK'><P  style = 'font-family:Comic Sans MS;'>~Uranus is the 7th planet from the sun.  </P></font>");
           ui->notebook->insertHtml("<font color='BLACK'><P  style = 'font-family:Comic Sans MS;'><br>~Uranus is considered similar to Neptune because both planets “bulk chemical” composition. </P></font>");
           ui->notebook->insertHtml("<P style = 'font-family:Comic Sans MS;'><font color='BLACK'><br>~Besided from consisting of mostly helium and hydrogen it also consists of “ices” like ammonia, methane and water. </P></font>");
           ui->notebook->insertHtml("<font color='BLACK'><P style = 'font-family:Comic Sans MS;'><br>~It is the coldest planetary atmosphere in the solar system with a minimum temperature of -224.2 celsius. </P></font>");
           ui->notebook->insertHtml("</body></html>");
        }
        else if (page_number == 10) // Neptune
        {
           ui->notebook->setStyleSheet("background-image: url(:/journalItems/Neptune_Journal.jpg);");
           ui->notebook->insertHtml("<body>");
           ui->notebook->insertHtml("<center><font color='BLACK'><h1 style = 'font-family:Comic Sans MS;'>Neptune</h1></font></center>");
           ui->notebook->insertHtml("<br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>~Neptune is the farthest planet from the sun and the densest planet in the solar system. </P></font>");
           ui->notebook->insertHtml("<font color='BLACK'><P style = 'font-family:Comic Sans MS;'><br>~Neptune is the only planet that was discovered through mathematical predictions rather than by empirical observation.  </P></font>");
           ui->notebook->insertHtml("<P style = 'font-family:Comic Sans MS;'><font color='BLACK'><br>~Neptune has the strongest sustained winds in the solar system, because of this there is active and visible weather patterns on its atmosphere.  </P></font>");
           ui->notebook->insertHtml("</body></html>");
        }
        else if (page_number == 11) // Pluto
        {
           ui->notebook->setStyleSheet("background-image: url(:/journalItems/pluto_Journal.jpeg);");
           ui->notebook->insertHtml("<body>");
           ui->notebook->insertHtml("<center><font color='BLACK'><h1 style = 'font-family:Comic Sans MS;'>Pluto</h1></font></center>");
           ui->notebook->insertHtml("<br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>~Pluto is not considered  planet on our solar system it is classified as a “dwarf” planet. </P></font>");
           ui->notebook->insertHtml("<font color='BLACK'><P style = 'font-family:Comic Sans MS;'><br>~In 1930 Pluto was the first belt object to be discovered, it was classified as a planet then but in 2005 pluto was moved to the category of Dwarf planet. </P></font>");
           ui->notebook->insertHtml("</body></html>");
        }
       else if (page_number == 12) // credits
       {
           ui->notebook->setStyleSheet("background-image: url(:/journalItems/the-milky-way_Journal.jpg);");
           ui->notebook->insertHtml("<body>");
           ui->notebook->insertHtml("<center><font color='BLACK'><h1 style = 'font-family:Comic Sans MS;'>Credit</h1></font></center>");
           ui->notebook->insertHtml("<center><br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>Anna Buchman </P></font></center>");
           ui->notebook->insertHtml("<center><font color='BLACK'><P style = 'font-family:Comic Sans MS;'><br>Connor Schacherer </P></font></center>");
           ui->notebook->insertHtml("<center><P style = 'font-family:Comic Sans MS;'><font color='BLACK'><br>Faith Oladele </P></font></center>");
           ui->notebook->insertHtml("<center><font color='BLACK'><P style = 'font-family:Comic Sans MS;'><br>Jeanette Arteaga </P></font></center>");
           ui->notebook->insertHtml("<center><font color='BLACK'><P style = 'font-family:Comic Sans MS;'><br>Stacey Kirby</P></font></center>");
           ui->notebook->insertHtml("<center><P style = 'font-family:Comic Sans MS;'><font color='BLACK'><br>Tivinia Pohahau </P></font></center>");
           ui->notebook->insertHtml("</body></html>");
       }
}

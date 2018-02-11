#include "backpack.h"
#include "ui_backpack.h"

Backpack::Backpack(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Backpack)
{
    itemSelected = 0;
    currentPlanet = "none";
    ui->setupUi(this);
    on_backButton_clicked();
    ui->background->setReadOnly(true);
    ui->background->setEnabled(true);

    ui->planetName->setEnabled(false);
    ui->planetName->setStyleSheet("QPushButton{background: transparent;}");
}

Backpack::~Backpack()
{
    delete ui;
}

void Backpack::on_backButton_clicked()
{
    ui->planetName->clear();
    ui->planetName->setFrameStyle(QFrame::NoFrame);
    ui->souvenirInformation->setFrameStyle(QFrame::NoFrame);
    ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                     " Welcome to the solar system!"
                                       "</h1></P></font><center>");
    if(itemSelected == 0){
     ui->planetName->viewport()->setAutoFillBackground(false);
     ui->souvenir1->setVisible(true);
     ui->souvenir2->setVisible(true);
     ui->souvenir3->setVisible(true);
     ui->souvenir4->setVisible(true);
     ui->souvenir5->setVisible(true);
     ui->souvenir6->setVisible(true);
     ui->souvenir7->setVisible(true);
     ui->souvenir8->setVisible(true);
     ui->souvenir9->setVisible(true);

    ui->background->setStyleSheet("background-image: url(:/journalItems/the-milky-way_Journal.jpg);");
    ui->souvenir1->setEnabled(true); //Earth
    ui->souvenir1->setIcon(QIcon(":/backpackItems/earthBackpack.ico"));
    ui->souvenir1->setIconSize(QSize(50,50));
    ui->souvenir1->setStyleSheet("QPushButton{background: transparent;}");
    ui->souvenir2->setEnabled(true); //Moon
    ui->souvenir2->setIcon(QIcon(":/backpackItems/moonBackpack.png"));
    ui->souvenir2->setIconSize(QSize(50,50));
    ui->souvenir2->setStyleSheet("QPushButton{background: transparent;}");
    ui->souvenir3->setEnabled(true); //Mercury
    ui->souvenir3->setIcon(QIcon(":/backpackItems/mercuryBackpack.png"));
    ui->souvenir3->setIconSize(QSize(50,50));
    ui->souvenir3->setStyleSheet("QPushButton{background: transparent;}");
    ui->souvenir4->setEnabled(true); //Venus
    ui->souvenir4->setIcon(QIcon(":/backpackItems/venusBackpack.ico"));
    ui->souvenir4->setIconSize(QSize(50,50));
    ui->souvenir4->setStyleSheet("QPushButton{background: transparent;}");

    ui->souvenir5->setEnabled(true); //Mars
    ui->souvenir5->setIcon(QIcon(":/backpackItems/marsBackpack.png"));
    ui->souvenir5->setIconSize(QSize(50,50));
    ui->souvenir5->setStyleSheet("QPushButton{background: transparent;}");

    ui->souvenir6->setEnabled(true); //Jupiter
    ui->souvenir6->setIcon(QIcon(":/backpackItems/jupiterBackpack.ico"));
    ui->souvenir6->setIconSize(QSize(50,50));
    ui->souvenir6->setStyleSheet("QPushButton{background: transparent;}");

    ui->souvenir7->setEnabled(true); //Saturn
    ui->souvenir7->setIcon(QIcon(":/backpackItems/saturnBackpack.png"));
    ui->souvenir7->setIconSize(QSize(50,50));
    ui->souvenir7->setStyleSheet("QPushButton{background: transparent;}");

    ui->souvenir8->setEnabled(true); //Uranus
    ui->souvenir8->setIcon(QIcon(":/backpackItems/uranusBackpack.png"));
    ui->souvenir8->setIconSize(QSize(50,50));
    ui->souvenir8->setStyleSheet("QPushButton{background: transparent;}");

    ui->souvenir9->setEnabled(true); //Neptune
    ui->souvenir9->setIcon(QIcon(":/backpackItems/neptuneBackpack.ico"));
    ui->souvenir9->setIconSize(QSize(50,50));
    ui->souvenir9->setStyleSheet("QPushButton{background: transparent;}");

    ui->currentSouvenir->setEnabled(false);
    ui->currentSouvenir->setVisible(false);
    ui->souvenirInformation->setEnabled(false);
    ui->souvenirInformation->setVisible(false);
    currentPlanet = "none";
    }
    else {
        itemSelected = 0;
        if (currentPlanet == "earth"){
            currentPlanet = "none";
            on_souvenir1_clicked();
        }
    else if (currentPlanet == "moon"){
            currentPlanet = "none";
            on_souvenir2_clicked();
        }
        else if(currentPlanet == "mercury"){
            currentPlanet = "none";
            on_souvenir3_clicked();
        }
        else if (currentPlanet == "venus"){
            currentPlanet = "none";
            on_souvenir4_clicked();
        }
        else if (currentPlanet == "mars"){
            currentPlanet = "none";
            on_souvenir5_clicked();
        }
        else if (currentPlanet == "jupiter"){
            currentPlanet = "none";
            on_souvenir6_clicked();
        }
        else if (currentPlanet == "saturn"){
            currentPlanet = "none";
            on_souvenir7_clicked();
        }
        else if (currentPlanet == "uranus"){
            currentPlanet = "none";
            on_souvenir8_clicked();
        }
        else if (currentPlanet == "neptune"){
            currentPlanet = "none";
            on_souvenir9_clicked();
        }
    }
}
//Earth
void Backpack::on_souvenir1_clicked()
{
    ui->currentSouvenir->setVisible(false);
    ui->currentSouvenir->setEnabled(false);
    ui->souvenirInformation->setVisible(false);
    ui->souvenirInformation->setEnabled(false);
  if(currentPlanet == "none"){
    currentPlanet = "earth";
    ui->planetName->clear();
    ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                       "Earth"
                                       "</h1></P></font><center>");
    ui->background->setStyleSheet("background-image: url(:/journalItems/earth_Journal.jpg);");
    ui->souvenir1->setIcon(QIcon(":/earthItems/earthOxygen.png"));
    ui->souvenir1->setIconSize(QSize(50,50));
    ui->souvenir1->setStyleSheet("QPushButton{background: transparent;}");
    ui->souvenir1->setVisible(true);
    ui->souvenir1->setEnabled(true);

    ui->souvenir2->setIcon(QIcon(":/earthItems/earthRadio.png"));
    ui->souvenir2->setIconSize(QSize(50,50));
    ui->souvenir2->setStyleSheet("QPushButton{background: transparent;}");
    ui->souvenir2->setVisible(true);
    ui->souvenir2->setEnabled(true);

    ui->souvenir3->setIcon(QIcon(":/earthItems/earthSpaceBlanket.png"));
    ui->souvenir3->setIconSize(QSize(50,50));
    ui->souvenir3->setStyleSheet("QPushButton{background: transparent;}");
    ui->souvenir3->setVisible(true);
    ui->souvenir3->setEnabled(true);

    ui->souvenir4->setIcon(QIcon(":/earthItems/earthWaterBottle.png"));
    ui->souvenir4->setIconSize(QSize(50,50));
    ui->souvenir4->setStyleSheet("QPushButton{background: transparent;}");
    ui->souvenir4->setVisible(true);
    ui->souvenir4->setEnabled(true);

    ui->souvenir5->setIcon(QIcon(":/earthItems/earthFood.png"));
    ui->souvenir5->setIconSize(QSize(50,50));
    ui->souvenir5->setStyleSheet("QPushButton{background: transparent;}");
    ui->souvenir5->setVisible(true);
    ui->souvenir5->setEnabled(true);

    ui->souvenir6->setEnabled(false);
    ui->souvenir6->setVisible(false);

    ui->souvenir7->setEnabled(false);
    ui->souvenir7->setVisible(false);

    ui->souvenir8->setEnabled(false);
    ui->souvenir8->setVisible(false);

    ui->souvenir9->setEnabled(false);
    ui->souvenir9->setVisible(false);
    }
  else {
      itemSelected = 1;
      showItemInformation();
  }
}
// Moon
void Backpack::on_souvenir2_clicked()
{

    ui->currentSouvenir->setVisible(false);
    ui->currentSouvenir->setEnabled(false);
    ui->souvenirInformation->setVisible(false);
    ui->souvenirInformation->setEnabled(false);
  if(currentPlanet == "none"){
    currentPlanet = "moon";
    ui->planetName->clear();
    ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                       "Moon"
                                       "</h1></P></font><center>");

    ui->background->setStyleSheet("background-image: url(:/journalItems/moon_Journal.jpg);");

    ui->souvenir1->setIcon(QIcon(":/moonItems/moonFarSide.png"));
    ui->souvenir1->setIconSize(QSize(50,50));
    ui->souvenir1->setStyleSheet("QPushButton{background: transparent;}");
    ui->souvenir1->setVisible(true);
    ui->souvenir1->setEnabled(true);

    ui->souvenir2->setIcon(QIcon(":/moonItems/moonNearSide.png"));
    ui->souvenir2->setIconSize(QSize(50,50));
    ui->souvenir2->setStyleSheet("QPushButton{background: transparent;}");
    ui->souvenir2->setVisible(true);
    ui->souvenir2->setEnabled(true);

    ui->souvenir3->setIcon(QIcon(":/moonItems/moonMaria.png"));
    ui->souvenir3->setIconSize(QSize(50,50));
    ui->souvenir3->setStyleSheet("QPushButton{background: transparent;}");
    ui->souvenir3->setVisible(true);
    ui->souvenir3->setEnabled(true);

    ui->souvenir4->setVisible(false);
    ui->souvenir4->setEnabled(false);

    ui->souvenir5->setVisible(false);
    ui->souvenir5->setEnabled(false);

    ui->souvenir6->setEnabled(false);
    ui->souvenir6->setVisible(false);

    ui->souvenir7->setEnabled(false);
    ui->souvenir7->setVisible(false);

    ui->souvenir8->setEnabled(false);
    ui->souvenir8->setVisible(false);

    ui->souvenir9->setEnabled(false);
    ui->souvenir9->setVisible(false);
    }
  else {
      itemSelected = 2;
      showItemInformation();
  }
}

void Backpack::on_souvenir3_clicked() // Mercury
{
    ui->currentSouvenir->setVisible(false);
    ui->currentSouvenir->setEnabled(false);
    ui->souvenirInformation->setVisible(false);
    ui->souvenirInformation->setEnabled(false);
  if(currentPlanet == "none"){
      ui->planetName->clear();
      ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                         "Mercury"
                                         "</h1></P></font><center>");
    currentPlanet = "mercury";
    ui->background->setStyleSheet("background-image: url(:/journalItems/mercury_Journal.jpg);");
    ui->souvenir1->setIcon(QIcon(":/mercuryItems/mercuryMantle.png"));
    ui->souvenir1->setIconSize(QSize(50,50));
    ui->souvenir1->setStyleSheet("QPushButton{background: transparent;}");
    ui->souvenir1->setVisible(true);
    ui->souvenir1->setEnabled(true);

    ui->souvenir2->setIcon(QIcon(":/mercuryItems/mercuryMetalCore.png"));
    ui->souvenir2->setIconSize(QSize(50,50));
    ui->souvenir2->setStyleSheet("QPushButton{background: transparent;}");
    ui->souvenir2->setVisible(true);
    ui->souvenir2->setEnabled(true);

    ui->souvenir3->setIcon(QIcon(":/mercuryItems/moonCrustSample.png"));
    ui->souvenir3->setIconSize(QSize(50,50));
    ui->souvenir3->setStyleSheet("QPushButton{background: transparent;}");
    ui->souvenir3->setVisible(true);
    ui->souvenir3->setEnabled(true);

    ui->souvenir4->setVisible(false);
    ui->souvenir4->setEnabled(false);

    ui->souvenir5->setVisible(false);
    ui->souvenir5->setEnabled(false);

    ui->souvenir6->setEnabled(false);
    ui->souvenir6->setVisible(false);

    ui->souvenir7->setEnabled(false);
    ui->souvenir7->setVisible(false);

    ui->souvenir8->setEnabled(false);
    ui->souvenir8->setVisible(false);

    ui->souvenir9->setEnabled(false);
    ui->souvenir9->setVisible(false);
    }
  else {
      itemSelected = 3;
      showItemInformation();
  }
}


void Backpack::on_souvenir4_clicked() //Venus
{
    ui->currentSouvenir->setVisible(false);
    ui->currentSouvenir->setEnabled(false);
    ui->souvenirInformation->setVisible(false);
    ui->souvenirInformation->setEnabled(false);
  if(currentPlanet == "none"){

      ui->planetName->clear();
      ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                         "Venus"
                                         "</h1></P></font><center>");
    currentPlanet = "venus";
    ui->background->setStyleSheet("background-image: url(:/journalItems/Venus_Journal.jpg);");

    ui->souvenir1->setIcon(QIcon(":/venusItems/venusMagneticFieldSample.png"));
    ui->souvenir1->setIconSize(QSize(50,50));
    ui->souvenir1->setStyleSheet("QPushButton{background: transparent;}");
    ui->souvenir1->setVisible(true);
    ui->souvenir1->setEnabled(true);

    ui->souvenir2->setIcon(QIcon(":/venusItems/venusRockyMantle.png"));
    ui->souvenir2->setIconSize(QSize(50,50));
    ui->souvenir2->setStyleSheet("QPushButton{background: transparent;}");
    ui->souvenir2->setVisible(true);
    ui->souvenir2->setEnabled(true);

    ui->souvenir3->setVisible(false);
    ui->souvenir3->setEnabled(false);

    ui->souvenir4->setVisible(false);
    ui->souvenir4->setEnabled(false);

    ui->souvenir5->setVisible(false);
    ui->souvenir5->setEnabled(false);

    ui->souvenir6->setEnabled(false);
    ui->souvenir6->setVisible(false);

    ui->souvenir7->setEnabled(false);
    ui->souvenir7->setVisible(false);

    ui->souvenir8->setEnabled(false);
    ui->souvenir8->setVisible(false);

    ui->souvenir9->setEnabled(false);
    ui->souvenir9->setVisible(false);
    }
  else {
      itemSelected = 4;
      showItemInformation();
  }
}
void Backpack::on_souvenir5_clicked()
{
    ui->currentSouvenir->setVisible(false);
    ui->currentSouvenir->setEnabled(false);
    ui->souvenirInformation->setVisible(false);
    ui->souvenirInformation->setEnabled(false);
  if(currentPlanet == "none"){
      ui->planetName->clear();
      ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                         "Mars"
                                         "</h1></P></font><center>");
    currentPlanet = "mars";
    ui->background->setStyleSheet("background-image: url(:/journalItems/Mars_Journal.jpg);");
    ui->souvenir1->setIcon(QIcon(":/marsItems/marsIron.png"));
    ui->souvenir1->setIconSize(QSize(50,50));
    ui->souvenir1->setStyleSheet("QPushButton{background: transparent;}");
    ui->souvenir1->setVisible(true);
    ui->souvenir1->setEnabled(true);

    ui->souvenir2->setIcon(QIcon(":/marsItems/marsSoil.png"));
    ui->souvenir2->setIconSize(QSize(50,50));
    ui->souvenir2->setStyleSheet("QPushButton{background: transparent;}");
    ui->souvenir2->setVisible(true);
    ui->souvenir2->setEnabled(true);

    ui->souvenir3->setVisible(false);
    ui->souvenir3->setEnabled(false);

    ui->souvenir4->setVisible(false);
    ui->souvenir4->setEnabled(false);

    ui->souvenir5->setVisible(false);
    ui->souvenir5->setEnabled(false);

    ui->souvenir6->setEnabled(false);
    ui->souvenir6->setVisible(false);

    ui->souvenir7->setEnabled(false);
    ui->souvenir7->setVisible(false);

    ui->souvenir8->setEnabled(false);
    ui->souvenir8->setVisible(false);

    ui->souvenir9->setEnabled(false);
    ui->souvenir9->setVisible(false);
    }
  else {
      itemSelected = 5;
      showItemInformation();
  }
}
void Backpack::on_souvenir6_clicked()
{
    ui->currentSouvenir->setVisible(false);
    ui->currentSouvenir->setEnabled(false);
    ui->souvenirInformation->setVisible(false);
    ui->souvenirInformation->setEnabled(false);
  if(currentPlanet == "none"){
      ui->planetName->clear();
      ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                         "Jupiter"
                                         "</h1></P></font><center>");
    currentPlanet = "jupiter";
    ui->background->setStyleSheet("background-image: url(:/journalItems/Jupiter_Journal.jpg);");

    ui->souvenir1->setIcon(QIcon(":/jupiterItems/jupiterCore.png"));
    ui->souvenir1->setIconSize(QSize(50,50));
    ui->souvenir1->setStyleSheet("QPushButton{background: transparent;}");
    ui->souvenir1->setVisible(true);
    ui->souvenir1->setEnabled(true);

    ui->souvenir2->setIcon(QIcon(":/jupiterItems/jupiterLiquidMetalicHydrogen.png"));
    ui->souvenir2->setIconSize(QSize(50,50));
    ui->souvenir2->setStyleSheet("QPushButton{background: transparent;}");
    ui->souvenir2->setVisible(true);
    ui->souvenir2->setEnabled(true);

    ui->souvenir3->setVisible(false);
    ui->souvenir3->setEnabled(false);

    ui->souvenir4->setVisible(false);
    ui->souvenir4->setEnabled(false);

    ui->souvenir5->setVisible(false);
    ui->souvenir5->setEnabled(false);

    ui->souvenir6->setEnabled(false);
    ui->souvenir6->setVisible(false);

    ui->souvenir7->setEnabled(false);
    ui->souvenir7->setVisible(false);

    ui->souvenir8->setEnabled(false);
    ui->souvenir8->setVisible(false);

    ui->souvenir9->setEnabled(false);
    ui->souvenir9->setVisible(false);
    }
  else {
      itemSelected = 6;
      showItemInformation();
  }
}
void Backpack::on_souvenir7_clicked()
{

    ui->currentSouvenir->setVisible(false);
    ui->currentSouvenir->setEnabled(false);
    ui->souvenirInformation->setVisible(false);
    ui->souvenirInformation->setEnabled(false);
  if(currentPlanet == "none"){
      ui->planetName->clear();
      ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                         "Saturn"
                                         "</h1></P></font><center>");
    currentPlanet = "saturn";
    ui->background->setStyleSheet("background-image: url(:/journalItems/Saturn_Journal.png);");

    ui->souvenir1->setIcon(QIcon(":/saturnItems/saturnCore.png"));
    ui->souvenir1->setIconSize(QSize(50,50));
    ui->souvenir1->setStyleSheet("QPushButton{background: transparent;}");
    ui->souvenir1->setVisible(true);
    ui->souvenir1->setEnabled(true);

    ui->souvenir2->setIcon(QIcon(":/saturnItems/saturnLiquidHydrogen.png"));
    ui->souvenir2->setIconSize(QSize(50,50));
    ui->souvenir2->setStyleSheet("QPushButton{background: transparent;}");
    ui->souvenir2->setVisible(true);
    ui->souvenir2->setEnabled(true);

    ui->souvenir3->setVisible(false);
    ui->souvenir3->setEnabled(false);

    ui->souvenir4->setVisible(false);
    ui->souvenir4->setEnabled(false);

    ui->souvenir5->setVisible(false);
    ui->souvenir5->setEnabled(false);

    ui->souvenir6->setEnabled(false);
    ui->souvenir6->setVisible(false);

    ui->souvenir7->setEnabled(false);
    ui->souvenir7->setVisible(false);

    ui->souvenir8->setEnabled(false);
    ui->souvenir8->setVisible(false);

    ui->souvenir9->setEnabled(false);
    ui->souvenir9->setVisible(false);
    }
  else {
      itemSelected = 7;
      showItemInformation();
  }
}
void Backpack::on_souvenir8_clicked()
{
    ui->currentSouvenir->setVisible(false);
    ui->currentSouvenir->setEnabled(false);
    ui->souvenirInformation->setVisible(false);
    ui->souvenirInformation->setEnabled(false);
  if(currentPlanet == "none"){
      ui->planetName->clear();
      ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                         "Uranus"
                                         "</h1></P></font><center>");
    currentPlanet = "uranus";
    ui->background->setStyleSheet("background-image: url(:/journalItems/uranus_Journal.jpg);");

    ui->souvenir1->setIcon(QIcon(":/uranusItems/uranusCore.png"));
    ui->souvenir1->setIconSize(QSize(50,50));
    ui->souvenir1->setStyleSheet("QPushButton{background: transparent;}");
    ui->souvenir1->setVisible(true);
    ui->souvenir1->setEnabled(true);

    ui->souvenir2->setIcon(QIcon(":/uranusItems/uranusLiquidHydrogen.png"));
    ui->souvenir2->setIconSize(QSize(50,50));
    ui->souvenir2->setStyleSheet("QPushButton{background: transparent;}");
    ui->souvenir2->setVisible(true);
    ui->souvenir2->setEnabled(true);

    ui->souvenir3->setVisible(false);
    ui->souvenir3->setEnabled(false);

    ui->souvenir4->setVisible(false);
    ui->souvenir4->setEnabled(false);

    ui->souvenir5->setVisible(false);
    ui->souvenir5->setEnabled(false);

    ui->souvenir6->setEnabled(false);
    ui->souvenir6->setVisible(false);

    ui->souvenir7->setEnabled(false);
    ui->souvenir7->setVisible(false);

    ui->souvenir8->setEnabled(false);
    ui->souvenir8->setVisible(false);

    ui->souvenir9->setEnabled(false);
    ui->souvenir9->setVisible(false);
    }
  else {
      itemSelected = 8;
      showItemInformation();
  }
}
void Backpack::on_souvenir9_clicked()
{
    ui->currentSouvenir->setVisible(false);
    ui->currentSouvenir->setEnabled(false);
    ui->souvenirInformation->setVisible(false);
    ui->souvenirInformation->setEnabled(false);
  if(currentPlanet == "none"){
      ui->planetName->clear();
      ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                         "Neptune"
                                         "</h1></P></font><center>");
    currentPlanet = "neptune";
    ui->background->setStyleSheet("background-image: url(:/journalItems/Neptune_Journal.jpg);");

    ui->souvenir1->setIcon(QIcon(":/neptuneItems/neptuneCore.png"));
    ui->souvenir1->setIconSize(QSize(50,50));
    ui->souvenir1->setStyleSheet("QPushButton{background: transparent;}");
    ui->souvenir1->setVisible(true);
    ui->souvenir1->setEnabled(true);

    ui->souvenir2->setIcon(QIcon(":/neptuneItems/neptuneLiquidHydrogen.png"));
    ui->souvenir2->setIconSize(QSize(50,50));
    ui->souvenir2->setStyleSheet("QPushButton{background: transparent;}");
    ui->souvenir2->setVisible(true);
    ui->souvenir2->setEnabled(true);

    ui->souvenir3->setVisible(false);
    ui->souvenir3->setEnabled(false);

    ui->souvenir4->setVisible(false);
    ui->souvenir4->setEnabled(false);

    ui->souvenir5->setVisible(false);
    ui->souvenir5->setEnabled(false);

    ui->souvenir6->setEnabled(false);
    ui->souvenir6->setVisible(false);

    ui->souvenir7->setEnabled(false);
    ui->souvenir7->setVisible(false);

    ui->souvenir8->setEnabled(false);
    ui->souvenir8->setVisible(false);

    ui->souvenir9->setEnabled(false);
    ui->souvenir9->setVisible(false);
    }
  else {
      itemSelected = 9;
      showItemInformation();
  }
}


void Backpack::showItemInformation(){
    ui->souvenir1->setEnabled(false);
    ui->souvenir1->setVisible(false);
    ui->souvenir2->setEnabled(false);
    ui->souvenir2->setVisible(false);
    ui->souvenir3->setEnabled(false);
    ui->souvenir3->setVisible(false);
    ui->souvenir4->setEnabled(false);
    ui->souvenir4->setVisible(false);
    ui->souvenir5->setEnabled(false);
    ui->souvenir5->setVisible(false);
    ui->souvenir6->setEnabled(false);
    ui->souvenir6->setVisible(false);
    ui->souvenir7->setEnabled(false);
    ui->souvenir7->setVisible(false);
    ui->souvenir8->setEnabled(false);
    ui->souvenir8->setVisible(false);
    ui->souvenir9->setEnabled(false);
    ui->souvenir9->setVisible(false);
    ui->currentSouvenir->setVisible(true);
    ui->souvenirInformation->setVisible(true);
    ui->currentSouvenir->setStyleSheet("QPushButton{background: transparent;}");
    ui->currentSouvenir->setEnabled(true);
    ui->souvenirInformation->viewport()->setAutoFillBackground(false);
    ui->currentSouvenir->setIconSize(QSize(150,150));
    ui->currentSouvenir->setStyleSheet("QPushButton{background: transparent;}");
    ui->souvenirInformation->clear();
    if(currentPlanet == "earth"){
        if(itemSelected == 1){
            ui->currentSouvenir->setIcon(QIcon(":/earthItems/earthOxygen.png"));
            ui->souvenirInformation->insertHtml("<br><br><br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>This is oxygen very important to take on your mission since you need to breath at all times in order for you not to die. Without it you wouldnt be able to go out into the planets and get samples for us.</P></font>");
            ui->planetName->clear();
            ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                               "Oxygen"
                                               "</h1></P></font><center>");
        }
        else if (itemSelected == 2){
            ui->currentSouvenir->setIcon(QIcon(":/earthItems/earthRadio.png"));
            ui->souvenirInformation->insertHtml("<br><br><br><br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>"
                                                "It is very important that you have a mean of "
                                                                               "communication with us so that we can help you if you "
                                                                               "get into trouble. We can also guide you on what things you"
                                                                               "should collect from each planet. </P></font>");
            ui->planetName->clear();
            ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                               "Radio"
                                               "</h1></P></font><center>");
        }
        else if (itemSelected == 3){
            ui->currentSouvenir->setIcon(QIcon(":/earthItems/earthSpaceBlanket.png"));
            ui->souvenirInformation->insertHtml("<br><br><br><br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>"
                                                "Other planets dont have perfect weather for us humans "
                                                                          "like we do hear on our planet earth so it is vital that "
                                                                          "you maintain warm on the nights with special space blanket"
                                                "</P></font>");
            ui->planetName->clear();
            ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                               "Space Blanket"
                                               "</h1></P></font><center>");

        }
        else if (itemSelected == 4){
            ui->currentSouvenir->setIcon(QIcon(":/earthItems/earthWaterBottle.png"));
            ui->souvenirInformation->insertHtml("<br><br><br><br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>"
                                                "This is a necessary choice you would not be "
                                                                         "able to survive anywhere without water to last "
                                                                         "you on your journey.</P></font>");

            ui->planetName->clear();
            ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                               "Water Bottle"
                                               "</h1></P></font><center>");
        }
        else if (itemSelected == 5){
            ui->currentSouvenir->setIcon(QIcon(":/earthItems/earthFood.png"));
            ui->souvenirInformation->insertHtml("<br><br><br><br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>"
                                                "Good thinking you need food to survive.</P></font>");

            ui->planetName->clear();
            ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                               "Food"
                                               "</h1></P></font><center>");
        }
    }
        if(currentPlanet == "moon"){
            if(itemSelected == 1){
                ui->currentSouvenir->setIcon(QIcon(":/moonItems/moonFarSide.png"));
                ui->souvenirInformation->insertHtml("<br><br><br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>"
                                                    "You are in the far side of the moon that is why if you "
                                                                              "look at the rock it is bumpier then the niear side rocks"
                                                    "</P></font>");
                ui->planetName->clear();
                ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                                   "Far Side of the Moon"
                                                   "</h1></P></font><center>");
            }
            else if (itemSelected == 2){
                ui->currentSouvenir->setIcon(QIcon(":/moonItems/moonNearSide.png"));
                ui->souvenirInformation->insertHtml("<br><br><br><br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>"
                                                    "You are standing on the near sode of the moon which is the side"
                                                                              "that we can see, you can tell that you are in the near side beacuse "
                                                                              "this rock is smoother then that of the far side. Take it to compare "
                                                                              "exactly with the far side"
                                                    " </P></font>");
                ui->planetName->clear();
                ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                                   "Near Side of the Moon"
                                                   "</h1></P></font><center>");

            }
            else if (itemSelected == 3){
                ui->currentSouvenir->setIcon(QIcon(":/moonItems/moonMaria.png"));
                ui->souvenirInformation->insertHtml("<br><br><br><br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>"
                                                    "This componant is called 'maria' you should "
                                                                              "take a sample so that we can analyse it on Earth"
                                                    "</P></font>");
                ui->planetName->clear();
                ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                                   "Moon Maria"
                                                   "</h1></P></font><center>");

            }
    }
        if(currentPlanet == "mercury"){
            if(itemSelected == 1){
                ui->currentSouvenir->setIcon(QIcon(":/mercuryItems/mercuryMantle.png"));
                ui->souvenirInformation->insertHtml("<br><br><br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>"
                                                    "This is a piece of the mantle of the planet that has "
                                                                              "chipped off you should keep it to analyse"
                                                    "</P></font>");
                ui->planetName->clear();
                ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                                   "Mercury's Mantle"
                                                   "</h1></P></font><center>");
            }
            else if (itemSelected == 2){
                ui->currentSouvenir->setIcon(QIcon(":/mercuryItems/mercuryMetalCore.png"));
                ui->souvenirInformation->insertHtml("<br><br><br><br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>"
                                                    "It seems like this is a piece of metal of the planets core, "
                                                                              "you should keep it to analyse"
                                                    " </P></font>");
                ui->planetName->clear();
                ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                                   "Mercury's Metal Core"
                                                   "</h1></P></font><center>");

            }
            else if (itemSelected == 3){
                ui->currentSouvenir->setIcon(QIcon(":/mercuryItems/moonCrustSample.png"));
                ui->souvenirInformation->insertHtml("<br><br><br><br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>"
                                                    "We detect you are in the magnetic field you should pick it up so that "
                                                                              "we can figure what it is back home"
                                                    "</P></font>");
                ui->planetName->clear();
                ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                                   "Mercury's Crust Sample"
                                                   "</h1></P></font><center>");

            }
        }
        if(currentPlanet == "venus"){
            if(itemSelected == 1){
                ui->currentSouvenir->setIcon(QIcon(":/venusItems/venusMagneticFieldSample.png"));
                ui->souvenirInformation->insertHtml("<br><br><br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>"
                                                    "We detect you are in the magnetic field you should pick it up so that "
                                                    "</P></font>");
                ui->planetName->clear();
                ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                                   "Magnetic Field Sample"
                                                   "</h1></P></font><center>");
            }
            else if (itemSelected == 2){
                ui->currentSouvenir->setIcon(QIcon(":/venusItems/venusRockyMantle.png"));
                ui->souvenirInformation->insertHtml("<br><br><br><br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>"
                                                    "This looks like a sample from the rocky mantle of the planet. You "
                                                                              "should get a sample"
                                                    "</P></font>");
                ui->planetName->clear();
                ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                                   "Rocky Mantle"
                                                   "</h1></P></font><center>");

            }
        }

        if(currentPlanet == "mars"){
            if(itemSelected == 1){
                ui->currentSouvenir->setIcon(QIcon(":/marsItems/marsIron.png"));
                ui->souvenirInformation->insertHtml("<br><br><br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>"
                                                    "This looks like Iron you should take some and compare it to "
                                                                              "Earths Iron"
                                                    "</P></font>");
                ui->planetName->clear();
                ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                                   "Iron"
                                                   "</h1></P></font><center>");
            }
            else if (itemSelected == 2){
                ui->currentSouvenir->setIcon(QIcon(":/marsItems/marsSoil.png"));
                ui->souvenirInformation->insertHtml("<br><br><br><br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>"
                                                    "This is some of the planets soil, you should collect some and "
                                                                              "bring it home"
                                                    "</P></font>");
                ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                                   "Soil"
                                                   "</h1></P></font><center>");

            }
        }
        if(currentPlanet == "jupiter"){
            if(itemSelected == 1){
                ui->currentSouvenir->setIcon(QIcon(":/jupiterItems/jupiterCore.png"));
                ui->souvenirInformation->insertHtml("<br><br><br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>"
                                                    "It looks like this is a piese of the planets core, you should take "
                                                                              "a sample of this"
                                                    "</P></font>");
                ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                                   "Jupiter's Core"
                                                   "</h1></P></font><center>");
            }
            else if (itemSelected == 2){
                ui->currentSouvenir->setIcon(QIcon(":/jupiterItems/jupiterLiquidMetalicHydrogen.png"));
                ui->souvenirInformation->insertHtml("<br><br><br><br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>"
                                                    "Hmm... we dont know what this can be. Great find you should definately bring a "
                                                                              "sample back home"
                                                    "</P></font>");
                ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                                   "Liquid Metalic Hydrogen"
                                                   "</h1></P></font><center>");

            }
        }
        if(currentPlanet == "saturn"){
            if(itemSelected == 1){
                ui->currentSouvenir->setIcon(QIcon(":/saturnItems/saturnCore.png"));
                ui->souvenirInformation->insertHtml("<br><br><br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>"
                                                    "It looks like this is a piese of the planets core, you should take "
                                                                              "a sample of this"
                                                    "</P></font>");
                ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                                   "Saturn's Core"
                                                   "</h1></P></font><center>");
            }
            else if (itemSelected == 2){
                ui->currentSouvenir->setIcon(QIcon(":/saturnItems/saturnLiquidHydrogen.png"));
                ui->souvenirInformation->insertHtml("<br><br><br><br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>"
                                                    "Hmm... we dont know what this can be. Great find you should definately bring a "
                                                                              "sample back home"
                                                    "</P></font>");
                ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                                   "Liquid Hydrogen"
                                                   "</h1></P></font><center>");
            }
        }
        if(currentPlanet == "uranus"){
            if(itemSelected == 1){
                ui->currentSouvenir->setIcon(QIcon(":/uranusItems/uranusCore.png"));
                ui->souvenirInformation->insertHtml("<br><br><br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>"
                                                    "It looks like this is a piese of the planets core, you should take "
                                                                              "a sample of this"
                                                    "</P></font>");
                ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                                   "Uranus Core"
                                                   "</h1></P></font><center>");
            }
            else if (itemSelected == 2){
                ui->currentSouvenir->setIcon(QIcon(":/uranusItems/uranusLiquidHydrogen.png"));
                ui->souvenirInformation->insertHtml("<br><br><br><br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>"
                                                    "Hmm... we dont know what this can be. Great find you should definately bring a "
                                                                              "sample back home"
                                                    "</P></font>");
                ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                                   "Liquid Hydrogen"
                                                   "</h1></P></font><center>");
            }
        }
        if(currentPlanet == "neptune"){
            if(itemSelected == 1){
                ui->currentSouvenir->setIcon(QIcon(":/neptuneItems/neptuneCore.png"));
                ui->souvenirInformation->insertHtml("<br><br><br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>"
                                                    "It looks like this is a piese of the planets core, you should take "
                                                                              "a sample of this"
                                                    "</P></font>");
                ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                                   "Neptune's Core"
                                                   "</h1></P></font><center>");
            }
            else if (itemSelected == 2){
                ui->currentSouvenir->setIcon(QIcon(":/neptuneItems/neptuneLiquidHydrogen.png"));
                ui->souvenirInformation->insertHtml("<br><br><br><br><font color='BLACK'><P style = 'font-family:Comic Sans MS;'>"
                                                    "Hmm... we dont know what this can be. Great find you should definately bring a "
                                                                              "sample back home"
                                                    "</P></font>");
                ui->planetName->insertHtml("<center><font color='BLACK' size ='6' ><P style = 'font-family:Comic Sans MS;'><h1>"
                                                   "Liquid Hydrogen"
                                                   "</h1></P></font><center>");
            }
        }
}

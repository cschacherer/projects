#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QObject>
#include <QMainWindow>
#include <QFileDialog>
#include <QColorDialog>
#include <QPainter>
#include <QToolButton>
#include <QGraphicsScene>
#include <QVector>
#include "frame.h"
#include "mygraphicsview.h"
#include <QTimer>
#include <QDateTime>
#include <Magick++.h>

using namespace Magick;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public: //style: variables lowercase
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QPainter paintBrush;
    Frame frames;
    QWidget toolbar;
    QColor selectedColor;
    QGraphicsScene *scene, *previewScene;
    QPixmap image;
    QTimer myTimer, myZeroTimer;
    QDateTime start, end;
    QVector<MyGraphicsView*> framesVector;
    int frameCount;
    int selectedFrame;
    int gridSquareSize;
    int fps;
    void (*ptr) (int);
    int brushSize;


    // void Draw(Point mousePosition);
    void DisplayImage();
    void PreviewFrames();
    void LoadFrames();
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

    void SetImageView(int);
    void SetFrameView(int);
    void UpdateFrameView();
    void UpdateZeroPreview();


    void TurnOffButton();

private slots:
    void BrushClicked();
    void EraseClicked();
    void FillClicked();
    void LineClicked();
    void RectangleClicked();
    void StampClicked();
    void UpdatePreview();

    void FPSClicked();

    void AddFrameClicked();
    void DeleteFrameClicked();
    void NewFrameSelected(int);

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionClose_triggered();

    void on_HelpButton_clicked();
    //Stamps
    void HeartStampSelected();
    void DiamondStampSelected();
    void TriangleStampSelected();
    void CustomSelected();
    //Immediate Colors
        void BlackSelected();
        void GreySelected();
        void WhiteSelected();
        void BlueSelected();
        void GreenSelected();
        void YellowSelected();
        void CyanSelected();
        void PurpleSelected();
        void RedSelected();

    /*void on_ColorButton_clicked();

    void on_BrushSizeButton_clicked();*/

    void on_ExportButton_clicked();

signals:

    void BrushSignal();
    void AddFrameSignal();
    void DeleteFrameSignal(int index);
    void GetFrameSize();
    void UserGridSize(int);



private:
    Ui::MainWindow *ui;
    int getMouseX(QMouseEvent * event);
    int getMouseY(QMouseEvent * event);
    void drawRectangle();
    void drawLine();
    void drawStraightLine(int startRow, int endRow, int column, int gridSquareSize);
    void Erase(QMouseEvent * event);
    void DrawHeart(int gridSquareSize, const QPen pen, QBrush brush, qreal pixelRow, qreal pixelColumn);
    void DrawDiamond(int gridSquareSize, const QPen pen, QBrush brush, qreal pixelRow, qreal pixelColumn);
    void DrawTriangle(int gridSquareSize, const QPen pen, QBrush brush, qreal pixelRow, qreal pixelColumn);
    void DisableStamps();
    void UnselectStamp();
    bool mousePressed = false;
    bool drawingLine = false;
    bool squareClicked = false;
    bool heartStampInProgress = false;
    bool diamondStampInProgress = false;
    bool triangleStampInProgress = false;
    int initialMouseX;
    int initialMouseY;
    int finalMouseX;
    int finalMouseY;
    int index=0;
    int frame = 0;
    bool hasChanged;
    bool erasing;
    int numberOfFrames;
    QString gridSize;
    bool isBrush;
    bool fillClicked;
    bool isStamped;
};

#endif // MAINWINDOW_H

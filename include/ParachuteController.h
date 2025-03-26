#ifndef PARACHUTECONTROLLER_H
#define PARACHUTECONTROLLER_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTranslator>
//#include "ui_parachute.h"
#include "ParachuteModel.h"


namespace Ui {
    class MainWindow;  // <-- forward declaration
}

class ParachuteController : public QMainWindow {
    Q_OBJECT

public:
    explicit ParachuteController(QWidget* parent = nullptr);
    ~ParachuteController();

private slots:
    void updateSectorsFromSlider(int value);
    void updateSectorsFromSpinBox(int value);
    void updateTracksFromSlider(int value);
    void updateTracksFromSpinBox(int value);
    void chooseColor();
    void chooseParachuteColor();
    void updateParachute();
    void toggleView();
    void openFile();
    void saveFile();
    void onQuit();
    void showAboutDialog();
    void switchToEnglish();
    void switchToFrench();
    void updateBinaryView();

private:
    Ui::MainWindow *ui;
    QColor parachuteColor;
    QColor outerColor = Qt::white;
    ParachuteModel model;
    QTranslator translatorFr;
    QTranslator translatorEn;
    QGraphicsScene *scene;        
    QGraphicsScene *binaryScene; 
    void drawParachute();
};

#endif // PARACHUTECONTROLLER_H
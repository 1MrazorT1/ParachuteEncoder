#ifndef PARACHUTECONTROLLER_H
#define PARACHUTECONTROLLER_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTranslator>
#include "ui_parachute.h"
#include "ParachuteModel.h"

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
    ParachuteModel model;
    QTranslator translatorFr;
    QTranslator translatorEn;
    QGraphicsScene *scene;        
    QGraphicsScene *binaryScene; 
    void drawParachute();
};

#endif // PARACHUTECONTROLLER_H
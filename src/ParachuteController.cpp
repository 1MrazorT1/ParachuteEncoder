#include "ParachuteController.h"
#include <QColorDialog>
#include <QPen>
#include <QBrush>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QGraphicsEllipseItem>

ParachuteController::ParachuteController(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      model(21, 5),
      parachuteColor(Qt::red)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->parachuteView->setScene(scene);
    ui->parachuteView->setRenderHint(QPainter::Antialiasing);
    binaryScene = new QGraphicsScene(this);
    ui->binaryGraphicsView->setScene(binaryScene);
    ui->binaryGraphicsView->setRenderHint(QPainter::Antialiasing);
    connect(ui->messageInput, &QLineEdit::textChanged, this, &ParachuteController::updateBinaryView);
    QMenu *languageMenu = menuBar()->addMenu(tr("&Language"));
    QAction *frenchAction = new QAction(tr("French (Fr)"), this);
    connect(frenchAction, &QAction::triggered, this, &ParachuteController::switchToFrench);
    languageMenu->addAction(frenchAction);
    QAction *englishAction = new QAction(tr("English (En)"), this);
    connect(englishAction, &QAction::triggered, this, &ParachuteController::switchToEnglish);
    languageMenu->addAction(englishAction);
    scene = new QGraphicsScene(this);
    ui->parachuteView->setScene(scene);
    ui->parachuteView->setRenderHint(QPainter::Antialiasing);
    connect(ui->sliderSectors, &QSlider::valueChanged, this, &ParachuteController::updateSectorsFromSlider);
    connect(ui->spinSectors, QOverload<int>::of(&QSpinBox::valueChanged), this, &ParachuteController::updateSectorsFromSpinBox);
    connect(ui->sliderTracks, &QSlider::valueChanged, this, &ParachuteController::updateTracksFromSlider);
    connect(ui->spinTracks, QOverload<int>::of(&QSpinBox::valueChanged),this, &ParachuteController::updateTracksFromSpinBox);
    connect(ui->colorButton, &QPushButton::clicked, this, &ParachuteController::chooseColor);
    connect(ui->messageInput, &QLineEdit::textChanged, [&](const QString& text) {model.setMessage(text);});
    connect(&model, &ParachuteModel::binaryMapChanged, this, &ParachuteController::updateParachute);
    connect(ui->toggleViewButton, &QPushButton::clicked, this, &ParachuteController::toggleView);
    connect(ui->messageInput, &QLineEdit::textChanged, this, &ParachuteController::updateBinaryView);

    QMenu *fileMenu = menuBar()->addMenu("&File");
    QAction *openAction = new QAction("&Open...", this);
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, &QAction::triggered, this, &ParachuteController::openFile);
    fileMenu->addAction(openAction);
    QAction *saveAction = new QAction("&Save...", this);
    saveAction->setShortcut(QKeySequence::Save);
    connect(saveAction, &QAction::triggered, this, &ParachuteController::saveFile);
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    QAction *quitAction = new QAction("&Quit", this);
    quitAction->setShortcut(QKeySequence::Quit);
    connect(quitAction, &QAction::triggered, this, &ParachuteController::onQuit);
    fileMenu->addAction(quitAction);
    QMenu *helpMenu = menuBar()->addMenu("&Help");
    QAction *aboutAction = new QAction("&About", this);
    connect(aboutAction, &QAction::triggered, this, &ParachuteController::showAboutDialog);
    helpMenu->addAction(aboutAction);
    drawParachute();
}

ParachuteController::~ParachuteController()
{
    delete ui;
}

void ParachuteController::updateParachute()
{
    drawParachute();
}

void ParachuteController::updateSectorsFromSlider(int value)
{
    if (ui->spinSectors->value() != value)
        ui->spinSectors->setValue(value);

    drawParachute();
}

void ParachuteController::updateSectorsFromSpinBox(int value)
{
    if (ui->sliderSectors->value() != value)
        ui->sliderSectors->setValue(value);

    drawParachute();
}

void ParachuteController::updateTracksFromSlider(int value)
{
    if (ui->spinTracks->value() != value)
        ui->spinTracks->setValue(value);

    drawParachute();
}

void ParachuteController::updateTracksFromSpinBox(int value)
{
    if (ui->sliderTracks->value() != value)
        ui->sliderTracks->setValue(value);

    drawParachute();
}

void ParachuteController::chooseColor()
{
    QColor color = QColorDialog::getColor(parachuteColor, this, tr("Select Parachute Color"));
    if (color.isValid()) {
        parachuteColor = color;
        drawParachute();
    }
}

void ParachuteController::drawParachute()
{
    scene->clear();

    int sectors = ui->spinSectors->value();
    int tracks = ui->spinTracks->value();
    int R = 200;
    QPen pen(Qt::black);
    QBrush defaultBrush(Qt::white);
    std::vector<int> binaryMap = model.getBinaryMap();
    bool hasData = !binaryMap.empty();
    for (int t = 0; t < tracks; ++t) {
        for (int s = 0; s < sectors; ++s) {
            int index = t * sectors + s;
            QColor fillColor = Qt::white;
            if (hasData && index < (int)binaryMap.size()) {
                fillColor = (binaryMap[index] == 1) ? parachuteColor : Qt::white;
            }
            double a1 = s * (2 * M_PI / sectors);
            double a2 = (s + 1) * (2 * M_PI / sectors);
            double r1 = (double)t / tracks * R;
            double r2 = (double)(t + 1) / tracks * R;
            QPointF p1(r1 * cos(a1), r1 * sin(a1));
            QPointF p2(r1 * cos(a2), r1 * sin(a2));
            QPointF q1(r2 * cos(a1), r2 * sin(a1));
            QPointF q2(r2 * cos(a2), r2 * sin(a2));
            QPolygonF sector;
            sector << p1 << p2 << q2 << q1;
            scene->addPolygon(sector, pen, QBrush(fillColor));
        }
    }
    scene->update();
    ui->parachuteView->update();
}

void ParachuteController::toggleView()
{
    if (ui->viewStack->currentIndex() == 0) {
        ui->viewStack->setCurrentIndex(1);
        ui->toggleViewButton->setText("Switch to Parachute View");
        updateBinaryView();
    } else {
        ui->viewStack->setCurrentIndex(0);
        ui->toggleViewButton->setText("Switch to Binary View");
    }
}

void ParachuteController::updateBinaryView()
{
    binaryScene->clear();
    std::vector<int> bits = model.getBinaryMap();
    if (bits.empty()) {
        return;
    }
    const int columns = 20;
    const int dotDiameter = 12;
    const int spacing = 15;
    for (size_t i = 0; i < bits.size(); ++i) {
        int bit = bits[i];
        int row = i / columns;
        int col = i % columns;
        int x = col * spacing;
        int y = row * spacing;
        QColor fillColor = (bit == 1) ? Qt::red : Qt::gray;
        QGraphicsEllipseItem *circleItem = binaryScene->addEllipse(
            x, y, dotDiameter, dotDiameter,
            QPen(Qt::black),
            QBrush(fillColor)
        );
    }
    binaryScene->update();
    ui->binaryGraphicsView->update();
}

void ParachuteController::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        QString(),
        tr("Text Files (*.txt);;All Files (*)")
    );
    if (filePath.isEmpty()) return;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot open file for reading."));
        return;
    }
    QTextStream in(&file);
    QString message      = in.readLine().trimmed();
    QString sectorsLine  = in.readLine().trimmed();
    QString tracksLine   = in.readLine().trimmed();
    file.close();
    if (!message.isEmpty()) {
        ui->messageInput->setText(message);
    }
    if (!sectorsLine.isEmpty()) {
        ui->spinSectors->setValue(sectorsLine.toInt());
    }
    if (!tracksLine.isEmpty()) {
        ui->spinTracks->setValue(tracksLine.toInt());
    }
}

void ParachuteController::saveFile()
{
    QString filePath = QFileDialog::getSaveFileName(
        this,
        tr("Save File"),
        QString(),
        tr("Text Files (*.txt);;All Files (*)")
    );
    if (filePath.isEmpty()) return;
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot open file for writing."));
        return;
    }
    QTextStream out(&file);
    out << ui->messageInput->text() << "\n";
    out << ui->spinSectors->value() << "\n";
    out << ui->spinTracks->value() << "\n";
    file.close();
}

void ParachuteController::onQuit()
{
    close();
}

void ParachuteController::showAboutDialog()
{
    QMessageBox::about(this,
        tr("About Parachute Encoder"),
        tr("<b>Parachute Encoder</b><br>"
           "A Qt-based application to encode messages in a parachute pattern.<br>"
           "© 2025. All rights reserved."));
}


void ParachuteController::switchToFrench()
{
    qApp->removeTranslator(&translatorEn);
    if (translatorFr.load(":/parachute_fr.qm")) {
        qApp->installTranslator(&translatorFr);
        ui->retranslateUi(this);
    } else {
        QMessageBox::warning(this, tr("Error"), tr("Could not load the French translation!"));
    }
}

void ParachuteController::switchToEnglish()
{
    qApp->removeTranslator(&translatorFr);
    ui->retranslateUi(this);
}
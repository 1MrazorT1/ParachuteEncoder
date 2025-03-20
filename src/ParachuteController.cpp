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

ParachuteController::ParachuteController(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      model(21, 5),                 // Default: 21 sectors, 5 tracks in the model
      parachuteColor(Qt::red)
{
    ui->setupUi(this);

    // Prepare the graphics scene for the parachute view
    scene = new QGraphicsScene(this);
    ui->parachuteView->setScene(scene);
    ui->parachuteView->setRenderHint(QPainter::Antialiasing);

    // --- Connect UI signals to our slots ---
    connect(ui->sliderSectors, &QSlider::valueChanged,
            this, &ParachuteController::updateSectorsFromSlider);
    connect(ui->spinSectors, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &ParachuteController::updateSectorsFromSpinBox);

    connect(ui->sliderTracks, &QSlider::valueChanged,
            this, &ParachuteController::updateTracksFromSlider);
    connect(ui->spinTracks, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &ParachuteController::updateTracksFromSpinBox);

    connect(ui->colorButton, &QPushButton::clicked,
            this, &ParachuteController::chooseColor);

    // Message input -> Model
    connect(ui->messageInput, &QLineEdit::textChanged,
            [&](const QString& text) {
                model.setMessage(text);
            });

    // Model -> Parachute redraw
    connect(&model, &ParachuteModel::binaryMapChanged,
            this, &ParachuteController::updateParachute);

    // Switch between Parachute and Binary views
    connect(ui->toggleViewButton, &QPushButton::clicked,
            this, &ParachuteController::toggleView);

    // Update binary text whenever message changes
    connect(ui->messageInput, &QLineEdit::textChanged,
            this, &ParachuteController::updateBinaryView);

    QMenu *fileMenu = menuBar()->addMenu("&File");

    // "Open…" action
    QAction *openAction = new QAction("&Open...", this);
    openAction->setShortcut(QKeySequence::Open); // typically Ctrl+O
    connect(openAction, &QAction::triggered, this, &ParachuteController::openFile);
    fileMenu->addAction(openAction);

    // "Save…" action
    QAction *saveAction = new QAction("&Save...", this);
    saveAction->setShortcut(QKeySequence::Save); // typically Ctrl+S
    connect(saveAction, &QAction::triggered, this, &ParachuteController::saveFile);
    fileMenu->addAction(saveAction);

    // Separator
    fileMenu->addSeparator();

    // "Quit" action
    QAction *quitAction = new QAction("&Quit", this);
    quitAction->setShortcut(QKeySequence::Quit); // typically Ctrl+Q
    connect(quitAction, &QAction::triggered, this, &ParachuteController::onQuit);
    fileMenu->addAction(quitAction);


    // ─────────────────────────────────────────────────────
    // 2) CREATE HELP MENU
    // ─────────────────────────────────────────────────────
    QMenu *helpMenu = menuBar()->addMenu("&Help");

    QAction *aboutAction = new QAction("&About", this);
    connect(aboutAction, &QAction::triggered, this, &ParachuteController::showAboutDialog);
    helpMenu->addAction(aboutAction);

    // Draw once at startup
    drawParachute();
}

ParachuteController::~ParachuteController()
{
    delete ui;  // Cleans up the UI elements
}

// Called whenever the model signals its data changed
void ParachuteController::updateParachute()
{
    drawParachute();
}

// Sync Sectors when slider changes
void ParachuteController::updateSectorsFromSlider(int value)
{
    if (ui->spinSectors->value() != value)
        ui->spinSectors->setValue(value);

    drawParachute();
}

// Sync Sectors when spin box changes
void ParachuteController::updateSectorsFromSpinBox(int value)
{
    if (ui->sliderSectors->value() != value)
        ui->sliderSectors->setValue(value);

    drawParachute();
}

// Sync Tracks when slider changes
void ParachuteController::updateTracksFromSlider(int value)
{
    if (ui->spinTracks->value() != value)
        ui->spinTracks->setValue(value);

    drawParachute();
}

// Sync Tracks when spin box changes
void ParachuteController::updateTracksFromSpinBox(int value)
{
    if (ui->sliderTracks->value() != value)
        ui->sliderTracks->setValue(value);

    drawParachute();
}

// Use a ColorDialog to pick the fill color for the parachute sectors
void ParachuteController::chooseColor()
{
    QColor color = QColorDialog::getColor(parachuteColor, this, "Select Parachute Color");
    if (color.isValid()) {
        parachuteColor = color;
        drawParachute();
    }
}

// Actually draw the sectors/tracks on the QGraphicsScene
void ParachuteController::drawParachute()
{
    scene->clear();  // Clear old shapes

    int sectors = ui->spinSectors->value();
    int tracks = ui->spinTracks->value();
    int R = 200;  // radius from center to outer track

    QPen pen(Qt::black);
    QBrush defaultBrush(Qt::white);

    // The binary map from your model: 0 or 1 per sector
    std::vector<int> binaryMap = model.getBinaryMap();
    bool hasData = !binaryMap.empty();

    // Build ring by ring (track by track), then sector by sector
    for (int t = 0; t < tracks; ++t) {
        for (int s = 0; s < sectors; ++s) {
            int index = t * sectors + s;

            // Default fill color is white if no message or a zero bit
            QColor fillColor = Qt::white;
            if (hasData && index < (int)binaryMap.size()) {
                fillColor = (binaryMap[index] == 1) ? parachuteColor : Qt::white;
            }

            // Angles for sector s
            double a1 = s * (2 * M_PI / sectors);
            double a2 = (s + 1) * (2 * M_PI / sectors);

            // Inner and outer radii for track t
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

// Switch QStackedWidget pages and update the button text
void ParachuteController::toggleView()
{
    if (ui->viewStack->currentIndex() == 0) {
        ui->viewStack->setCurrentIndex(1);
        ui->toggleViewButton->setText("Switch to Parachute View");
    } else {
        ui->viewStack->setCurrentIndex(0);
        ui->toggleViewButton->setText("Switch to Binary View");
    }
}

// Show the binary representation in the QTextEdit
void ParachuteController::updateBinaryView()
{
    QString binaryText;
    std::vector<int> binaryMap = model.getBinaryMap();

    if (binaryMap.empty()) {
        ui->binaryView->setText("No message entered.");
        return;
    }

    // Build a spaced-out, line-broken string
    for (size_t i = 0; i < binaryMap.size(); i++) {
        binaryText += QString::number(binaryMap[i]);
        if ((i + 1) % 7 == 0)  binaryText += " ";   // space every 7 bits
        if ((i + 1) % 70 == 0) binaryText += "\n";  // line break every 70 bits
    }

    ui->binaryView->setText(binaryText.trimmed());
}


void ParachuteController::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        QString(),
        tr("Text Files (*.txt);;All Files (*)")
    );

    if (filePath.isEmpty()) return; // user canceled

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot open file for reading."));
        return;
    }

    QTextStream in(&file);

    // Example: we'll read lines in order:
    // 1) message text
    // 2) sectors
    // 3) tracks
    QString message      = in.readLine().trimmed();
    QString sectorsLine  = in.readLine().trimmed();
    QString tracksLine   = in.readLine().trimmed();

    file.close();

    // Update UI
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

    if (filePath.isEmpty()) return; // user canceled

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot open file for writing."));
        return;
    }

    QTextStream out(&file);

    // Example format: first line=message, second line=sectors, third line=tracks
    out << ui->messageInput->text() << "\n";
    out << ui->spinSectors->value() << "\n";
    out << ui->spinTracks->value() << "\n";

    file.close();
}

void ParachuteController::onQuit()
{
    // A slot to handle quit
    close(); // same as hitting the window's close button
}

void ParachuteController::showAboutDialog()
{
    QMessageBox::about(this,
        tr("About Parachute Encoder"),
        tr("<b>Parachute Encoder</b><br>"
           "A Qt-based application to encode messages in a parachute pattern.<br>"
           "© 2025. All rights reserved."));
}

#include "ParachuteController.h"

ParachuteController::ParachuteController(QWidget* parent)
    : QWidget(parent), model(21, 5) {

    this->resize(1028, 768);

    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* labelMessage = new QLabel("Enter Message:");
    messageInput = new QLineEdit();

    QLabel* labelSectors = new QLabel("Sectors:");
    QLabel* labelTracks = new QLabel("Tracks:");
    QSlider* sliderSectors = new QSlider(Qt::Horizontal);
    QSlider* sliderTracks = new QSlider(Qt::Horizontal);
    QSpinBox* spinSectors = new QSpinBox();
    QSpinBox* spinTracks = new QSpinBox();

    sliderSectors->setRange(7, 42);
    sliderTracks->setRange(3, 10);
    spinSectors->setRange(7, 42);
    spinTracks->setRange(3, 10);

    layout->addWidget(labelMessage);
    layout->addWidget(messageInput);
    layout->addWidget(labelSectors);
    layout->addWidget(sliderSectors);
    layout->addWidget(spinSectors);
    layout->addWidget(labelTracks);
    layout->addWidget(sliderTracks);
    layout->addWidget(spinTracks);

    parachuteView = new ParachuteView(&model);
    layout->addWidget(parachuteView);

    connect(messageInput, &QLineEdit::textChanged, [&](const QString& text) {
        model.setMessage(text);
        parachuteView->update();
    });

    connect(spinSectors, QOverload<int>::of(&QSpinBox::valueChanged), [&](int value) {
        model.setSectors(value);
        parachuteView->update();
    });

    connect(spinTracks, QOverload<int>::of(&QSpinBox::valueChanged), [&](int value) {
        model.setTracks(value);
        parachuteView->update();
    });
}

#include "../include/ParachuteController.h"

class ParachuteController : public QWidget {
    Q_OBJECT
public:
    ParachuteController(QWidget* parent = nullptr) : QWidget(parent), model(21, 5) {
        QVBoxLayout* layout = new QVBoxLayout(this);
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
        
        layout->addWidget(labelSectors);
        layout->addWidget(sliderSectors);
        layout->addWidget(spinSectors);
        layout->addWidget(labelTracks);
        layout->addWidget(sliderTracks);
        layout->addWidget(spinTracks);
        
        parachuteView = new ParachuteView(&model);
        layout->addWidget(parachuteView);
        
        connect(sliderSectors, &QSlider::valueChanged, spinSectors, &QSpinBox::setValue);
        connect(spinSectors, QOverload<int>::of(&QSpinBox::valueChanged), sliderSectors, &QSlider::setValue);
        connect(spinSectors, QOverload<int>::of(&QSpinBox::valueChanged), [&](int value) {
            model.setSectors(value);
            parachuteView->update();
        });

        connect(sliderTracks, &QSlider::valueChanged, spinTracks, &QSpinBox::setValue);
        connect(spinTracks, QOverload<int>::of(&QSpinBox::valueChanged), sliderTracks, &QSlider::setValue);
        connect(spinTracks, QOverload<int>::of(&QSpinBox::valueChanged), [&](int value) {
            model.setTracks(value);
            parachuteView->update();
        });
    }

private:
    ParachuteModel model;
    ParachuteView* parachuteView;
};
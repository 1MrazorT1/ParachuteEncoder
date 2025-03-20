#ifndef PARACHUTECONTROLLER_H
#define PARACHUTECONTROLLER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QSlider>
#include <QSpinBox>
#include <QLabel>
#include <QLineEdit>
#include "ParachuteModel.h"
#include "ParachuteView.h"

class ParachuteController : public QWidget {
    Q_OBJECT

public:
    explicit ParachuteController(QWidget* parent = nullptr);

private:
    ParachuteModel model;
    ParachuteView* parachuteView;
    QLineEdit* messageInput;
};

#endif // PARACHUTECONTROLLER_H

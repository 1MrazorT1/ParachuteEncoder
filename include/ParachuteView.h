#ifndef PARACHUTEVIEW_H
#define PARACHUTEVIEW_H

#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QPainterPath>
#include "ParachuteModel.h"

class ParachuteView : public QWidget {
    Q_OBJECT

public:
    explicit ParachuteView(ParachuteModel* model, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    ParachuteModel* model = nullptr;
};

#endif // PARACHUTEVIEW_H

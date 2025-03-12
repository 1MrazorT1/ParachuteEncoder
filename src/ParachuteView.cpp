#include "../include/ParachuteView.h"

class ParachuteView : public QWidget {
    Q_OBJECT
public:
    ParachuteView(ParachuteModel* model, QWidget* parent = nullptr) : QWidget(parent), model(model) {}

protected:
    void paintEvent(QPaintEvent*) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        
        int width = this->width();
        int height = this->height();
        int radius = qMin(width, height) / 2 - 10;
        
        int sectors = model->getSectors();
        int tracks = model->getTracks();
        double angleStep = 360.0 / sectors;
        double trackStep = radius / tracks;
        
        for (int t = 0; t < tracks; ++t) {
            for (int s = 0; s < sectors; ++s) {
                double startAngle = s * angleStep;
                int innerRadius = t * trackStep;
                int outerRadius = (t + 1) * trackStep;
                
                painter.setBrush((s + t) % 2 == 0 ? Qt::red : Qt::white);
                painter.drawPie(width/2 - outerRadius, height/2 - outerRadius,
                                outerRadius * 2, outerRadius * 2,
                                startAngle * 16, angleStep * 16);
            }
        }
    }

private:
    ParachuteModel* model;
};

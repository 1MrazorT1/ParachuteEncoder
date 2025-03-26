#include "ParachuteView.h"
#include <cmath>


ParachuteView::ParachuteView(ParachuteModel* model, QWidget* parent) : QWidget(parent), model(model) {}

void ParachuteView::paintEvent(QPaintEvent*)
{
    if (!model) {
        qDebug() << "Error: ParachuteModel is null!";
        return;
    }
    std::vector<int> binaryMap = model->getBinaryMap();

    if (binaryMap.empty()) {
        qDebug() << "Error: binaryMap is empty!";
        return;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    int width  = this->width();
    int height = this->height();
    int R      = qMin(width, height) / 2 - 10;
    int S      = model->getSectors();
    int T      = model->getTracks();
    double a_c = 2.0 * M_PI / S;
    for (int t = 0; t < T; ++t) {
        for (int s = 0; s < S; ++s) {
            int k = t * S + s;
            QColor fillColor = Qt::white;
            if (k < (int)binaryMap.size()) {
                fillColor = (binaryMap[k] == 1) ? parachuteColor : Qt::white;
            }
            double a1 = s * a_c;
            double a2 = (s + 1) * a_c;
            double r_p = (double)t / T * R;
            double r_q = (double)(t + 1) / T * R;
            QPointF p1((int)(r_p * cos(a1) + width / 2),  (int)(r_p * sin(a1) + height / 2));
            QPointF p2((int)(r_p * cos(a2) + width / 2),  (int)(r_p * sin(a2) + height / 2));
            QPointF q1((int)(r_q * cos(a1) + width / 2),  (int)(r_q * sin(a1) + height / 2));
            QPointF q2((int)(r_q * cos(a2) + width / 2),  (int)(r_q * sin(a2) + height / 2));
            QPainterPath path;
            path.moveTo(p1);
            path.lineTo(p2);
            path.lineTo(q2);
            path.lineTo(q1);
            path.closeSubpath();
            painter.setPen(Qt::black);
            painter.setBrush(fillColor);
            painter.drawPath(path);
        }
    }
}

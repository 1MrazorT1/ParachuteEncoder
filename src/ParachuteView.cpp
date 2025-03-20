#include "ParachuteView.h"
#include <cmath>


ParachuteView::ParachuteView(ParachuteModel* model, QWidget* parent) : QWidget(parent), model(model) {}

void ParachuteView::paintEvent(QPaintEvent*)
{
    if (!model) {
        qDebug() << "Error: ParachuteModel is null!";
        return;
    }

    // Retrieve the binary sequence
    std::vector<int> binaryMap = model->getBinaryMap();
    if (binaryMap.empty()) {
        qDebug() << "Error: binaryMap is empty!";
        return;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Determine radius and angles
    int width  = this->width();
    int height = this->height();
    int R      = qMin(width, height) / 2 - 10;  // Full parachute radius

    // Model parameters
    int S      = model->getSectors(); // Number of sectors
    int T      = model->getTracks();  // Number of concentric tracks
    double a_c = 2.0 * M_PI / S;      // Angle per sector

    // Draw trapezoids for each track (t) and sector (s)
    for (int t = 0; t < T; ++t) {
        for (int s = 0; s < S; ++s) {
            // Compute the index in binaryMap
            int k = t * S + s;

            // If we exceed the binary data, fill with white
            QColor fillColor = Qt::white;
            if (k < (int)binaryMap.size()) {
                // We still have data
                fillColor = (binaryMap[k] == 1) ? Qt::red : Qt::white;
            }

            // Angles for this sector
            double a1 = s * a_c;
            double a2 = (s + 1) * a_c;

            // Radii for this track
            double r_p = (double)t / T * R;      // inner radius
            double r_q = (double)(t + 1) / T * R; // outer radius

            // Compute trapezoid corners
            QPointF p1(r_p * cos(a1) + width / 2,  r_p * sin(a1) + height / 2);
            QPointF p2(r_p * cos(a2) + width / 2,  r_p * sin(a2) + height / 2);
            QPointF q1(r_q * cos(a1) + width / 2,  r_q * sin(a1) + height / 2);
            QPointF q2(r_q * cos(a2) + width / 2,  r_q * sin(a2) + height / 2);

            // Draw the trapezoid as a path
            QPainterPath path;
            path.moveTo(p1);
            path.lineTo(p2);
            path.lineTo(q2);
            path.lineTo(q1);
            path.closeSubpath();

            // Color based on the binary value (red = 1, white = 0)
            painter.setPen(Qt::black); // optional black outline
            painter.setBrush(fillColor);
            painter.drawPath(path);
        }
    }
}

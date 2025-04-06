#include <QApplication>
#include <QFile>
#include <QDebug>

#include "ParachuteModel.h"
#include "ParachuteView.h"
#include "ParachuteController.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QFile styleFile(":/src/style.qss");
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = QString::fromUtf8(styleFile.readAll());
        app.setStyleSheet(styleSheet);
    } else {
        qWarning() << "Could not load style.qss!";
    }
    ParachuteController controller;
    controller.show();
    return app.exec();
}

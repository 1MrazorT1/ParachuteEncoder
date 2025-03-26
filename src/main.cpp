#include <QApplication>
#include <QFile>
#include <QDebug>

#include "ParachuteModel.h"
#include "ParachuteView.h"
#include "ParachuteController.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Apply style.qss
    QFile styleFile(":/src/style.qss");  // Use ":/style.qss" if it's in a .qrc resource file
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = QString::fromUtf8(styleFile.readAll());
        app.setStyleSheet(styleSheet);
    } else {
        qWarning() << "Could not load style.qss!";
    }

    // Launch the controller
    ParachuteController controller;
    controller.show();

    return app.exec();
}

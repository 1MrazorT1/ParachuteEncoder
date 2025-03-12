int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    ParachuteController controller;
    controller.show();
    return app.exec();
}

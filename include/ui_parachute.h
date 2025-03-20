/********************************************************************************
** Form generated from reading UI file 'parachute.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARACHUTE_H
#define UI_PARACHUTE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *messageBox;
    QVBoxLayout *messageLayout;
    QLabel *labelMessage;
    QLineEdit *messageInput;
    QGroupBox *settingsBox;
    QGridLayout *settingsLayout;
    QLabel *labelSectors;
    QSlider *sliderSectors;
    QSpinBox *spinSectors;
    QLabel *labelTracks;
    QSlider *sliderTracks;
    QSpinBox *spinTracks;
    QPushButton *toggleViewButton;
    QStackedWidget *viewStack;
    QWidget *parachutePage;
    QVBoxLayout *verticalLayout_parachute;
    QGraphicsView *parachuteView;
    QWidget *binaryPage;
    QVBoxLayout *verticalLayout_binary;
    QTextEdit *binaryView;
    QPushButton *colorButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(948, 875);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        messageBox = new QGroupBox(centralwidget);
        messageBox->setObjectName(QString::fromUtf8("messageBox"));
        messageLayout = new QVBoxLayout(messageBox);
        messageLayout->setObjectName(QString::fromUtf8("messageLayout"));
        labelMessage = new QLabel(messageBox);
        labelMessage->setObjectName(QString::fromUtf8("labelMessage"));

        messageLayout->addWidget(labelMessage);

        messageInput = new QLineEdit(messageBox);
        messageInput->setObjectName(QString::fromUtf8("messageInput"));

        messageLayout->addWidget(messageInput);


        verticalLayout->addWidget(messageBox);

        settingsBox = new QGroupBox(centralwidget);
        settingsBox->setObjectName(QString::fromUtf8("settingsBox"));
        settingsLayout = new QGridLayout(settingsBox);
        settingsLayout->setObjectName(QString::fromUtf8("settingsLayout"));
        labelSectors = new QLabel(settingsBox);
        labelSectors->setObjectName(QString::fromUtf8("labelSectors"));

        settingsLayout->addWidget(labelSectors, 0, 0, 1, 1);

        sliderSectors = new QSlider(settingsBox);
        sliderSectors->setObjectName(QString::fromUtf8("sliderSectors"));
        sliderSectors->setMinimum(7);
        sliderSectors->setMaximum(42);
        sliderSectors->setValue(21);
        sliderSectors->setOrientation(Qt::Horizontal);

        settingsLayout->addWidget(sliderSectors, 0, 1, 1, 1);

        spinSectors = new QSpinBox(settingsBox);
        spinSectors->setObjectName(QString::fromUtf8("spinSectors"));
        spinSectors->setMinimum(7);
        spinSectors->setMaximum(42);
        spinSectors->setValue(21);

        settingsLayout->addWidget(spinSectors, 0, 2, 1, 1);

        labelTracks = new QLabel(settingsBox);
        labelTracks->setObjectName(QString::fromUtf8("labelTracks"));

        settingsLayout->addWidget(labelTracks, 1, 0, 1, 1);

        sliderTracks = new QSlider(settingsBox);
        sliderTracks->setObjectName(QString::fromUtf8("sliderTracks"));
        sliderTracks->setMinimum(3);
        sliderTracks->setMaximum(10);
        sliderTracks->setValue(5);
        sliderTracks->setOrientation(Qt::Horizontal);

        settingsLayout->addWidget(sliderTracks, 1, 1, 1, 1);

        spinTracks = new QSpinBox(settingsBox);
        spinTracks->setObjectName(QString::fromUtf8("spinTracks"));
        spinTracks->setMinimum(3);
        spinTracks->setMaximum(10);
        spinTracks->setValue(5);

        settingsLayout->addWidget(spinTracks, 1, 2, 1, 1);


        verticalLayout->addWidget(settingsBox);

        toggleViewButton = new QPushButton(centralwidget);
        toggleViewButton->setObjectName(QString::fromUtf8("toggleViewButton"));

        verticalLayout->addWidget(toggleViewButton);

        viewStack = new QStackedWidget(centralwidget);
        viewStack->setObjectName(QString::fromUtf8("viewStack"));
        parachutePage = new QWidget();
        parachutePage->setObjectName(QString::fromUtf8("parachutePage"));
        verticalLayout_parachute = new QVBoxLayout(parachutePage);
        verticalLayout_parachute->setObjectName(QString::fromUtf8("verticalLayout_parachute"));
        parachuteView = new QGraphicsView(parachutePage);
        parachuteView->setObjectName(QString::fromUtf8("parachuteView"));
        parachuteView->setMinimumSize(QSize(600, 400));

        verticalLayout_parachute->addWidget(parachuteView);

        viewStack->addWidget(parachutePage);
        binaryPage = new QWidget();
        binaryPage->setObjectName(QString::fromUtf8("binaryPage"));
        verticalLayout_binary = new QVBoxLayout(binaryPage);
        verticalLayout_binary->setObjectName(QString::fromUtf8("verticalLayout_binary"));
        binaryView = new QTextEdit(binaryPage);
        binaryView->setObjectName(QString::fromUtf8("binaryView"));
        binaryView->setReadOnly(true);

        verticalLayout_binary->addWidget(binaryView);

        viewStack->addWidget(binaryPage);

        verticalLayout->addWidget(viewStack);

        colorButton = new QPushButton(centralwidget);
        colorButton->setObjectName(QString::fromUtf8("colorButton"));

        verticalLayout->addWidget(colorButton);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        viewStack->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Parachute Encoder", nullptr));
        messageBox->setTitle(QCoreApplication::translate("MainWindow", "Message", nullptr));
        labelMessage->setText(QCoreApplication::translate("MainWindow", "Enter Message:", nullptr));
        settingsBox->setTitle(QCoreApplication::translate("MainWindow", "Parachute Settings", nullptr));
        labelSectors->setText(QCoreApplication::translate("MainWindow", "Sectors:", nullptr));
        labelTracks->setText(QCoreApplication::translate("MainWindow", "Tracks:", nullptr));
        toggleViewButton->setText(QCoreApplication::translate("MainWindow", "Switch to Binary View", nullptr));
        binaryView->setStyleSheet(QCoreApplication::translate("MainWindow", "\n"
"            QTextEdit {\n"
"              font-size: 14px;\n"
"              color: white;\n"
"              background-color: #333;\n"
"              border-radius: 5px;\n"
"            }\n"
"            ", nullptr));
        colorButton->setText(QCoreApplication::translate("MainWindow", "Choose Color", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARACHUTE_H

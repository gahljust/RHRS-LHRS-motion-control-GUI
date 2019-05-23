/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionWin;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout;
    QRadioButton *rdbCam;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QLabel *lblTheta;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *btnRotary;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_5;
    QLabel *at1lbl;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *btnx1;
    QPushButton *btny1;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_6;
    QLabel *at2lbl;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnx2;
    QPushButton *btny2;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_4;
    QLabel *lblOrigin;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnXAxis;
    QPushButton *btnYAxis;
    QVBoxLayout *verticalLayout_5;
    QLabel *label;
    QLabel *lblVolts;
    QLabel *label_2;
    QLabel *lblCmdOut;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *btnSetMainSpeed;
    QPushButton *btnSetA_tSpeed;
    QPushButton *btnKill;
    QPushButton *btnQuit;
    QPushButton *btnHome;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *btnAdvanced;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *btnStoreCmd;
    QPushButton *btnReadCmd;
    QPushButton *btnSendCmd;
    QVBoxLayout *verticalLayout_6;
    QLabel *lblCustomCmd;
    QLineEdit *lineEdit;
    QVBoxLayout *verticalLayout_7;
    QLabel *lblCmdCheckDesc;
    QLabel *lblCmdCheck;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnAverageUser;
    QWidget *Camerabtnwid;
    QVBoxLayout *verticalLayout_9;
    QPushButton *btnTiltUp;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *btnPanRight;
    QPushButton *btnPanLeft;
    QPushButton *btnTiltDown;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(979, 620);
        MainWindow->setStyleSheet(QStringLiteral(""));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionWin = new QAction(MainWindow);
        actionWin->setObjectName(QStringLiteral("actionWin"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"	border: 2px solid gray;\n"
"	padding: 0 8px;\n"
"	background: white;\n"
"}\n"
"\n"
"QPushButton\n"
"{\n"
"background: white;\n"
"border: 2px solid black;\n"
"border-radius: 2px;\n"
"}\n"
"\n"
"#btny1\n"
"{\n"
"background-color: rgb(252, 2, 128);\n"
"}\n"
"\n"
"\n"
"#btnx1\n"
"{\n"
"background-color: magenta;\n"
"}\n"
"\n"
"#btny2\n"
"{\n"
"background-color: lightblue;\n"
"}\n"
"\n"
"\n"
"#btnx2\n"
"{\n"
"background-color: blue;\n"
"}\n"
"\n"
"#btnXAxis\n"
"{\n"
"background-color: yellow;\n"
"}\n"
"\n"
"\n"
"\n"
"#btnYAxis\n"
"{\n"
"background-color: cyan;\n"
"}\n"
"\n"
"#btnRotary\n"
"{\n"
"background-color: gray;\n"
"}\n"
"\n"
"\n"
"\n"
""));
        verticalLayout_10 = new QVBoxLayout(centralWidget);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(12, 12, 12, 12);
        rdbCam = new QRadioButton(centralWidget);
        rdbCam->setObjectName(QStringLiteral("rdbCam"));
        rdbCam->setAutoExclusive(false);

        horizontalLayout->addWidget(rdbCam);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(12, 12, 12, 12);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setStyleSheet(QLatin1String("background: none;\n"
"border: black;"));

        verticalLayout->addWidget(label_3);

        lblTheta = new QLabel(centralWidget);
        lblTheta->setObjectName(QStringLiteral("lblTheta"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lblTheta->sizePolicy().hasHeightForWidth());
        lblTheta->setSizePolicy(sizePolicy);
        lblTheta->setMinimumSize(QSize(75, 50));

        verticalLayout->addWidget(lblTheta);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(-1, 0, -1, -1);
        btnRotary = new QPushButton(centralWidget);
        btnRotary->setObjectName(QStringLiteral("btnRotary"));
        sizePolicy.setHeightForWidth(btnRotary->sizePolicy().hasHeightForWidth());
        btnRotary->setSizePolicy(sizePolicy);
        btnRotary->setMinimumSize(QSize(75, 0));
        btnRotary->setMaximumSize(QSize(75, 16777215));
        btnRotary->setStyleSheet(QStringLiteral(""));

        horizontalLayout_9->addWidget(btnRotary);


        verticalLayout->addLayout(horizontalLayout_9);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(12, 12, 12, 12);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setStyleSheet(QLatin1String("border: none;\n"
"background: none;"));

        verticalLayout_2->addWidget(label_5);

        at1lbl = new QLabel(centralWidget);
        at1lbl->setObjectName(QStringLiteral("at1lbl"));
        sizePolicy.setHeightForWidth(at1lbl->sizePolicy().hasHeightForWidth());
        at1lbl->setSizePolicy(sizePolicy);
        at1lbl->setMinimumSize(QSize(150, 50));

        verticalLayout_2->addWidget(at1lbl);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, -1, -1, -1);
        btnx1 = new QPushButton(centralWidget);
        btnx1->setObjectName(QStringLiteral("btnx1"));
        sizePolicy.setHeightForWidth(btnx1->sizePolicy().hasHeightForWidth());
        btnx1->setSizePolicy(sizePolicy);
        btnx1->setMinimumSize(QSize(75, 0));
        btnx1->setStyleSheet(QStringLiteral(""));

        horizontalLayout_4->addWidget(btnx1);

        btny1 = new QPushButton(centralWidget);
        btny1->setObjectName(QStringLiteral("btny1"));
        sizePolicy.setHeightForWidth(btny1->sizePolicy().hasHeightForWidth());
        btny1->setSizePolicy(sizePolicy);
        btny1->setMinimumSize(QSize(75, 0));
        btny1->setStyleSheet(QStringLiteral(""));

        horizontalLayout_4->addWidget(btny1);


        verticalLayout_2->addLayout(horizontalLayout_4);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(12, 12, 12, 12);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setStyleSheet(QLatin1String("border: none;\n"
"background: none;"));

        verticalLayout_3->addWidget(label_6);

        at2lbl = new QLabel(centralWidget);
        at2lbl->setObjectName(QStringLiteral("at2lbl"));
        sizePolicy.setHeightForWidth(at2lbl->sizePolicy().hasHeightForWidth());
        at2lbl->setSizePolicy(sizePolicy);
        at2lbl->setMinimumSize(QSize(150, 50));

        verticalLayout_3->addWidget(at2lbl);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, -1, -1, -1);
        btnx2 = new QPushButton(centralWidget);
        btnx2->setObjectName(QStringLiteral("btnx2"));
        sizePolicy.setHeightForWidth(btnx2->sizePolicy().hasHeightForWidth());
        btnx2->setSizePolicy(sizePolicy);
        btnx2->setMinimumSize(QSize(75, 0));

        horizontalLayout_3->addWidget(btnx2);

        btny2 = new QPushButton(centralWidget);
        btny2->setObjectName(QStringLiteral("btny2"));

        horizontalLayout_3->addWidget(btny2);


        verticalLayout_3->addLayout(horizontalLayout_3);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(12, 12, 12, 12);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setStyleSheet(QLatin1String("background: none;\n"
"border: black;"));

        verticalLayout_4->addWidget(label_4);

        lblOrigin = new QLabel(centralWidget);
        lblOrigin->setObjectName(QStringLiteral("lblOrigin"));
        sizePolicy.setHeightForWidth(lblOrigin->sizePolicy().hasHeightForWidth());
        lblOrigin->setSizePolicy(sizePolicy);
        lblOrigin->setMinimumSize(QSize(150, 50));
        lblOrigin->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout_4->addWidget(lblOrigin);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, -1, -1, -1);
        btnXAxis = new QPushButton(centralWidget);
        btnXAxis->setObjectName(QStringLiteral("btnXAxis"));
        btnXAxis->setMinimumSize(QSize(75, 0));
        btnXAxis->setMaximumSize(QSize(75, 16777215));
        btnXAxis->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(btnXAxis);

        btnYAxis = new QPushButton(centralWidget);
        btnYAxis->setObjectName(QStringLiteral("btnYAxis"));
        sizePolicy.setHeightForWidth(btnYAxis->sizePolicy().hasHeightForWidth());
        btnYAxis->setSizePolicy(sizePolicy);
        btnYAxis->setMinimumSize(QSize(75, 0));
        btnYAxis->setMaximumSize(QSize(75, 16777215));
        btnYAxis->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(btnYAxis);


        verticalLayout_4->addLayout(horizontalLayout_2);


        horizontalLayout->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(12, 12, 12, 12);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QLatin1String("background: none;\n"
"border: none;\n"
""));

        verticalLayout_5->addWidget(label);

        lblVolts = new QLabel(centralWidget);
        lblVolts->setObjectName(QStringLiteral("lblVolts"));

        verticalLayout_5->addWidget(lblVolts);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setStyleSheet(QLatin1String("background: none;\n"
"border: none;\n"
""));

        verticalLayout_5->addWidget(label_2);

        lblCmdOut = new QLabel(centralWidget);
        lblCmdOut->setObjectName(QStringLiteral("lblCmdOut"));

        verticalLayout_5->addWidget(lblCmdOut);


        horizontalLayout->addLayout(verticalLayout_5);


        verticalLayout_10->addLayout(horizontalLayout);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(-1, 0, -1, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        btnSetMainSpeed = new QPushButton(centralWidget);
        btnSetMainSpeed->setObjectName(QStringLiteral("btnSetMainSpeed"));

        horizontalLayout_5->addWidget(btnSetMainSpeed);

        btnSetA_tSpeed = new QPushButton(centralWidget);
        btnSetA_tSpeed->setObjectName(QStringLiteral("btnSetA_tSpeed"));

        horizontalLayout_5->addWidget(btnSetA_tSpeed);

        btnKill = new QPushButton(centralWidget);
        btnKill->setObjectName(QStringLiteral("btnKill"));

        horizontalLayout_5->addWidget(btnKill);

        btnQuit = new QPushButton(centralWidget);
        btnQuit->setObjectName(QStringLiteral("btnQuit"));

        horizontalLayout_5->addWidget(btnQuit);

        btnHome = new QPushButton(centralWidget);
        btnHome->setObjectName(QStringLiteral("btnHome"));

        horizontalLayout_5->addWidget(btnHome);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_8);

        btnAdvanced = new QPushButton(centralWidget);
        btnAdvanced->setObjectName(QStringLiteral("btnAdvanced"));

        horizontalLayout_5->addWidget(btnAdvanced);


        verticalLayout_11->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        btnStoreCmd = new QPushButton(centralWidget);
        btnStoreCmd->setObjectName(QStringLiteral("btnStoreCmd"));
        btnStoreCmd->setEnabled(true);

        horizontalLayout_6->addWidget(btnStoreCmd);

        btnReadCmd = new QPushButton(centralWidget);
        btnReadCmd->setObjectName(QStringLiteral("btnReadCmd"));
        btnReadCmd->setEnabled(true);

        horizontalLayout_6->addWidget(btnReadCmd);

        btnSendCmd = new QPushButton(centralWidget);
        btnSendCmd->setObjectName(QStringLiteral("btnSendCmd"));

        horizontalLayout_6->addWidget(btnSendCmd);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(-1, 0, 0, -1);
        lblCustomCmd = new QLabel(centralWidget);
        lblCustomCmd->setObjectName(QStringLiteral("lblCustomCmd"));
        lblCustomCmd->setStyleSheet(QLatin1String("\n"
"border: none;\n"
"background:none;"));

        verticalLayout_6->addWidget(lblCustomCmd);

        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy1);

        verticalLayout_6->addWidget(lineEdit);


        horizontalLayout_6->addLayout(verticalLayout_6);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(-1, -1, 0, -1);
        lblCmdCheckDesc = new QLabel(centralWidget);
        lblCmdCheckDesc->setObjectName(QStringLiteral("lblCmdCheckDesc"));
        lblCmdCheckDesc->setStyleSheet(QLatin1String("background: none;\n"
"border: none;"));

        verticalLayout_7->addWidget(lblCmdCheckDesc);

        lblCmdCheck = new QLabel(centralWidget);
        lblCmdCheck->setObjectName(QStringLiteral("lblCmdCheck"));

        verticalLayout_7->addWidget(lblCmdCheck);


        horizontalLayout_6->addLayout(verticalLayout_7);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        btnAverageUser = new QPushButton(centralWidget);
        btnAverageUser->setObjectName(QStringLiteral("btnAverageUser"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btnAverageUser->sizePolicy().hasHeightForWidth());
        btnAverageUser->setSizePolicy(sizePolicy2);
        btnAverageUser->setMaximumSize(QSize(1666666, 166666));

        horizontalLayout_6->addWidget(btnAverageUser);


        verticalLayout_11->addLayout(horizontalLayout_6);


        verticalLayout_10->addLayout(verticalLayout_11);

        Camerabtnwid = new QWidget(centralWidget);
        Camerabtnwid->setObjectName(QStringLiteral("Camerabtnwid"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(Camerabtnwid->sizePolicy().hasHeightForWidth());
        Camerabtnwid->setSizePolicy(sizePolicy3);
        Camerabtnwid->setMaximumSize(QSize(50, 50));
        Camerabtnwid->setStyleSheet(QStringLiteral(""));
        verticalLayout_9 = new QVBoxLayout(Camerabtnwid);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(-1, -1, -1, 1);
        btnTiltUp = new QPushButton(Camerabtnwid);
        btnTiltUp->setObjectName(QStringLiteral("btnTiltUp"));

        verticalLayout_9->addWidget(btnTiltUp);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        btnPanRight = new QPushButton(Camerabtnwid);
        btnPanRight->setObjectName(QStringLiteral("btnPanRight"));

        horizontalLayout_8->addWidget(btnPanRight);

        btnPanLeft = new QPushButton(Camerabtnwid);
        btnPanLeft->setObjectName(QStringLiteral("btnPanLeft"));

        horizontalLayout_8->addWidget(btnPanLeft);


        verticalLayout_9->addLayout(horizontalLayout_8);

        btnTiltDown = new QPushButton(Camerabtnwid);
        btnTiltDown->setObjectName(QStringLiteral("btnTiltDown"));

        verticalLayout_9->addWidget(btnTiltDown);


        verticalLayout_10->addWidget(Camerabtnwid);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_10->addItem(verticalSpacer);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", nullptr));
        actionSave->setText(QApplication::translate("MainWindow", "Save", nullptr));
        actionWin->setText(QApplication::translate("MainWindow", "Win", nullptr));
        rdbCam->setText(QApplication::translate("MainWindow", "Camera", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Angle:", nullptr));
        lblTheta->setText(QString());
        btnRotary->setText(QApplication::translate("MainWindow", "Rotary", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Position A_T 1", nullptr));
        at1lbl->setText(QString());
        btnx1->setText(QApplication::translate("MainWindow", "x1", nullptr));
        btny1->setText(QApplication::translate("MainWindow", "y1", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Position A_T 2", nullptr));
        at2lbl->setText(QString());
        btnx2->setText(QApplication::translate("MainWindow", "x2", nullptr));
        btny2->setText(QApplication::translate("MainWindow", "y2", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Main Position:", nullptr));
        lblOrigin->setText(QString());
        btnXAxis->setText(QApplication::translate("MainWindow", "X-Axis", nullptr));
        btnYAxis->setText(QApplication::translate("MainWindow", "Y-Axis", nullptr));
        label->setText(QApplication::translate("MainWindow", "Input Voltage:", nullptr));
        lblVolts->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "Last Command", nullptr));
        lblCmdOut->setText(QString());
        btnSetMainSpeed->setText(QApplication::translate("MainWindow", "Set Main Speeds", nullptr));
        btnSetA_tSpeed->setText(QApplication::translate("MainWindow", "Set A_T Speeds", nullptr));
        btnKill->setText(QApplication::translate("MainWindow", "Kill", nullptr));
        btnQuit->setText(QApplication::translate("MainWindow", "Quit", nullptr));
        btnHome->setText(QApplication::translate("MainWindow", "Go Home", nullptr));
        btnAdvanced->setText(QApplication::translate("MainWindow", "Advanced\n"
"User Mode", nullptr));
        btnStoreCmd->setText(QApplication::translate("MainWindow", "Store Cmnd", nullptr));
        btnReadCmd->setText(QApplication::translate("MainWindow", "Read Cmnd", nullptr));
        btnSendCmd->setText(QApplication::translate("MainWindow", "Send Cmnd", nullptr));
        lblCustomCmd->setText(QApplication::translate("MainWindow", "Custom Command:", nullptr));
        lblCmdCheckDesc->setText(QApplication::translate("MainWindow", "Current Comand:", nullptr));
        lblCmdCheck->setText(QString());
        btnAverageUser->setText(QApplication::translate("MainWindow", "Standard\n"
"User Mode", nullptr));
        btnTiltUp->setText(QApplication::translate("MainWindow", "Tilt Up", nullptr));
        btnPanRight->setText(QApplication::translate("MainWindow", "Pan Right", nullptr));
        btnPanLeft->setText(QApplication::translate("MainWindow", "Pan Left", nullptr));
        btnTiltDown->setText(QApplication::translate("MainWindow", "Tilt Down", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

/********************************************************************************
** Form generated from reading UI file 'inputbox.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTBOX_H
#define UI_INPUTBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InputBox
{
public:
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *lblDesc;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *newMoveCmd;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *rdbx1;
    QRadioButton *rdby1;
    QRadioButton *rdbx2;
    QRadioButton *rdby2;
    QVBoxLayout *verticalLayout;
    QRadioButton *rdbY;
    QRadioButton *rdbX;
    QRadioButton *rdbTheta;
    QDialogButtonBox *buttonBox;
    QDialogButtonBox *buttonBox_2;

    void setupUi(QDialog *InputBox)
    {
        if (InputBox->objectName().isEmpty())
            InputBox->setObjectName(QString::fromUtf8("InputBox"));
        InputBox->resize(449, 209);
        horizontalLayoutWidget_2 = new QWidget(InputBox);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(3, 0, 451, 211));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 20, -1, -1);
        lblDesc = new QLabel(horizontalLayoutWidget_2);
        lblDesc->setObjectName(QString::fromUtf8("lblDesc"));
        lblDesc->setWordWrap(true);

        verticalLayout_2->addWidget(lblDesc);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        newMoveCmd = new QLineEdit(horizontalLayoutWidget_2);
        newMoveCmd->setObjectName(QString::fromUtf8("newMoveCmd"));
        newMoveCmd->setEchoMode(QLineEdit::Normal);

        horizontalLayout_2->addWidget(newMoveCmd);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, -1, -1, -1);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, -1, -1, -1);
        rdbx1 = new QRadioButton(horizontalLayoutWidget_2);
        rdbx1->setObjectName(QString::fromUtf8("rdbx1"));

        verticalLayout_3->addWidget(rdbx1);

        rdby1 = new QRadioButton(horizontalLayoutWidget_2);
        rdby1->setObjectName(QString::fromUtf8("rdby1"));

        verticalLayout_3->addWidget(rdby1);

        rdbx2 = new QRadioButton(horizontalLayoutWidget_2);
        rdbx2->setObjectName(QString::fromUtf8("rdbx2"));

        verticalLayout_3->addWidget(rdbx2);

        rdby2 = new QRadioButton(horizontalLayoutWidget_2);
        rdby2->setObjectName(QString::fromUtf8("rdby2"));

        verticalLayout_3->addWidget(rdby2);


        horizontalLayout_4->addLayout(verticalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, -1, -1, -1);
        rdbY = new QRadioButton(horizontalLayoutWidget_2);
        rdbY->setObjectName(QString::fromUtf8("rdbY"));

        verticalLayout->addWidget(rdbY);

        rdbX = new QRadioButton(horizontalLayoutWidget_2);
        rdbX->setObjectName(QString::fromUtf8("rdbX"));

        verticalLayout->addWidget(rdbX);

        rdbTheta = new QRadioButton(horizontalLayoutWidget_2);
        rdbTheta->setObjectName(QString::fromUtf8("rdbTheta"));

        verticalLayout->addWidget(rdbTheta);


        horizontalLayout_4->addLayout(verticalLayout);


        horizontalLayout_2->addLayout(horizontalLayout_4);


        verticalLayout_2->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout_2);

        buttonBox = new QDialogButtonBox(horizontalLayoutWidget_2);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_3->addWidget(buttonBox);

        buttonBox_2 = new QDialogButtonBox(horizontalLayoutWidget_2);
        buttonBox_2->setObjectName(QString::fromUtf8("buttonBox_2"));
        buttonBox_2->setOrientation(Qt::Vertical);
        buttonBox_2->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_3->addWidget(buttonBox_2);


        retranslateUi(InputBox);
        QObject::connect(buttonBox, SIGNAL(accepted()), InputBox, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), InputBox, SLOT(reject()));

        QMetaObject::connectSlotsByName(InputBox);
    } // setupUi

    void retranslateUi(QDialog *InputBox)
    {
        InputBox->setWindowTitle(QApplication::translate("InputBox", "Dialog", nullptr));
        lblDesc->setText(QString());
        rdbx1->setText(QApplication::translate("InputBox", "x1", nullptr));
        rdby1->setText(QApplication::translate("InputBox", "y1", nullptr));
        rdbx2->setText(QApplication::translate("InputBox", "x2", nullptr));
        rdby2->setText(QApplication::translate("InputBox", "y2", nullptr));
        rdbY->setText(QApplication::translate("InputBox", "Y-Axis", nullptr));
        rdbX->setText(QApplication::translate("InputBox", "X-Axis", nullptr));
        rdbTheta->setText(QApplication::translate("InputBox", "Rotary", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputBox: public Ui_InputBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTBOX_H

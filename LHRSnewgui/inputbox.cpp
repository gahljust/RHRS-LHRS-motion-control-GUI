#include "inputbox.h"
#include "ui_inputbox.h"
#include <string>
#include <iostream>
#include <fstream>
#include <QMessageBox>
#include "unistd.h"



InputBox::InputBox(MainWindow &parent, QString title, QString desc, QString defaultValue,_funcType func) :

    ui(new Ui::InputBox),
    m_func(func),
    parent_window(parent)
{
    ui->setupUi(this);
    this->setWindowTitle(title);
    ui->lblDesc->setText(desc);          //text above input box for title
    ui->newMoveCmd->setText(defaultValue);  //current name of MainWindow

    ui->rdbX->setVisible(false);
    ui->rdbY->setVisible(false);
    ui->rdbTheta->setVisible(false);
    ui->rdbx1->setVisible(false);
    ui->rdbx2->setVisible(false);
    ui->rdby1->setVisible(false);
    ui->rdby2->setVisible(false);

    ui->buttonBox_2->setVisible(false);


    if(title.contains("Advanced"))
    {
        ui->newMoveCmd->setEchoMode(QLineEdit::Password);
    }

    ui->newMoveCmd->setFocus();

    if(title.contains("Main"))
    {
        ui->buttonBox_2->setVisible(true);
        ui->buttonBox->setVisible(false);

        ui->rdbX->setVisible(true);
        ui->rdbY->setVisible(true);
        ui->rdbTheta->setVisible(true);

    }

    if(title.contains("A_T Speed Settings"))
    {
        ui->buttonBox_2->setVisible(true);
        ui->buttonBox->setVisible(false);

        ui->rdbx1->setVisible(true);
        ui->rdbx2->setVisible(true);
        ui->rdby1->setVisible(true);
        ui->rdby2->setVisible(true);


    }


}

InputBox::~InputBox()
{

}

void InputBox::on_buttonBox_accepted()
{


    if(this->windowTitle().contains("Vertical") || this->windowTitle().contains("Horizontal"))
    {

        QString input = ui->newMoveCmd->text();

        double cm = input.split(" ")[0].toDouble();     //2000 steps/cm
        int steps = (int)(cm*2000);

        if(cm != 0)
        {
            QString QcmString = QString::number(cm);

            QString QstepString = QString::number(steps);
            std::string stepString = QstepString.toStdString();

            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Confirmation","Are you sure you want the move the motor " + QcmString + " cm?",QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                (parent_window.*m_func)(stepString);              //first parenthesis is
            }                                                     // change title function pointer,
        }                                                        // second is text contained in the type in

        else
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Invalid Input");
        }
    }

    else if(this->windowTitle().contains("Rotational"))
    {
        QString input = ui->newMoveCmd->text();

        double deg =  input.split(" ")[0].toDouble();     //160 steps/deg
        int steps = (int)(deg*160);

        if(deg != 0)
        {
            QString QdegString = QString::number(deg);

            QString QstepString = QString::number(steps);
            std::string stepString = QstepString.toStdString();

            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Confirmation","Are you sure you want the move the motor " + QdegString + "degrees?",QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                (parent_window.*m_func)(stepString);    //first parenthesis is
            }                                                    // change title function pointer,
        }                                                     // second is text contained in the type in
        else
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Invalid Input");
        }

    }
    else if(this->windowTitle().contains("Advanced"))
    {

        QString password = ui->newMoveCmd->text();

        if(password == "pi")
        {
            (parent_window.*m_func)("");
        }
        else
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Incorrect Password");
        }
    }
    //  std::cout << ss.toStdString() << std::endl;

}

void InputBox::on_buttonBox_2_accepted()
{
    QString input = ui->newMoveCmd->text();


    if(ui->rdbX->isChecked())
    {


        this->parent_window.whichMotor = "h";

        double mmPerSec = input.split(" ")[0].toDouble();
        int stepsPerSec = (int)(mmPerSec*200);

        if(mmPerSec > 0 && mmPerSec <= 30)
        {
            QString QSpdString = QString::number(mmPerSec);
            QString QstepString = QString::number(stepsPerSec);
            std::string stepString = QstepString.toStdString();

            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this,"Confirmation","Are you sure you want change the motors speed to " + QSpdString + " mm/s?",QMessageBox::Yes|QMessageBox::No);
            if(reply == QMessageBox::Yes)
            {
                (parent_window.*m_func)(stepString);
            }
        }
        else
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Invalid Input");
        }


    }

    else if(ui->rdbY->isChecked())
    {


        this->parent_window.whichMotor = "v";

        double mmPerSec = input.split(" ")[0].toDouble();
        int stepsPerSec = (int)(mmPerSec*200);

        if(mmPerSec > 0 && mmPerSec <= 30)
        {
            QString QSpdString = QString::number(mmPerSec);
            QString QstepString = QString::number(stepsPerSec);
            std::string stepString = QstepString.toStdString();

            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this,"Confirmation","Are you sure you want change the motors speed to " + QSpdString + " mm/s?",QMessageBox::Yes|QMessageBox::No);
            if(reply == QMessageBox::Yes)
            {
                (parent_window.*m_func)(stepString);
            }
        }
        else
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Invalid Input");
        }


    }

    else if(ui->rdbTheta->isChecked())
    {


        this->parent_window.whichMotor = "t";

        double degPerSec = input.split(" ")[0].toDouble();
        int stepsPerSec = (int)(degPerSec*160);

        if(degPerSec > 0)
        {
            QString QSpdString = QString::number(degPerSec);
            QString QstepString = QString::number(stepsPerSec);
            std::string stepString = QstepString.toStdString();

            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this,"Confirmation","Are you sure you want change the motors speed to " + QSpdString + " deg/s?",QMessageBox::Yes|QMessageBox::No);
            if(reply == QMessageBox::Yes)
            {
                (parent_window.*m_func)(stepString);

            }
        }
        else
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Invalid Input");
        }


    }

    else if(ui->rdbx1->isChecked())
    {


        this->parent_window.speedtype = "x1";

        double mmPerSec = input.split(" ")[0].toDouble();
        int stepsPerSec = (int)(mmPerSec*200);

        if(mmPerSec > 0 && mmPerSec <= 30)
        {
            QString QSpdString = QString::number(mmPerSec);
            QString QstepString = QString::number(stepsPerSec);
            std::string stepString = QstepString.toStdString();

            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this,"Confirmation","Are you sure you want change the motors speed to " + QSpdString + " mm/s?",QMessageBox::Yes|QMessageBox::No);
            if(reply == QMessageBox::Yes)
            {
                (parent_window.*m_func)(stepString);
            }
        }
        else
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Invalid Input");
        }


    }

    else if(ui->rdbx2->isChecked())
    {


        this->parent_window.speedtype = "x2";

        double mmPerSec = input.split(" ")[0].toDouble();
        int stepsPerSec = (int)(mmPerSec*200);

        if(mmPerSec > 0 && mmPerSec <= 30)
        {
            QString QSpdString = QString::number(mmPerSec);
            QString QstepString = QString::number(stepsPerSec);
            std::string stepString = QstepString.toStdString();

            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this,"Confirmation","Are you sure you want change the motors speed to " + QSpdString + " mm/s?",QMessageBox::Yes|QMessageBox::No);
            if(reply == QMessageBox::Yes)
            {
                (parent_window.*m_func)(stepString);
            }
        }
        else
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Invalid Input");
        }


    }
    else if(ui->rdby1->isChecked())
    {


        this->parent_window.speedtype = "y1";

        double mmPerSec = input.split(" ")[0].toDouble();
        int stepsPerSec = (int)(mmPerSec*200);

        if(mmPerSec > 0 && mmPerSec <= 30)
        {
            QString QSpdString = QString::number(mmPerSec);
            QString QstepString = QString::number(stepsPerSec);
            std::string stepString = QstepString.toStdString();

            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this,"Confirmation","Are you sure you want change the motors speed to " + QSpdString + " mm/s?",QMessageBox::Yes|QMessageBox::No);
            if(reply == QMessageBox::Yes)
            {
                (parent_window.*m_func)(stepString);
            }
        }
        else
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Invalid Input");
        }


    }

    else if(ui->rdby2->isChecked())
    {


        this->parent_window.speedtype = "y2";

        double mmPerSec = input.split(" ")[0].toDouble();
        int stepsPerSec = (int)(mmPerSec*200);

        if(mmPerSec > 0 && mmPerSec <= 30)
        {
            QString QSpdString = QString::number(mmPerSec);
            QString QstepString = QString::number(stepsPerSec);
            std::string stepString = QstepString.toStdString();

            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this,"Confirmation","Are you sure you want change the motors speed to " + QSpdString + " mm/s?",QMessageBox::Yes|QMessageBox::No);
            if(reply == QMessageBox::Yes)
            {
                (parent_window.*m_func)(stepString);
            }
        }
        else
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Invalid Input");
        }


    }

    else
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","No Motor Selected");
    }
    this->close();


}

void InputBox::on_buttonBox_2_rejected()
{
    this->close();
}



void InputBox::on_rdbY_clicked()
{
    ui->lblDesc->setText("How fast would you like the motors to go? (mm/s), Max: 30mm/s");
}

void InputBox::on_rdbX_clicked()
{
    ui->lblDesc->setText("How fast would you like the motors to go? (mm/s), Max: 30mm/s");
}

void InputBox::on_rdbx1_clicked()
{
    ui->lblDesc->setText("How fast would you like the motors to go? (mm/s), Max: 30mm/s");
}

void InputBox::on_rdbx2_clicked()
{
    ui->lblDesc->setText("How fast would you like the motors to go? (mm/s), Max: 30mm/s");
}

void InputBox::on_rdby1_clicked()
{
    ui->lblDesc->setText("How fast would you like the motors to go? (mm/s), Max: 30mm/s");
}

void InputBox::on_rdby2_clicked()
{
    ui->lblDesc->setText("How fast would you like the motors to go? (mm/s), Max: 30mm/s");
}

void InputBox::on_rdbTheta_clicked()
{
    ui->lblDesc->setText("How fast would you like the motors to go? (deg/s)");
}

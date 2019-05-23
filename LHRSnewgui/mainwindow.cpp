#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cstdlib"
#include "fstream"
#include "iostream"
#include "string"
#include <QDialog>
#include "inputbox.h"
#include <string>
#include "VXM_interface_bare.cpp"
#include <QProcess>
#include "assert.h"
#include <QTimer>
#include <QPainter>
#include <sstream>
#include <unistd.h>
#include <QtWidgets>
#include <QPushButton>
#include <QLabel>


VXM_interface *port;
Log *port2;
VXM_interface2 *port3;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setWindowTitle("Velmex Motor Controller Left Arm");
    setFocusPolicy(Qt::StrongFocus);
    this->setFocus();

    x = 0;                     //motor coordinates


    port = new VXM_interface();
    port2 = new Log();
    port3 = new VXM_interface2;

    ui->btnReadCmd->setVisible(false);                       //this chunk hides stuff for advanced user mode
    //ui->btnReadBuf->setVisible(false);
    ui->btnStoreCmd->setVisible(false);
    ui->btnSendCmd->setVisible(false);
    ui->lineEdit->setVisible(false);
    ui->lblTheta->setStyleSheet("background-color: white");
    ui->btnAverageUser->setVisible(false);
    ui->lblCmdCheck->setStyleSheet("background-color: yellow");
    ui->lblCmdCheck->setVisible(false);
    //ui->lblBufferOut->setStyleSheet("background-color: yellow");
   // ui->lblBufferOut->setVisible(false);
    //ui->lblBufferOutDesc->setVisible(false);
    ui->lblCmdCheckDesc->setVisible(false);
    ui->lblCustomCmd->setVisible(false);
    ui->btnHome->setVisible(false);
    ui->btnKill->setStyleSheet("background-color: red");


    ui->btnPanRight->setVisible(false);
    ui->btnPanLeft->setVisible(false);
    ui->btnTiltUp->setVisible(false);
    ui->btnTiltDown->setVisible(false);


    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(readLabJack()));         //reads labjack output  10 times/sec
    timer->start(1000);

    QTimer *timer2 = new QTimer(this);
    connect(timer2,SIGNAL(timeout()),this,SLOT(update()));              //updates drawing 10 times/sec
    timer2->start(100);

    QTimer *timer3 = new QTimer(this);                                  //updates angle display once/sec
    timer3->start(1000);
    connect(timer3,SIGNAL(timeout()),this,SLOT(displayAngle()));


    int panStart = 53;
    int tiltStart = 53;

    QProcess p1;
    QString exe1 = "gpio -g pwm 18 " + QString::number(panStart);
    p1.startDetached(exe1);
    p1.waitForFinished();

    QProcess p2;
    QString exe2 = "gpio -g pwm 13 " + QString::number(tiltStart);
    p2.startDetached(exe2);
    p2.waitForFinished();

    panPos = panStart;
    tiltPos = tiltStart;

 }

MainWindow::~MainWindow()
{
    QProcess p;
    QString exe = "pkill raspivid";
    p.start(exe);
    p.waitForFinished();
    delete ui;
}

void MainWindow::on_btnQuit_clicked()
{
    port->exit_interface();
    qApp->quit();

}



void MainWindow::displayAngle()
{
    QFont font("Arial",20,QFont::Bold);                         // displays the angle of the rotary motor on a timer
    double theta = port2->getInitialT()/160;
    QString thetaDisplay = QString::number(theta);
    ui->lblTheta->setAlignment(Qt::AlignCenter);
    ui->lblTheta->setFont(font);
    ui->lblTheta->setText(thetaDisplay + "\u00B0");            //unicode for theta

}




void MainWindow::on_btnXAxis_clicked()   //button on right controls horizontal motor
{
    whichMotor = "h";
    InputBox *inp2 = new InputBox(*this,
                                  "Horizontal Motor",
                                  "How many centimeters would you like to move?",
                                  "",
                                  &MainWindow::storeCommand);
    inp2->exec();
    delete inp2;
}




void MainWindow::on_btnYAxis_clicked()   // button on left, controls vertical motor
{
    whichMotor = "v";
    InputBox *inp = new InputBox(*this,
                                 "Vertical Motor",
                                 "How many centimeters would you like to move?",
                                 "",
                                 &MainWindow::storeCommand);
    inp->exec();
    delete inp;
}




void MainWindow::on_btnRotary_clicked()
{
    whichMotor = "t";
    InputBox *inp3 = new InputBox(*this,
                                  "Rotational Motor",
                                  "How many degrees would you like to move?",
                                  "",
                                  &MainWindow::storeCommand);
    inp3->exec();
    delete inp3;
}

void MainWindow::on_btnx1_clicked()
{
    whichMotor = "x1";
    speedtype = "x1";
    InputBox *inp4 = new InputBox(*this,"Horizontal A_T Motor x1","How many centimeters would you like to move?","",&MainWindow::storeCommand2);
    inp4->exec();
    delete inp4;
}

void MainWindow::on_btny1_clicked()
{
    whichMotor = "y1";
    speedtype ="y1";
    InputBox *inp5 = new InputBox(*this,"Vertical A_T Motor y1","How many centimeters would you like to move?","",&MainWindow::storeCommand2);
    inp5->exec();
    delete inp5;
}

void MainWindow::on_btnx2_clicked()
{
    whichMotor = "x2";
    speedtype ="x2";
    InputBox *inp6 = new InputBox(*this,"Horizontal A_T Motor x2","How many centimeters would you like to move?","",&MainWindow::storeCommand2);
    inp6->exec();
    delete inp6;
}

void MainWindow::on_btny2_clicked()
{
    whichMotor = "y2";
    speedtype ="y2";
    InputBox *inp7 = new InputBox(*this,"Vertical A_T Motor y2","How many centimeters would you like to move?","",&MainWindow::storeCommand2);
    inp7->exec();
    delete inp7;
}


void MainWindow::changeTitle(QString title)
{
    this->setWindowTitle(title);

}




void MainWindow::readLabJack()
{
    QProcess p;
    QString exe = "python script.py";            //main x axis voltage
    p.start(exe);
    p.waitForFinished(3000);
    QString output = p.readAll();

    QProcess p2;
    QString exe2 = "python script2.py";         //main input voltage
    p2.start(exe2);
    p2.waitForFinished(3000);
    QString output2 = p2.readAll();

    QProcess p3;
    QString exe3 = "python script3.py";         // main y axis voltage
    p3.start(exe3);
    p3.waitForFinished(3000);
    QString output3 = p3.readAll();

    QProcess p4;
    QString exe4 = "python script4.py";       // for x1 transducer voltage
    p4.start(exe4);
    p4.waitForFinished(3000);
    QString output4 = p4.readAll();

    QProcess p5;
    QString exe5 = "python script5.py";         // for y1 transducer voltage
    p5.start(exe5);
    p5.waitForFinished(3000);
    QString output5 = p5.readAll();

    QProcess p6;
    QString exe6 = "python script6.py";         // for x2 transducer voltage
    p6.start(exe6);
    p6.waitForFinished(3000);
    QString output6 = p6.readAll();

    QProcess p7;
    QString exe7 = "python script7.py";         // for y2 transducer voltage
    p7.start(exe7);
    p7.waitForFinished(3000);
    QString output7 = p7.readAll();



    double inputVoltage = output2.toDouble();     //changed volts to xvolts and distance to xdistance
    double xvolts = output.toDouble();
    double yvolts = output3.toDouble();
    double x1volts = output4.toDouble();
    double y1volts = output5.toDouble();
    double x2volts = output6.toDouble();
    double y2volts = output7.toDouble();


    double voltsToCmRatio = inputVoltage/54;
    double atvoltsToCmRatio = inputVoltage/10.2 ;   //total range of travel is 4 inches (10.2 cm) for one set of transducers and 54 cm for another set.

    double xdistance = xvolts/voltsToCmRatio;
    double ydistance = yvolts/voltsToCmRatio;

    double x1distance = x1volts/atvoltsToCmRatio;
    double y1distance = y1volts/atvoltsToCmRatio;
    double x2distance = x2volts/atvoltsToCmRatio;
    double y2distance = y2volts/atvoltsToCmRatio;

    if(xdistance < .0000001)
    {
        xdistance = 0;
    }

    if(ydistance < .0000001)
    {
        ydistance = 0;
    }

    if(x1distance < .0000001)
    {
        x1distance = 0;
    }

    if(y1distance < .0000001)
    {
        y1distance = 0;
    }

    if(x2distance < .0000001)
    {
        x2distance = 0;
    }

    if(y2distance < .0000001)
    {
        y2distance = 0;
    }

    QString voltDisplay = QString::number(inputVoltage,'f',2);
    ui->lblVolts->setText( voltDisplay + "V");


    if(inputVoltage < 0.1)
    {
        x = 0;
        y = 0;
        x1 = 0;
        y1 = 0;
        x2 = 0;
        y2 = 0;
    }

    y = ydistance;   // this actually moves the x axis of the gui
    x = xdistance;   // this actually moves the y axis of the gui
    y1 = y1distance;
    x1 = x1distance;
    y2 = y2distance;
    x2 = x2distance;

}


void MainWindow::storeCommand(std::string steps)
{
    ui->lblCmdOut->setText("");

    port->new_move_command(whichMotor,steps);                                  //store move command
    QString commandName = QString::fromStdString(port->get_command());         //print action to gui
    ui->lblCmdOut->setText(ui->lblCmdOut->text() + commandName);


    port->send_command();
    ui->lblCmdOut->setText(ui->lblCmdOut->text());
}

void MainWindow::storeCommand2(std::string steps)
{
    port3->new_move_command2(whichMotor,steps);
    port3->send_command2();
}


void MainWindow::on_btnSendCmd_clicked()
{
    if(port->get_port_open())
    {
        port->send_command();
    }

    else
    {
        assert(port->get_port_open());
    }


}





void MainWindow::on_btnStoreCmd_clicked()
{
    std::string cmd = (ui->lineEdit->text()).toStdString();
    port->set_command(cmd);
}





void MainWindow::on_btnReadCmd_clicked()
{
    ui->lblCmdCheck->setText(QString::fromStdString(port->get_command()));
}




/*void MainWindow::on_btnReadBuf_clicked()
{
    ui->lblBufferOut->setText("");
    ui->lblBufferOut->setText(QString::fromStdString(port->read_port()));
}*/




/*void MainWindow::on_btnHome_clicked()
{
    std::string cmd = "S2M100,I2M0,I2M-2000,";
    port->set_command(cmd);
    usleep(1);

    if(port->get_port_open())
    {
        port->send_command();
    }
    else
    {
        assert(port->get_port_open());
    }

}*/
void MainWindow::on_btnAdvanced_clicked()
{
    InputBox *inp9 = new InputBox(*this,
                                  "Advanced User Verification",
                                  "Password: ",
                                  "",
                                  &MainWindow::advancedUser);
    inp9->exec();
    delete inp9;




}
//makes advanced user buttons visible
void MainWindow::advancedUser(std::string s)
{
    ui->btnReadCmd->setVisible(true);
   // ui->btnReadBuf->setVisible(true);
    ui->btnStoreCmd->setVisible(true);
    ui->btnSendCmd->setVisible(true);
    ui->lineEdit->setVisible(true);
    ui->btnAverageUser->setVisible(true);
    ui->lblCmdCheck->setVisible(true);
   // ui->lblBufferOut->setVisible(true);
    //ui->lblBufferOutDesc->setVisible(true);
    ui->lblCmdCheckDesc->setVisible(true);
    ui->lblCustomCmd->setVisible(true);
}
//makes advanced user buttons hidden
void MainWindow::on_btnAverageUser_clicked()
{
    ui->btnReadCmd->setVisible(false);
   // ui->btnReadBuf->setVisible(false);
    ui->btnStoreCmd->setVisible(false);
    ui->btnSendCmd->setVisible(false);

    ui->lineEdit->setVisible(false);

    ui->btnAverageUser->setVisible(false);

    ui->lblCmdCheck->setVisible(false);

    //ui->lblBufferOut->setVisible(false);
   // ui->lblBufferOutDesc->setVisible(false);
    ui->lblCmdCheckDesc->setVisible(false);
    ui->lblCustomCmd->setVisible(false);
}
//stops velmex motors
void MainWindow::on_btnKill_clicked()
{
    std::string cmd = "D";
    port->set_command(cmd);
    usleep(10);
    if(port->get_port_open())
    {
        port->send_command();
    }

    else
    {
        assert(port->get_port_open());
    }
}
//changes speed of main velmex motors
void MainWindow::sendSpeedCmd(std::string stepsPerSec)
{
    std::string sendCmd = "";

    if(whichMotor == "h")
    {
        sendCmd = "S1M" + stepsPerSec + ",";
    }
    else if(whichMotor == "v")
    {
        sendCmd = "S2M" + stepsPerSec + ",";
    }
    else if(whichMotor == "t")
    {
        sendCmd = "S3M" + stepsPerSec + ",";
    }
    port->set_command(sendCmd);
    usleep(10);
    port->send_command();

    QString commandName = QString::fromStdString(port->get_command());

    ui->lblCmdOut->setText(ui->lblCmdOut->text() + commandName);

    ui->lblCmdOut->setText(ui->lblCmdOut->text());
}

void MainWindow::on_btnSetMainSpeed_clicked()
{
    InputBox *inp5 = new InputBox(*this,
                                  "Change Main Speed Settings",
                                  "How fast would you like the motors to go?",
                                  "",
                                  &MainWindow::sendSpeedCmd);
    inp5->exec();
    delete inp5;
}

void MainWindow::sendSpeedCmd2(std::string stepsPerSec)
{
    std::string sendCmd2 = "";

    if(whichMotor == "x1")
    {
        sendCmd2 = "S1M" + stepsPerSec + ",";
    }
    else if(whichMotor == "y1")
    {
        sendCmd2 = "S2M" + stepsPerSec + ",";
    }
    else if(whichMotor == "x2")
    {
        sendCmd2 = "S3M" + stepsPerSec + ",";
    }
    else if(whichMotor == "y2")
    {
        sendCmd2 = "S4M" + stepsPerSec + ",";
    }
    port3->set_command2(sendCmd2);
    usleep(10);
    port3->send_command2();

    QString commandName = QString::fromStdString(port3->get_command2());

    ui->lblCmdOut->setText(ui->lblCmdOut->text() + commandName);

    ui->lblCmdOut->setText(ui->lblCmdOut->text());
}

void MainWindow::on_btnSetA_tSpeed_clicked()
{
    InputBox *inp10 = new InputBox(*this,
                                  "Change A_T Speed Settings",
                                  "How fast would you like the motors to go?",
                                  "",
                                  &MainWindow::sendSpeedCmd);
    inp10->exec();
    delete inp10;
}

void MainWindow::on_rdbCam_clicked()
{
    if(ui->rdbCam->isChecked())
    { //raspivid -o - -t 0 -w 1920 -h 1080 -p -n -fps 30 | cvlc -vvv stream:///dev/stdin --sout '#rtp{sdp=rtsp://:8554/}' :demux=h264
        QProcess C1;  // what the new command does is set up a stream on the local area network that can be accessed through VLC opening a network connection to rtsp://(PI's IP address):8554/
        QString exe = "./cam.sh";   //new
        C1.start(exe);
        C1.waitForFinished();
    }
    else if(ui->rdbCam->isChecked() == false)
    {
        QProcess p;
        QString exe = "pkill raspivid";
        p.start(exe);
        p.waitForFinished();
    }
}



void MainWindow::paintEvent(QPaintEvent *)
{
    //To change the geometry the rectangle set up is ( x position, y position,length, width)
    // changing the fill color is straight forward and the axies that need to move in the
    //appropriate direction need to be assinged to move with that variabl
// the x axis of the main motors is actually controlled by the varible y, and the y axis of the main motors is controlled by the varible x.

    QPainter borderPaint(this);
    borderPaint.drawRect(QRect(10,310,460,300));      // rectangle for main display
    borderPaint.drawRect(QRect(470,310,460,300));     //rectangle for a_t display
    borderPaint.drawLine(825,310,825,610);            // vertical line for mian symbols
    borderPaint.drawLine(825,430,930,430);            // line for main symbols
    borderPaint.drawLine(365,310,365,610);            //vertical line for a_t dectors symbols
    borderPaint.drawLine(365,430,470,430);            // hor. line for a_t symbols


    QPainter yPainter(this);
    yPainter.setPen(QPen(Qt::black, 4, Qt::SolidLine, Qt::RoundCap));        //Y axis slider
    yPainter.setBrush(QBrush(Qt::cyan, Qt::SolidPattern));
    yPainter.drawRect(530,472,266,38);
    yPainter.setBrush(QBrush(Qt::blue,Qt::SolidPattern));                    //Y axis motor
    yPainter.drawRect(796,480,22,22.6);


    QPainter xPainter(this);
    xPainter.setPen(QPen(Qt::black,4,Qt::SolidLine,Qt::RoundCap));                    //X axis slider
    xPainter.setBrush(QBrush(Qt::yellow,Qt::SolidPattern));
    xPainter.drawRect(758-(y*13),424,38,136);                                      // this will move the slider and motor to the right with positive x values
    xPainter.setBrush(QBrush(Qt::blue,Qt::SolidPattern));                             //x axis motor
    xPainter.drawRect(766-(y*13),402,22.6,22);


    QPainter rotarypainter(this);                                                     //Paints gray rotory motor
    rotarypainter.setPen(QPen(Qt::black,4,Qt::SolidLine,Qt::RoundCap));
    rotarypainter.setBrush(QBrush(Qt::gray,Qt::SolidPattern));
    rotarypainter.drawRect(758-(y*6),512-(x*9),38,48);                        // this will move the rotary motor up and to the right with positve x and y values


    QPainter mainaxiespainter(this);                                                //axies for main
    mainaxiespainter.setPen(QPen(Qt::black,4,Qt::SolidLine,Qt::RoundCap));
    mainaxiespainter.drawLine(900,420,900,340);
    mainaxiespainter.drawLine(835,400,915,400);
    mainaxiespainter.drawText(885,350,"X");
    mainaxiespainter.drawText(840,415,"Y");

    QPainter ataxiespainter(this);                                          //axies for A_t's
    ataxiespainter.setPen(QPen(Qt::black,4,Qt::SolidLine,Qt::RoundCap));
    ataxiespainter.drawLine(395,420,395,340);
    ataxiespainter.drawLine(375,400,455,400);
    ataxiespainter.drawText(380,350,"Y");
    ataxiespainter.drawText(445,415,"X");

    QPainter mainelectrons(this);                                          //Lines for main electrons
    mainelectrons.setPen(QPen(Qt::red,4,Qt::DashLine,Qt::RoundCap));
    mainelectrons.drawLine(890,600,890,500);
    mainelectrons.drawLine(870,600,870,550);
    mainelectrons.drawLine(910,600,910,550);

    QPainter A_Telectrons(this);                                        //ellipse and cros for A_t electrons
    A_Telectrons.setRenderHint(QPainter::Antialiasing);
    A_Telectrons.setPen(QPen(Qt::red,4,Qt::SolidLine,Qt::RoundCap));
    A_Telectrons.drawEllipse(392,510,50,50);
    A_Telectrons.drawLine(392,535,442,535);
    A_Telectrons.drawLine(417,510,417,560);

    QPainterPath path;
    path.moveTo(880,500);                                                 //arrowhead for main electrons
    path.lineTo(890,490);
    path.lineTo(900,500);
    mainelectrons.fillPath(path,QBrush(QColor("red")));

    QPainterPath path2;
    path2.moveTo(860,550);                                                //arrowhead for main electrons
    path2.lineTo(870,540);
    path2.lineTo(880,550);
    mainelectrons.fillPath(path2,QBrush(QColor("red")));

    QPainterPath path3;
    path3.moveTo(900,550);                                                 //arrowhead for main electrons
    path3.lineTo(910,540);
    path3.lineTo(920,550);
    mainelectrons.fillPath(path3,QBrush(QColor("red")));

    QPainter At1painter(this);                                               //draws first rectangle for A_t 1
    At1painter.setPen(QPen(Qt::black,4,Qt::SolidLine,Qt::RoundCap));
    At1painter.setBrush(QBrush(Qt::magenta,Qt::DiagCrossPattern));
    At1painter.drawRect(75+(x1*6),400-(y1*6),120,40);

    QPainter At2painter(this);                                          //draws second rectangle for A _t 2
    At2painter.setPen(QPen(Qt::black,4,Qt::SolidLine,Qt::RoundCap));
    At2painter.setBrush(QBrush(Qt::blue,Qt::DiagCrossPattern));
    At2painter.drawRect(145+(x2*6),460-(y2*6),120,40);


                                                         //Different fonts used in text drawing
    QFont elecfont("Times",7,QFont::Bold);
    QFont axiesfont("Times",12,QFont::Bold);
    QFont titlefont("Times",16,QFont::Bold);


    QPainter textpainter(this);
    textpainter.setPen(Qt::red);
    textpainter.setFont(elecfont);
    textpainter.drawText(830,465,"Scattering Electrons");
    textpainter.drawText(370,465,"Scattering Electrons");
    textpainter.setPen(Qt::black);
    textpainter.setFont(axiesfont);
    textpainter.drawText(387,325,"A_t Axies");
    textpainter.drawText(844,325,"Main Axies");
    textpainter.setFont(titlefont);
    textpainter.drawText(530,330,"Left Arm Main Motors");
    textpainter.drawText(75,330,"Left Arm A_T Detectors");


    QFont font("Arial",14,QFont::Bold);
    QString xDisplay = QString::number(x,'f',2);                              //code to display the main x and y coordinats
    QString yDisplay = QString::number(y,'f',2);
    QString x1Display = QString::number(x1,'f',2);                              //code to display the main x and y coordinats
    QString y1Display = QString::number(y1,'f',2);
    QString x2Display = QString::number(x2,'f',2);                              //code to display the main x and y coordinats
    QString y2Display = QString::number(y2,'f',2);

    ui->lblVolts->setAlignment(Qt::AlignCenter);
    ui->lblOrigin->setText("("+xDisplay +","+ yDisplay + ") cm");
    ui->lblOrigin->setFont(font);
    ui->lblOrigin->setAlignment(Qt::AlignCenter);
    ui->at1lbl->setText("("+x1Display +","+ y1Display + ") cm");
    ui->at1lbl->setFont(font);
    ui->at1lbl->setAlignment(Qt::AlignCenter);
    ui->at2lbl->setText("("+x2Display +","+ y2Display + ") cm");
    ui->at2lbl->setFont(font);
    ui->at2lbl->setAlignment(Qt::AlignCenter);



    /* QPainter painter(this);

        painter.setRenderHint(QPainter::Antialiasing, true);

        painter.setPen(QPen(Qt::black, 4, Qt::SolidLine, Qt::RoundCap)); //Box 1
        painter.drawRect(250,165,618,225);


        painter.setPen(QPen(Qt::black, 4, Qt::SolidLine, Qt::RoundCap)); //Box 2
        painter.drawRect(250,390,618,225);

        painter.setPen(QPen(Qt::red,4,Qt::SolidLine,Qt::RoundCap));    // scattering electron symbol

        painter.drawEllipse(265,275,15,15);
        painter.setPen(QPen(Qt::red,4,Qt::SolidLine,Qt::RoundCap));



        painter.setPen(QPen(Qt::black, 4, Qt::SolidLine, Qt::RoundCap));  // blue smaller platform 3
        painter.setBrush(QBrush(Qt::blue, Qt::DiagCrossPattern));
        painter.drawRect(484,192,150,30);


        painter.setPen(QPen(Qt::black,4,Qt::SolidLine,Qt::RoundCap));    // magenta smaller platform 4
        painter.setBrush(QBrush(Qt::magenta,Qt::DiagCrossPattern));
        painter.drawRect(484,217,150,30);

        painter.setPen(QPen(Qt::black, 4, Qt::SolidLine, Qt::RoundCap));  //Y axis slider
        painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
        painter.drawRect(530,472,266,38);


        painter.setPen(QPen(Qt::black,4,Qt::SolidLine,Qt::RoundCap));    //Y axis motor
        painter.setBrush(QBrush(Qt::blue,Qt::SolidPattern));
        painter.drawRect(796,480,22,22.6);

        painter.setPen(QPen(Qt::black,4,Qt::SolidLine,Qt::RoundCap));    //X axis slider
        painter.setBrush(QBrush(Qt::yellow,Qt::SolidPattern));
        painter.drawRect(758-(y*6),424,38,136);


        painter.setPen(QPen(Qt::black,4,Qt::SolidLine,Qt::RoundCap));  //X axis motor
        painter.setBrush(QBrush(Qt::blue,Qt::SolidPattern));
        painter.drawRect(766-(y*6),402,22.6,22);


        painter.setPen(QPen(Qt::black,4,Qt::SolidLine,Qt::RoundCap));    // Rotary motor
        painter.setBrush(QBrush(Qt::gray,Qt::SolidPattern));
        painter.drawRect(758-(y*6),512,38,48);


        painter.setPen(QPen(Qt::magenta,7,Qt::SolidLine,Qt::RoundCap));      //origin point
        painter.drawPoint(758-y*6,512);


        painter.setPen(QPen(Qt::black,2,Qt::SolidLine,Qt::RoundCap));  //line that points to (0,0)
        painter.drawLine(754-y*6,507,530-y*6,405);


        QPainterPath path;
        path.moveTo(754-y*6,507);                                //arrowhead of line that points to (0,0)
        path.lineTo(747-y*6,507);
        path.lineTo(754-y*6,500);
        painter.fillPath(path,QBrush(QColor("black")));

        painter.drawLine(707.4,110,657.4,110);
        painter.drawLine(707.4,110,707.4,70);

        painter.setPen(QPen(Qt::red,2,Qt::DashDotLine,Qt::RoundCap));  // middle red line
        painter.drawLine(315,530,315,580);

        painter.setPen(QPen(Qt::red,2,Qt::DashDotLine,Qt::RoundCap));  // left red line
        painter.drawLine(305,555,305,580); //10 pixels to the left, half the height of the middle

        painter.setPen(QPen(Qt::red,2,Qt::DashDotLine,Qt::RoundCap));  // right red line
        painter.drawLine(325,555,325,580);  //10 pixels to the right, half the height of the middle

        QPainterPath path4;                                         // left red arrow for bottom scattering elec.
        path4.moveTo(300,555);
        path4.lineTo(305,548);
        path4.lineTo(310,555);
        painter.fillPath(path4,QBrush(QColor("red")));

        QPainterPath path5;                                         // middle red arrow
        path5.moveTo(310,530);
        path5.lineTo(315,523);
        path5.lineTo(320,530);
        painter.fillPath(path5,QBrush(QColor("red")));

        QPainterPath path6;                                         // right red arrow
        path6.moveTo(320,555);
        path6.lineTo(325,548);
        path6.lineTo(330,555);
        painter.fillPath(path6,QBrush(QColor("red")));


        ui->lblOrigin->setGeometry(QRect(480-(y*6),395+(x*6),300,50));//738,290,300,50
        QString xDisplay = QString::number(x);
        QString yDisplay = QString::number(y);

        ui->lblOrigin->setText("("+xDisplay+","+  yDisplay + ") cm");//"("xDisplay new

        QPainterPath path2;
        path2.moveTo(657.4,105);                                  //arrows
        path2.lineTo(657.4,115);
        path2.lineTo(650.4,110);
        painter.fillPath(path2,QBrush(QColor("black")));

        QPainterPath path3;
        path3.moveTo(702.4,70);
        path3.lineTo(707.4,63);                                     //arrows
        path3.lineTo(712.4,70);
        painter.fillPath(path3,QBrush(QColor("black")));*/


    if(ui->rdbCam->isChecked() == true)
    {

        if(ui->btnPanLeft->isDown() == true && panPos <= 247)
        {
            int panPosNew = panPos + 3;
            QProcess p;
            QString exe = "gpio -g pwm 18 " + QString::number(panPosNew);
            p.startDetached(exe);
            p.waitForFinished();
            panPos = panPosNew;
        }

        else if(ui->btnPanRight->isDown() == true && panPos >= 53)
        {
            int panPosNew = panPos - 3;
            QProcess p;
            QString exe = "gpio -g pwm 18 " + QString::number(panPosNew);
            p.startDetached(exe);
            p.waitForFinished();
            panPos = panPosNew;
        }

        if(ui->btnTiltUp->isDown() == true && tiltPos <= 247)
        {
            int tiltPosNew = tiltPos + 3;
            QProcess p;
            QString exe = "gpio -g pwm 13 " + QString::number(tiltPosNew);
            p.startDetached(exe);
            p.waitForFinished();
            tiltPos = tiltPosNew;
        }
        else if(ui->btnTiltDown->isDown() == true && tiltPos >= 53)
        {
            int tiltPosNew = tiltPos - 3;
            QProcess p;
            QString exe = "gpio -g pwm 13 " + QString::number(tiltPosNew);
            p.startDetached(exe);
            p.waitForFinished();
            tiltPos = tiltPosNew;
        }
    }
}




/*void MainWindow::updateDrawing()
{


    update();
}
*/


void MainWindow::keyPressEvent(QKeyEvent * event)
{

    if(event->key() == Qt::Key_Right)
    {
        ui->btnPanRight->setDown(true);
    }
    if(event->key() == Qt::Key_Left)
    {
        ui->btnPanLeft->setDown(true);
    }
    if(event->key() == Qt::Key_Up)
    {
        ui->btnTiltUp->setDown(true);
    }if(event->key() == Qt::Key_Down)
    {
        ui->btnTiltDown->setDown(true);
    }


}

void MainWindow::keyReleaseEvent(QKeyEvent * event)
{

    if(event->key() == Qt::Key_Right)
    {
        ui->btnPanRight->setDown(false);
    }
    if(event->key() == Qt::Key_Left)
    {
        ui->btnPanLeft->setDown(false);
    }
    if(event->key() == Qt::Key_Up)
    {
        ui->btnTiltUp->setDown(false);
    }
    if(event->key() == Qt::Key_Down)
    {
        ui->btnTiltDown->setDown(false);
    }

}





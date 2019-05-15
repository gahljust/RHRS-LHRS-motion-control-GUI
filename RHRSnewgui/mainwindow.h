#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QProcess>
#include <QList>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    std::string whichMotor;
    std::string speedtype;



private slots:
    //void on_btnReadBuf_clicked();
    void on_btnReadCmd_clicked();
    void on_btnStoreCmd_clicked();
    void on_btnSendCmd_clicked();
    //void on_btnHome_clicked();
    void on_btnAdvanced_clicked();
    void on_btnXAxis_clicked();
    void on_btnYAxis_clicked();
    void on_btnQuit_clicked();
    void on_btnRotary_clicked();
    void on_btnAverageUser_clicked();
    void on_btnKill_clicked();
    void on_btnSetMainSpeed_clicked();
    void on_btnSetA_tSpeed_clicked();
    void on_btnx1_clicked();
    void on_btny1_clicked();
    void on_btnx2_clicked();
    void on_btny2_clicked();
    //void updateDrawing();
    void paintEvent(QPaintEvent *);


   // void moveCamera(int);
    //void Test();




    void on_rdbCam_clicked();



    void readLabJack();

    void displayAngle();









private:
    Ui::MainWindow *ui;
    void changeTitle(QString);
    void storeCommandVertical(std::string);

    void storeCommand(std::string);
    void storeCommand2(std::string);
    void advancedUser(std::string);
    void sendSpeedCmd(std::string);
    void sendSpeedCmd2(std::string);
    double x;
    double y;
    double x1;
    double y1;
    double x2;
    double y2;
    int panPos;
    int tiltPos;
    void keyPressEvent(QKeyEvent *);

    void keyReleaseEvent(QKeyEvent *);


    //void readLabJack();






};


#endif // MAINWINDOW_H

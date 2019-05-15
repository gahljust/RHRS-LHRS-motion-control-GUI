#ifndef INPUTBOX_H
#define INPUTBOX_H

#include <QDialog>
#include <QString>
#include <mainwindow.h>
namespace Ui {
class InputBox;
}

class InputBox : public QDialog
{
    Q_OBJECT

public:
    typedef void (MainWindow::*_funcType)(std::string);
    _funcType m_func;

   // typedef void (MainWindow::*_funcType(std::string, std::string));
   // _funcType n_func;


    MainWindow &parent_window;
    explicit InputBox(MainWindow &parent, QString title, QString desc, QString defaultValue,_funcType func);

    ~InputBox();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_2_accepted();
    void on_buttonBox_2_rejected();

    void on_rdbY_clicked();

    void on_rdbX_clicked();

    void on_rdbTheta_clicked();

    void on_rdbx1_clicked();

    void on_rdbx2_clicked();

    void on_rdby1_clicked();

    void on_rdby2_clicked();


private:
    Ui::InputBox *ui;
};

#endif // INPUTBOX_H

#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>
#include <QTextEdit>
namespace Ui {
class Notepad;
}

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    explicit Notepad(QWidget *parent = 0);
    ~Notepad();

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionExit_triggered();

    void on_actionNew_triggered();

    void on_actionSave_As_triggered();

    void on_pushButton_clicked();



    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_actionOpen_2_triggered();

    void on_actionNew_2_triggered();

    void on_actionSave_2_triggered();

    void on_actionSave_AS_triggered();

private:
    Ui::Notepad *ui;
    QString fileName;
};

#endif // NOTEPAD_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSettings>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class thread1 : public QObject
{
    Q_OBJECT

public:

    ~thread1()
    {
        deleteLater();
    }
    void run();

public slots:
    void test();
    void test2();
    void test3();
signals:
    void doWork();
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
    thread1 *my;
    thread1 *my2;
    thread1 *my3;
    QThread* mTread;
    QThread* mTread2;
    QThread* mTread3;
    QSettings* mySetting;
};

#endif // MAINWINDOW_H

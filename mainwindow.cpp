#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QThread"
#include <QMutex>
#include <QWaitCondition>
#include <QWidget>

#include <QFile>
#include <QFileDialog>
QWaitCondition waiting;
QMutex mutex;

typedef struct _CurveData
{
    QVector<double> keyVec;//x
    QVector<double> valVec;//y
}CurveData;//单个曲线的数据

QVector<CurveData> myData;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



//    this->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/background.jpg)"));


    QString strPath = QCoreApplication::applicationDirPath()+"/config.ini";
    mySetting = new QSettings(strPath, QSettings::IniFormat);
    //    mySetting->clear();
    //    mySetting->beginGroup("dataConfig");
    //    mySetting->setValue("user"," zhangsan");
    //    mySetting->setValue("age"," 30");
    //    mySetting->setValue("height",140.5);
    //    mySetting->endGroup();

    qDebug()<< mySetting->allKeys()<<endl;
    QString width  = mySetting->value("/Res/width").toString();
    qDebug()<<width<<endl;

    my = new thread1;
    my2 = new thread1;
    my3 = new thread1;
    mTread = new QThread();
    mTread2 = new QThread();
    mTread3 = new QThread();

    qDebug()<<"当前线程"<<QThread::currentThreadId()<<endl;

    my->moveToThread(mTread);
    my2->moveToThread(mTread2);
    my3->moveToThread(mTread3);

    connect(my,SIGNAL(doWork()),my,SLOT(test()));
    connect(my2,SIGNAL(doWork()),my2,SLOT(test2()));
    connect(my3,SIGNAL(doWork()),my3,SLOT(test3()));


}

MainWindow::~MainWindow()
{
    delete ui;
}




void thread1::test()
{
    qDebug()<<"线程1"<<QThread::currentThreadId()<<endl;
    mutex.lock();
    qDebug()<<"线程1等待条件"<<endl;
    waiting.wait(&mutex);
    qDebug()<<"线程1条件达成"<<endl;
    mutex.unlock();
    mutex.lock();
    qDebug()<<"线程1抢占"<<endl;

    mutex.unlock();
}

void thread1::test2()
{
    qDebug()<<"线程2"<<QThread::currentThreadId()<<endl;
    mutex.lock();
    qDebug()<<"释放条件"<<endl;
    waiting.wakeAll();
    mutex.unlock();
}

void thread1::test3()
{
    qDebug()<<"线程3"<<QThread::currentThreadId();
    mutex.lock();
    qDebug()<<"线程3等待条件";
    waiting.wait(&mutex);
    qDebug()<<"线程3条件达成";
    mutex.unlock();
    mutex.lock();
    qDebug()<<"线程3抢占";
    mutex.unlock();
}

void MainWindow::on_pushButton_clicked()
{
    qDebug()<<"线程启动";
    mTread->start();
    mTread2->start();
    mTread3->start();
    qDebug()<<"线程运行？"<<mTread->isRunning();

}

void MainWindow::on_pushButton_2_clicked()
{


    mTread->quit();
    mTread->wait();
    mTread2->quit();
    mTread2->wait();
    mTread3->quit();
    mTread3->wait();
    qDebug()<<"线程退出"<<mTread->isRunning();


}

void MainWindow::on_pushButton_3_clicked()
{
    emit my->doWork();
}

void MainWindow::on_pushButton_4_clicked()
{
    emit my2->doWork();
}

void MainWindow::on_pushButton_5_clicked()
{
     emit my3->doWork();
}

void MainWindow::on_pushButton_6_clicked()
{
//    QFileDialog *FileDialog = new QFileDialog(this);
//    QString fileName = FileDialog->getOpenFileName(this,tr("Open File"),qApp->applicationDirPath ());
//    if(fileName == "")
//        return ;
    QString fileName= qApp->applicationDirPath() +"/QDarkStyleSheet.qss";
    qDebug()<<fileName;
    QFile file(fileName);
    qDebug()<<file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString styleSheet = this->styleSheet();
        styleSheet += QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
    }
}

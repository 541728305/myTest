#include "mainwindow.h"
#include "form.h"
#include <QApplication>
#include "QThread"
#include <QFile>
#include <QMutex>
#include <QDateTime>
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
  {
    // 加锁
        static QMutex mutex;
        mutex.lock();

        QByteArray localMsg = msg.toUtf8();

        QString strMsg("");
        switch(type)
        {
        case QtDebugMsg:
            strMsg = QString("Debug:");
            break;
        case QtWarningMsg:
            strMsg = QString("Warning:");
            break;
        case QtCriticalMsg:
            strMsg = QString("Critical:");
            break;
        case QtFatalMsg:
            strMsg = QString("Fatal:");
            break;
        }

        // 设置输出信息格式
        QString strDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
        QString strMessage = QString("Message:[%6] —— %1 File:%2  Line:%3  Function:%4  DateTime:%5")
                .arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function).arg(strDateTime).arg(strMsg.constData());

        // 输出信息至文件中（读写、追加形式）
        QFile file("log.txt");
        file.open(QIODevice::ReadWrite | QIODevice::Append);
        QTextStream stream(&file);
        stream << strMessage << "\r\n";
        file.flush();
        file.close();

        // 解锁
        mutex.unlock();
  }
int main(int argc, char *argv[])
{
    qInstallMessageHandler(myMessageOutput);
    QApplication a(argc, argv);
    MainWindow w;
    Form f;
    w.show();
//    f.show();

    return a.exec();
}

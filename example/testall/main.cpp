#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#if QT_VERSION < QT_VERSION_CHECK(4, 6, 0)
#if defined(Q_WS_WIN)
    QTextCodec::setCodecForCStrings( QTextCodec::codecForLocale() );
    QTextCodec::setCodecForLocale( QTextCodec::codecForLocale() );
    QTextCodec::setCodecForTr( QTextCodec::codecForLocale() );
#else
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
#endif
#endif
    qsrand(QTime::currentTime().msec());
    MainWindow w;
    w.show();
    
    return a.exec();
}

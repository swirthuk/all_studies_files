#include "baldawindow.h"
#include <QApplication>
#include <QTextCodec>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //For russian letters
    QTextCodec *cyrillicCodec = QTextCodec::codecForName("Windows-1251");
    QTextCodec::setCodecForLocale(cyrillicCodec);
    BaldaWindow w;
    w.show();

    return a.exec();
}

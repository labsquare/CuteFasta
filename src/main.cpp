#include "MainWindow.h"
#include <QApplication>
#include "FastaFile.h"
#include "FastaViewer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow win;
    win.show();


    return a.exec();
}

#include "MainWindow.h"
#include <QApplication>
#include "FastaFile.h"
#include "FastaViewer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FastaViewer * viewer = new FastaViewer;
    viewer->show();



    return a.exec();
}

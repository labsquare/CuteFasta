#include "MainWindow.h"
#include <QApplication>
#include "FastaFile.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FastaFile device("/home/sacha/hg19.fa");

    qDebug()<<device.readIndex();

    qDebug()<<device.sequence("chr3", 100000, 100300);



    return 0;
}

#include "MainWindow.h"
#include <QApplication>
#include "FastaFile.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FastaFile device("/home/sacha/hg19.fa");

    device.createIndex();


    return 0;
}

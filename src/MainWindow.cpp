#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mViewer = new FastaViewer;
    mSlider = new QSlider(Qt::Horizontal);
    mSlider->setRange(5,40);

    setCentralWidget(mViewer);

    ui->mainToolBar->addWidget(mSlider);

    connect(mSlider,SIGNAL(valueChanged(int)), mViewer, SLOT(setFontSize(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include "FastaViewer.h"

FastaViewer::FastaViewer(QWidget *parent)
    :QScrollArea(parent)
{

    resize(800,600);
    mFile = new FastaFile("/home/sacha/hg19.fa");

    setRegion("chr3", 100000);


}

void FastaViewer::setRegion(const QByteArray &seqName, quint64 start)
{
    mSeqName = seqName;
    mStart = start;


    computeScrollBar();


}



void FastaViewer::paintEvent(QPaintEvent *event)
{

    qDebug()<<"paint";

    QByteArray seq = mFile->sequence("chr3", mStart, mStart + 10000);

    QPainter painter(viewport());

    QFont font = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    font.setPointSize(15);


    QFontMetrics metrics (font);

    painter.setFont(font);
    painter.setBrush(QBrush(Qt::red));
    painter.setPen(QPen(Qt::blue));

    QRect tbox = viewport()->rect();
    tbox.adjust(20,20,-20,-20);
    painter.drawRect(tbox);



    QTextOption option;
    option.setWrapMode(QTextOption::WrapAnywhere);
    painter.drawText(tbox, QString(seq), option);







}

void FastaViewer::scrollContentsBy(int dx, int dy)
{
    Q_UNUSED(dx);

    mStart += 10;

    update();

}

void FastaViewer::resizeEvent(QResizeEvent *event)
{
    computeScrollBar();
    QAbstractScrollArea::resizeEvent(event);
}

void FastaViewer::computeScrollBar()
{

    verticalScrollBar()->setPageStep(viewport()->size().height());


    verticalScrollBar()->setRange(0, mFile->indexOf(mSeqName).size);



}


#include "FastaViewer.h"

FastaViewer::FastaViewer(QWidget *parent)
    :QScrollArea(parent)
{

    resize(800,600);
    mFile = new FastaFile("/tmp/example/test.fa");


    mFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    mFont.setPointSize(15);


    setRegion("chr1", 0);


}

void FastaViewer::setRegion(const QByteArray &seqName, quint64 start)
{
    mSeqName = seqName;
    mStart   = start;
    computeScrollBar();
}

void FastaViewer::setFontSize(int size)
{
    mFont.setPointSize(size);
    update();
}



void FastaViewer::paintEvent(QPaintEvent *event)
{

    QByteArray seq = mFile->sequence("chr1", mStart, mStart + 10000);

    QPainter painter(viewport());

    painter.setFont(mFont);
    painter.setBrush(QBrush(Qt::white));
    painter.setPen(QPen(Qt::blue));

    QRect tbox = viewport()->rect();


//    tbox.adjust(0,0,0,0);
    tbox.setLeft(200);
    tbox.setWidth(lineWidth(mBasePerLine));

    painter.drawRect(tbox);


    for (int y=0,nb = mStart-mBasePerLine; y<= viewport()->height(); y+= fontMetrics().height(),nb += mBasePerLine)
    {
        painter.drawText(0,y, QString::number(nb));
    }




    QTextOption option;
    option.setWrapMode(QTextOption::WrapAnywhere);
    painter.drawText(tbox, QString(seq), option);







}

void FastaViewer::scrollContentsBy(int dx, int dy)
{
    Q_UNUSED(dx);

    mStart += -dy * mBasePerLine;

    update();

}

void FastaViewer::resizeEvent(QResizeEvent *event)
{
    computeScrollBar();
    QAbstractScrollArea::resizeEvent(event);
}

void FastaViewer::computeScrollBar()
{


    int lineCount = qFloor(mFile->indexOf("chr1").size / mBasePerLine);

    qDebug()<<"line count" << lineCount;


    verticalScrollBar()->setPageStep(seqHeight(("chr1")) / viewport()->height());
    verticalScrollBar()->setRange(0, lineCount);

    qDebug()<<"height"<<seqHeight("chr1")<< " "<< viewport();



}

QFontMetrics FastaViewer::fontMetrics() const
{
    return QFontMetrics(mFont);
}

int FastaViewer::lineWidth(int baseCount) const
{
    return fontMetrics().width(QString("A").repeated(baseCount));
}

int FastaViewer::seqHeight(const QString &seqname) const
{
    int lineCount = mFile->indexOf("chr1").size / mBasePerLine;
    return fontMetrics().height() * lineCount;

}


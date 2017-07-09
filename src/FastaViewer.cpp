#include "FastaViewer.h"

FastaViewer::FastaViewer(QWidget *parent)
    :QScrollArea(parent)
{

    resize(800,600);
    mFile = new FastaFile("/tmp/example/test.fa");
//    mFile = new FastaFile("/home/sacha/hg19.fa");


    mFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    mFont.setPointSize(15);


    setRegion("chr1", 0);


}

void FastaViewer::setRegion(const QByteArray &seqName, quint64 start)
{
    mSeqName       = seqName;
    mCurrentLine   = start / mBasePerLine;
    computeScrollBar();
}

void FastaViewer::setFontSize(int size)
{
    mFont.setPointSize(size);
    computeScrollBar();
    update();
}



void FastaViewer::paintEvent(QPaintEvent *event)
{

    int maxLine = viewport()->height() / fontMetrics().height();

    int start = mBasePerLine * mCurrentLine;


    QByteArray seq = mFile->sequence("chr1", start, start + maxLine * mBasePerLine);

    QPainter painter;
    painter.begin(viewport());

    painter.setFont(mFont);
    painter.setBrush(QBrush(Qt::white));
    painter.setPen(QPen(Qt::blue));

    QRect tbox = viewport()->rect();


//    tbox.adjust(0,0,0,0);
    tbox.setLeft(mNumMargin);
    tbox.setWidth(lineWidth(mBasePerLine));

    painter.drawRect(tbox);


    for (int y=0,nb = start; y<= viewport()->height(); y+= fontMetrics().height(),nb += mBasePerLine)
    {
        QRect rect(0,y, mNumMargin - 5, y + fontMetrics().height());
        painter.drawText(rect, Qt::AlignRight, QString::number(nb));
    }




    QTextOption option;
    option.setWrapMode(QTextOption::WrapAnywhere);
    painter.drawText(tbox, QString(seq), option);


    painter.end();





}

void FastaViewer::scrollContentsBy(int dx, int dy)
{
    Q_UNUSED(dx);

    mCurrentLine += -dy;

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


    verticalScrollBar()->setPageStep(maxLine());
    verticalScrollBar()->setRange(0, lineCount - maxLine() + 1);




}

QFontMetrics FastaViewer::fontMetrics() const
{
    return QFontMetrics(mFont);
}

int FastaViewer::lineWidth(int baseCount) const
{
    return qCeil(fontMetrics().width(QString("A").repeated(baseCount))) + 1;
}

int FastaViewer::seqHeight(const QString &seqname) const
{
    int lineCount = mFile->indexOf("chr1").size / mBasePerLine;
    return fontMetrics().height() * lineCount;

}

int FastaViewer::maxLine() const
{
    return qCeil(viewport()->height() / fontMetrics().height());
}


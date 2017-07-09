#ifndef FASTAVIEWER_H
#define FASTAVIEWER_H
#include <QScrollArea>
#include <QtWidgets>
#include <QtCore>
#include "FastaFile.h"


class FastaViewer : public QScrollArea
{
    Q_OBJECT
public:
    FastaViewer(QWidget * parent = nullptr);
    void setRegion(const QByteArray& seqName, quint64 start);

public Q_SLOTS:
    void setFontSize(int size);

protected:
    void paintEvent(QPaintEvent * event) Q_DECL_OVERRIDE;
    void scrollContentsBy(int dx, int dy) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent * event) Q_DECL_OVERRIDE;

    void computeScrollBar();

    QFontMetrics fontMetrics() const;

    int lineWidth(int baseCount) const;
    int seqHeight(const QString& seqname) const;



private:
    FastaFile  * mFile;
    QByteArray mSeqName;
    quint64 mStart;
    QFont mFont;
    int mBasePerLine = 51;





};

#endif // FASTAVIEWER_H

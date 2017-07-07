#ifndef FASTAFILE_H
#define FASTAFILE_H
#include <QtCore>

class FastaFile
{
public:
    FastaFile(const QString& filename);

    bool createIndex() const;
    bool readIndex();
    bool hasIndex() const;

    QList<QByteArray> seqnames() const;
    QByteArray sequence(const QByteArray& seqname, quint64 start = 0, quint64 end = 0);


    QString indexPath() const;

private:
    QFile * mFile;

    struct Index {
       QString seqname;
       quint64 size;
       quint64 offset;
       quint64 chompLineSize;
       quint64 lineSize;

    };

    QHash<QByteArray, Index> mIndexes;

};

#endif // FASTAFILE_H

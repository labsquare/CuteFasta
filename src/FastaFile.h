#ifndef FASTAFILE_H
#define FASTAFILE_H
#include <QtCore>

struct Index {
   QString seqname;
   quint64 size;
   quint64 offset;
   quint64 chompLineSize;
   quint64 lineSize;

};

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

    Index indexOf(const QByteArray& seqName);

private:
    QFile * mFile;



    QHash<QByteArray, Index> mIndexes;

};

#endif // FASTAFILE_H

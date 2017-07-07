#ifndef FASTAFILE_H
#define FASTAFILE_H
#include <QtCore>

class FastaFile
{
public:
    FastaFile(const QString& filename);

    bool createIndex() const;
    bool readIndex() const;
    bool hasIndex() const;

    QStringList seqnames() const;
    QByteArray sequence(const QString& seqname, quint64 pos = 0);


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

    QHash<QString, Index> mIndexes;

};

#endif // FASTAFILE_H

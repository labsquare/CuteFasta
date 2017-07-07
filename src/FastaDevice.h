#ifndef FASTAFILE_H
#define FASTAFILE_H
#include <QtCore>

class FastaDevice
{
public:
    FastaDevice(QIODevice * device);
    FastaDevice(const QString& filename);

    void createIndex() const;
    bool hasIndex() const;

    QStringList seqnames() const;
    QByteArray sequence(const QString& seqname, quint64 pos = 0);



private:
    QIODevice * mDevice;
};

#endif // FASTAFILE_H

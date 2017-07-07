#include "FastaDevice.h"


FastaDevice::FastaDevice(QIODevice *device)
    :mDevice(device)
{

}

FastaDevice::FastaDevice(const QString &filename)
    :mDevice(new QFile(filename))
{

}

void FastaDevice::createIndex() const
{


}

bool FastaDevice::hasIndex() const
{

}

QStringList FastaDevice::seqnames() const
{

}

QByteArray FastaDevice::sequence(const QString &seqname, quint64 pos)
{

}

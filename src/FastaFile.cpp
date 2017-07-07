#include "FastaFile.h"


FastaFile::FastaFile(const QString &filename)
    :mFile(new QFile(filename))
{
    qDebug()<<mFile->exists();
}

bool FastaFile::createIndex() const
{
    if (!hasIndex())
    {


        QList<Index> indexes;
        Index index;


        if (mFile->open(QIODevice::ReadOnly))
        {

            while (!mFile->atEnd()) {
                QByteArray line = mFile->readLine();



                if (line.startsWith(">"))
                {
                    if (!index.seqname.isEmpty())
                        indexes.append(index);

                    index.seqname = line.right(line.length()-1).trimmed();
                    index.offset = mFile->pos();
                    index.size = 0;
                    index.lineSize = 0;
                    index.chompLineSize = 0;
                }

                else
                {
                    index.size += line.trimmed().length();
                    // initialization
                    if (index.lineSize == 0)
                    {
                        index.chompLineSize = line.trimmed().length();
                        index.lineSize = line.size();
                    }

                    // classic case
                    //                    if (index.lineSize != line.size() || index.chompLineSize != line.simplified().size()){
                    //                        qDebug()<<Q_FUNC_INFO<<"line has different sizes";
                    //                        return false;
                    //                    }
                }
            }

            mFile->close();
        }

        // write index File ;
        QFile indexFile(indexPath());
        if (indexFile.open(QIODevice::WriteOnly))
        {
            QTextStream stream(&indexFile);
            for (Index i : indexes)
            {
                stream<<i.seqname<<"\t"<<i.size<<"\t"<<i.offset<<"\t"<<i.chompLineSize<<"\t"<<i.lineSize<<"\n";

            }

            qDebug()<<"Index file writted";
            indexFile.close();
            return true;
        }

    }

    return false;


}

bool FastaFile::readIndex()
{
    if (hasIndex())
    {
        mIndexes.clear();
        QFile indexFile(indexPath());

        if (indexFile.open(QIODevice::ReadOnly))
        {

            while (!indexFile.atEnd()) {
                QByteArray line = indexFile.readLine().trimmed();
                QList<QByteArray> row = line.split(QChar::Tabulation);
                mIndexes[row[0]] = {row[0], row[1].toInt(), row[2].toInt(), row[3].toInt(), row[4].toInt()};

            }
        }
        else
            qDebug()<<"cannot read";
    }

    else
    {
        qDebug()<<Q_FUNC_INFO<<"no index";
    }

    return true;
}

bool FastaFile::hasIndex() const
{
    return QFile::exists(indexPath());
}

QList<QByteArray> FastaFile::seqnames() const
{
    return mIndexes.keys();
}

QByteArray FastaFile::sequence(const QByteArray &seqname, quint64 start, quint64 end)
{


    if (!mIndexes.contains(seqname))
        return QByteArray();


    Index index = mIndexes[seqname];

    quint64 length = end - start ;

    if (start > end )
        return QByteArray();

    if (end > index.size)
        end = index.size;


    if (mFile->open(QIODevice::ReadOnly))
    {

        quint64 offset = index.offset + start + start / index.chompLineSize;
        mFile->seek(offset);

        return mFile->read(length + (length)/index.chompLineSize).simplified();



    }



}



QString FastaFile::indexPath() const
{
    QFileInfo info(*mFile);
    return info.absoluteDir().filePath(info.fileName()+".fai");
}

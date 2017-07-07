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

                    index.seqname = line.right(line.length()-1).simplified();
                    index.offset = mFile->pos();
                    index.size = 0;
                    index.lineSize = 0;
                    index.chompLineSize = 0;
                }

                else
                {
                    index.size += line.simplified().length();
                    // initialization
                    if (index.lineSize == 0)
                    {
                        index.chompLineSize = line.simplified().length();
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
        }

    }


}

bool FastaFile::readIndex() const
{
    if (hasIndex())
    {
        QFile indexFile(indexPath());

        if (indexFile.open(QIODevice::ReadOnly))
        {

            while (!mFile->atEnd()) {
                QByteArray line = mFile->readLine().simplified();
                QList<QByteArray> row = line.split(QChar::Tabulation);



            }
        }
    }

    else
    {
        qDebug()<<Q_FUNC_INFO<<"no index";
    }
}

bool FastaFile::hasIndex() const
{
    return QFile::exists(indexPath());
}

QStringList FastaFile::seqnames() const
{

}

QByteArray FastaFile::sequence(const QString &seqname, quint64 pos)
{

}

QString FastaFile::indexPath() const
{
    QFileInfo info(*mFile);
    return info.absoluteDir().filePath(info.fileName()+".fai");
}

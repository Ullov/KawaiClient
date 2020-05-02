#ifndef KFFFS_H
#define KFFFS_H

#include "../KTools/file.h"
#include "../KTools/converter.h"
#include "KffFileTypes/kffdir.h"
#include "kffstream.h"

namespace Kff
{
    class Fs
    {
    public:
        Fs(const QString &path, const QString &fileName);

        qint64 dataBlockStart;

        template<typename T>
        T create();

    private:
        QByteArray signature = "KFFS0001";
        KTools::File *fileInNativeFs;
        qint64 inodesBlockStart = signature.size();
        qint64 inodesNumber = 0;
        qint64 inodesAppendNumber = 20;

        void appendInodes();
        qint64 findClearInode();
        qint64 findClearCluster();
    };
}


#endif // KFFFS_H

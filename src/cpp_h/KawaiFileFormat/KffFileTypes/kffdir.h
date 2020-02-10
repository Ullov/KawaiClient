#ifndef KFFDIR_H
#define KFFDIR_H

#include "kfffileclass.h"

class KffDir : public KffFileClass
{
public:
    KffDir();

    bool open(const qint64 &pos);
    void save();

private:
// structures
    struct FolderHeader : public Header
    {
        quint64 filesNumber;
        QVector<qint64> addresToFile;
    };

// variables
    FolderHeader *folderHeaderStruct;
    qint64 startPos;

// functions
    bool readHeader(const qint64 &pos);
};

#endif // KFFDIR_H

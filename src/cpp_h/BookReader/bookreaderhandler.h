#ifndef BOOKREADERHANDLER_H
#define BOOKREADERHANDLER_H

#include "../KTools/archiverw.h"
#include <QDir>

class BookReaderHandler
{
    Q_OBJECT
public:
    BookReaderHandler();

public slots:
    void getBookContent(const QString pathToBook);
};

#endif // BOOKREADERHANDLER_H

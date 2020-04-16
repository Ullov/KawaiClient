#include "bookreaderhandler.h"

BookReaderHandler::BookReaderHandler()
{

}

void BookReaderHandler::getBookContent(const QString pathToBook)
{
    QList<QString> list = pathToBook.split("/", QString::SplitBehavior::SkipEmptyParts);
    ArchiveRW::extractArchive("", QDir::temp().path() + "/BookReader/" + list.last());
}

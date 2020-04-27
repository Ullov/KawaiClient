#include "ktoolsqmlinterface.h"

KToolsQmlInterface::KToolsQmlInterface() {}

void KToolsQmlInterface::optionsHandlerSetRootProgramPath(const QString path)
{
    OptionsHandler::setRootProgramPath(path);
}

void KToolsQmlInterface::optionsHandlerEmitRootProgramPath()
{
    emit optionsHandlerSendRootProgramPath(OptionsHandler::rootProgramPath);
}

void KToolsQmlInterface::optionsHandlerSlotGetParam(const QString pathToParam)
{
    emit optionsHandlerSignalParam(pathToParam, OptionsHandler::getParam(pathToParam));
}

void KToolsQmlInterface::optionsHandlerSlotSetParam(const QString pathToParam, const QString param)
{
    OptionsHandler::setParam(pathToParam, param);
}

void KToolsQmlInterface::curlSendProgress(const QList<double> list, const qint64 millisecondsFromStart, const KEnums::Parsers downloaderType)
{
    emit obj.curlProgressSignal(list, millisecondsFromStart, downloaderType);
}

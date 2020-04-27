#include "ktoolsqmlinterface.h"

KToolsQmlInterface::KToolsQmlInterface()
{

}

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

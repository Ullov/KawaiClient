#ifndef KTOOLSQMLINTERFACE_H
#define KTOOLSQMLINTERFACE_H

#include <QObject>
#include "optionshandler.h"

class KToolsQmlInterface : public QObject
{
    Q_OBJECT
public:
    KToolsQmlInterface();

public slots:
    void optionsHandlerSetRootProgramPath(const QString path); // OptionsHandler::setRootProgramPath()
    void optionsHandlerEmitRootProgramPath(); // OptionsHandler::emitRootProgramPath()
    void optionsHandlerSlotSetParam(const QString pathToParam, const QString param); // OptionsHandler::slotSetParam()
    void optionsHandlerSlotGetParam(const QString pathToParam); // OptionsHandler::slotGetParam()

signals:
    void optionsHandlerSendRootProgramPath(const QString path); // OptionsHandler::sendRootProgramPath()
    void optionsHandlerSignalParam(const QString pathToParam, const QVariant param); // OptionsHandler::signalParam()
};

#endif // KTOOLSQMLINTERFACE_H

#include "ErrorHandler.h"
#include <QDebug>

ErrorHandler::ErrorHandler(QObject *parent) : QObject(parent)
{

}

void ErrorHandler::handleError(const QString &message)
{
    qDebug() << "Ошибка:" << message;
    emit errorOccurred(message);
}
